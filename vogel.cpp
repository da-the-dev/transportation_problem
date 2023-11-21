#include "bfs_generator.cpp"
#include "transportation_matrix.cpp"
#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

class Vogels : public BFS_Generator {
public:
  void generate_bfs(TransportationMatrix m) {
    vector<int> &u = m.u;
    vector<int> &v = m.v;
    vector<int> &supply = m.supply;
    vector<int> &demand = m.demand;

    // Repeat until only one untouched cell remains
    do {
      // Find penalties for rows
      for (int row = 0; row < m.height; row++) {
        if (m.isCrossedRow(row))
          continue;
        vector<int> rowCosts;
        for (int col = 0; col < m.width; col++)
          if (!m.isCrossedColumn(col))
            rowCosts.push_back(m.c(row, col));
        sort(rowCosts.begin(), rowCosts.end());

        u[row] = rowCosts[1] - rowCosts[0];
      }

      // Find penalties for columns
      for (int col = 0; col < m.width; col++) {
        if (m.isCrossedColumn(col))
          continue;
        vector<int> colCosts;
        for (int row = 0; row < m.height; row++)
          if (!m.isCrossedRow(row))
            colCosts.push_back(m.c(row, col));
        sort(colCosts.begin(), colCosts.end());

        v[col] = colCosts[1] - colCosts[0];
      }

      // Find max row penalty and its index gg
      int maxRowPenalty = -1, maxRowPenaltyIdx = -1;
      for (int row = 0; row < m.height; row++)
        if (!m.isCrossedRow(row))
          if (u[row] > maxRowPenalty) {
            maxRowPenalty = u[row];
            maxRowPenaltyIdx = row;
          }

      // Find max col penalty and its index
      int maxColPenalty = -1, maxColPenaltyIdx = -1;
      for (int col = 0; col < m.width; col++)
        if (!m.isCrossedColumn(col))
          if (v[col] > maxColPenalty) {
            maxColPenalty = v[col];
            maxColPenaltyIdx = col;
          }

      // Find the largest penalty
      if (maxRowPenalty >= maxColPenalty) {
        // Find the smallest cost within row maxRowPenaltyIdx
        int smallestCost = INT_MAX;
        int smallestCostCol = -1;
        for (int col = 0; col < m.width; col++)
          if (!m.isCrossedColumn(col)) {
            if (m.c(maxRowPenaltyIdx, col) < smallestCost) {
              smallestCost = m.c(maxRowPenaltyIdx, col);
              smallestCostCol = col;
            }
          }
        // Find the largest - supply or demand
        int maxAllocation =
            min(supply[maxRowPenaltyIdx], demand[smallestCostCol]);
        // Deallocate supply, fill demand, and update allocation
        supply[maxRowPenaltyIdx] -= maxAllocation;
        demand[smallestCostCol] -= maxAllocation;
        m(maxRowPenaltyIdx, smallestCostCol).allocated = maxAllocation;

        // Crossout spent row or column
        if (demand[smallestCostCol] == 0) {
          v[smallestCostCol] = -INT_MAX;
          m.crossOutColumn(smallestCostCol);
        } else {
          u[maxRowPenaltyIdx] = -INT_MAX;
          m.crossOutRow(maxRowPenaltyIdx);
        }
      } else {
        int smallestCost = INT_MAX;
        int smallestCostRow = -1;
        for (int row = 0; row < m.height; row++)
          if (!m.isCrossedRow(row)) {
            if (m.c(row, maxColPenaltyIdx) < smallestCost) {
              smallestCost = m.c(row, maxColPenaltyIdx);
              smallestCostRow = row;
            }
          }

        // Find the largest - supply or demand
        int maxAllocation =
            min(supply[smallestCostRow], demand[maxColPenaltyIdx]);
        // Deallocate supply, fill demand, and update allocation
        supply[smallestCostRow] -= maxAllocation;
        demand[maxColPenaltyIdx] -= maxAllocation;
        m(smallestCostRow, maxColPenaltyIdx).allocated = maxAllocation;

        // Crossout spent row or column
        if (supply[smallestCostRow] == 0) {
          u[smallestCostRow] = -INT_MAX;
           m.crossOutRow(smallestCostRow);
        } else {
          v[maxColPenaltyIdx] = -INT_MAX;
          m.crossOutColumn(maxColPenaltyIdx);
        }
      }
    // } while (m.crossedOutColumns.size() != m.width - 1 ||
    //          m.crossedOutRows.size() != m.height - 1);
    } while (m.crossedOutColumns.size() - 1 >= m.width ||
             m.crossedOutRows.size() - 1 >= m.height);

    cout << m << endl;
    for (int i = 0; i < m.height; i++)
    {
      for (int j = 0; j < m.width; j++) {
        cout << "x" << i + 1 << j + 1 << ": " << m(i, j).allocated << endl;
      }
    }
  }
};
