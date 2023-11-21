#ifndef RUSSELL
#define RUSSELL

#include "bfs_generator.cpp"
#include <cassert>
#include <climits>

typedef pair<int, int> coordinates;
typedef pair<coordinates, int> node;
const node faultyNode = {{-1, -1}, INT_MAX};

class Russell : public BFS_Generator {
public:
  void generate_bfs(TransportationMatrix m) {
    vector<vector<int>> w =
        vector<vector<int>>(m.height, vector<int>(m.width, 0));
    vector<int> &v = m.v;
    vector<int> &u = m.u;

    // Set highest costs for each row
    for (int row = 0; row < m.height; row++) {
      int largestRowCost = -1;
      for (int col = 0; col < m.width; col++)
        largestRowCost =
            m.c(row, col) > largestRowCost ? m.c(row, col) : largestRowCost;
      u[row] = largestRowCost;
    }

    // Set highest costs for each column
    for (int col = 0; col < m.width; col++) {
      int largestColCost = -1;
      for (int row = 0; row < m.height; row++)
        largestColCost =
            m.c(row, col) > largestColCost ? m.c(row, col) : largestColCost;
      v[col] = largestColCost;
    }

    // Repeat untill only one untouched cell remains
    do {
      // Calculate deltas
      for (int i = 0; i < m.height; i++)
        for (int j = 0; j < m.width; j++)
          if (!m.isCrossedOutCell(i, j))
            w[i][j] = m.c(i, j) - (u[i] + v[j]);

      // Find cell with the greatest negative value
      node gnv = faultyNode;
      for (int i = 0; i < m.height; i++)
        for (int j = 0; j < m.width; j++)
          if (!m.isCrossedOutCell(i, j))
            if (w[i][j] < gnv.second && w[i][j] < 0)
              gnv = {{i, j}, w[i][j]};

      if (gnv == faultyNode)
        break;

      // Allocate as many goods as possilble from supply or demand
      int &supply = m.supply[gnv.first.first];
      int &demand = m.demand[gnv.first.second];

      int maxToAllocate = supply < demand ? supply : demand;

      m(gnv.first.first, gnv.first.second).allocated = maxToAllocate;
      supply -= maxToAllocate;
      demand -= maxToAllocate;

      // Crossout spent supply row or demand column
      if (supply == 0)
        m.crossOutRow(gnv.first.first);
      else
        m.crossOutColumn(gnv.first.second);
    } while (m.crossedOutColumns.size() - 1 != m.width &&
             m.crossedOutRows.size() - 1 != m.height);

    cout << m << endl;

    for (int i = 0; i < m.height; i++) {
      for (int j = 0; j < m.width; j++) {
        cout << "x" << i + 1 << j + 1 << ": " << m(i, j).allocated << endl;
      }
    }
  }
};

#endif // !RUSSELL
