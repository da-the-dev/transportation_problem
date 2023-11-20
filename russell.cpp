#ifndef RUSSELL
#define RUSSELL

#include "bfs_generator.cpp"
#include <cassert>
#include <climits>

typedef pair<int, int> coordinates;
typedef pair<coordinates, int> node;
const node faultyNode = {{-1, -1}, INT_MAX};

class Russell : public BFS_Generator {
  void generate_bfs(TransportationMatrix m) {
    vector<vector<int>> w =
        vector<vector<int>>(m.height, vector<int>(m.width, 0));
    vector<int> &v = m.v;
    vector<int> &u = m.u;

    // Set highest costs for each row
    for (int i; i < m.height; i++) {
      int largestRowCost = -1;
      for (int j; j < m.width; j++)
        largestRowCost =
            m.c(i, j) > largestRowCost ? m.c(i, j) : largestRowCost;
      u[i] = largestRowCost;
    }

    // Set highest costs for each column
    for (int i; i < m.width; i++) {
      int largestColCost = -1;
      for (int j; j < m.height; j++)
        largestColCost =
            m.c(i, j) > largestColCost ? m.c(i, j) : largestColCost;
      v[i] = largestColCost;
    }

    // Repeat untill only one untouched cell remains
    do {
      // Calculate deltas
      for (int i = 0; i < m.height; i++)
        for (int j = 0; j < m.width; j++)
          w[i][j] = m.c(i, j) - (u[i] + v[j]);

      // Find cell with the greatest negative value
      node gnv = faultyNode;
      for (int i = 0; i < m.height; i++)
        for (int j = 0; j < m.width; j++)
          if (w[i][j] < gnv.second && w[i][j] < 0)
            gnv = {{i, j}, w[i][j]};

      assert(gnv == faultyNode);

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
  }
};

#endif // !RUSSELL
