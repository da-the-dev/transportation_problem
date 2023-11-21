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
      auto uMax = max_element(u.begin(), u.end());
      int maxRowPenalty = *uMax;
      int maxRowPenaltyIdx = uMax - u.begin();

      // Find max col penalty and its index
      auto vMax = max_element(v.begin(), v.end());
      int maxColPenalty = *vMax;
      int maxColPenaltyIdx = vMax - v.begin();

      // Find the largest penalty
      if (maxRowPenalty >= maxColPenalty) {
        // Find the smallest cost within row maxRowPenaltyIdx
        int smallestCost = INT_MAX;
        int col = 0;
        for (; col < m.width; col++)
          smallestCost = m.c(maxRowPenaltyIdx, col) < smallestCost
                             ? m.c(maxRowPenaltyIdx, col)
                             : smallestCost;

        // Find the largest - supply or demand
        col -= 1;
        int maxAllocation = min(supply[maxRowPenaltyIdx], demand[col]);
        // Deallocate supply, fill demand, and update allocation
        supply[maxRowPenaltyIdx] -= maxAllocation;
        demand[col] -= maxAllocation;
        m(maxRowPenaltyIdx, col).allocated = maxAllocation;

        // Crossout spent row or column
        if (demand[col] == 0) {
          v[col] = -INT_MAX;
          m.crossOutColumn(col);
        }
        else {
          u[maxRowPenaltyIdx] = -INT_MAX;
          m.crossOutRow(maxRowPenaltyIdx);
        }
      } else {
        int smallestCost = INT_MAX;
        int row = 0;
        for (; row < m.height; row++)
          smallestCost = m.c(row, maxColPenaltyIdx) < smallestCost
                             ? m.c(row, maxColPenaltyIdx)
                             : smallestCost;

        // Find the largest - supply or demand
        row -= 1;
        int maxAllocation = min(supply[row], demand[maxColPenaltyIdx]);
        // Deallocate supply, fill demand, and update allocation
        supply[row] -= maxAllocation;
        demand[maxColPenaltyIdx] -= maxAllocation;
        m(row, maxColPenaltyIdx).allocated = maxAllocation;

        // Crossout spent row or column
        if (supply[row] == 0) {
          u[row] = -INT_MAX;
          m.crossOutRow(row);
        }
        else {
          v[maxColPenaltyIdx] = -INT_MAX;
          m.crossOutColumn(maxColPenaltyIdx);
        }
      }
    } while (m.crossedOutColumns.size() - 1 != m.width &&
             m.crossedOutRows.size() - 1 != m.height);

    for (int i = 0; i < m.height; i++) {
      for (int j = 0; j < m.width; j++) {
        cout << "x" << i + 1 << j + 1 << ": " << m(i, j).allocated << endl;
      }
    }
  }
};
