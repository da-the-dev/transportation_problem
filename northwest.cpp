#ifndef NORTHWEST
#define NORTHWEST

#include "bfs_generator.cpp"
#include <iostream>

class Northwest : public BFS_Generator {
public:
  void generate_bfs(TransportationMatrix matrix) {
    int x = 0, y = 0;
    vector<int> answer = vector<int>(matrix.height * matrix.width, 0);

    while (x <= matrix.width && y <= matrix.height) {
      int &supply = matrix.supply[x];
      int &demand = matrix.demand[y];

      if (demand == 0)
        y++;
      else if (supply == 0)
        x++;
      else {
        int t = min(demand, supply);
        supply -= t;
        demand -= t;
        matrix(x, y).allocated += t;
      }
    }

    cout << matrix << endl;

    for (int i = 0; i < matrix.height; i++) {
      for (int j = 0; j < matrix.width; j++) {
        cout << "x" << i + 1 << j + 1 << ": " << matrix(i, j).allocated << endl;
      }
    }

    // for (int i = 0; i < SOURCES; i++) {
    //   if (A.matrix[i][DEST] != 0) {
    //     cout << "The method is not applicable!";
    //     return;
    //   }
    // }

    // for (int i = 0; i < DEST; i++) {
    //   if (A.matrix[SOURCES][i] != 0) {
    //     cout << "The method is not applicable!";
    //     return;
    //   }
    // }
    //
  }

  //   Matrix createTable(Matrix S, Matrix C, Matrix D) {
  //     Matrix A(SOURCES + 1, DEST + 1);
  //     for (int i = 0; i < SOURCES; i++) {
  //       for (int j = 0; j < DEST; j++) {
  //         A.matrix[i][j] = C.matrix[i][j];
  //       }
  //       A.matrix[i][DEST] = S.matrix[i][0];
  //     }
  //     for (int j = 0; j < DEST; j++) {
  //       A.matrix[SOURCES][j] = D.matrix[j][0];
  //     }

  //     return A;
  //   }

  //   void northwest(Matrix S, Matrix C, Matrix D) {

  //     if (!(isBalanced(S, D))) {
  //       return;
  //     }

  //     Matrix A = createTable(S, C, D);
  //     cout << "Input parameter table:" << endl;
  //     cout << A;

  //     int x = 0;
  //     int y = 0;
  //     double answer = 0;

  //     while (x <= SOURCES && y <= DEST) {
  //       double supply = A.matrix[x][DEST];
  //       double demand = A.matrix[SOURCES][y];

  //       if (demand == 0) {
  //         y++;
  //       } else if (supply == 0) {
  //         x++;
  //       } else {
  //         double t = min(demand, supply);
  //         A.matrix[x][DEST] -= t;
  //         A.matrix[SOURCES][y] -= t;
  //         answer += A.matrix[x][y] * t;
  //       }
  //     }

  //     for (int i = 0; i < SOURCES; i++) {
  //       if (A.matrix[i][DEST] != 0) {
  //         cout << "The method is not applicable!";
  //         return;
  //       }
  //     }

  //     for (int i = 0; i < DEST; i++) {
  //       if (A.matrix[SOURCES][i] != 0) {
  //         cout << "The method is not applicable!";
  //         return;
  //       }
  //     }

  //     cout << "Answer: " << answer;
  //   }
  // }
};

#endif // !NORTHWEST
