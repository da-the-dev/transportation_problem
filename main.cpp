#include <iostream>
#include "matrix.h"

#define SOURCES 3
#define DEST 4

using namespace std;

bool isBalanced(Matrix S, Matrix D) {
    double sumS = 0;
    double sumD = 0;
    for (int i = 0; i < SOURCES; i++) {
        sumS += S.matrix[i][0];
    }

    for (int i = 0; i < DEST; i++) {
        sumD += D.matrix[i][0];
    }

    if (sumD != sumS) {
        cout << "The problem is not balanced!";
        return false;
    }

    return true;
}

Matrix createTable (Matrix S, Matrix C, Matrix D) {
    Matrix A(SOURCES + 1, DEST + 1);
    for (int i = 0; i < SOURCES; i++) {
        for (int j = 0; j < DEST; j++) {
            A.matrix[i][j] = C.matrix[i][j];
        }
        A.matrix[i][DEST] = S.matrix[i][0];
    }
    for (int j = 0; j < DEST; j++) {
        A.matrix[SOURCES][j] = D.matrix[j][0];
    }

    return A;
}

void northwest (Matrix S, Matrix C, Matrix D) {

    if (!(isBalanced(S, D))) {
        return;
    }

    Matrix A = createTable(S, C, D);
    cout << "Input parameter table:" << endl;
    cout << A;

    int x = 0;
    int y = 0;
    double answer = 0;

    while (x <= SOURCES && y <= DEST) {
        double supply = A.matrix[x][DEST];
        double demand = A.matrix[SOURCES][y];

        if (demand == 0) {
            y++;
        } else if (supply == 0) {
            x++;
        } else {
            double t = min(demand, supply);
            A.matrix[x][DEST] -= t;
            A.matrix[SOURCES][y] -= t;
            answer += A.matrix[x][y] * t;
        }
    }

    for (int i = 0; i < SOURCES; i++) {
        if (A.matrix[i][DEST] != 0) {
            cout << "The method is not applicable!";
            return;
        }
    }

    for (int i = 0; i < DEST; i++) {
        if (A.matrix[SOURCES][i] != 0) {
            cout << "The method is not applicable!";
            return;
        }
    }

    cout << "Answer: " << answer;
}

int main() {
    Matrix S(SOURCES, 1);
    cin >> S;

    Matrix C(SOURCES, DEST);
    cin >> C;

    Matrix D(DEST, 1);
    cin >> D;

    northwest(S, C, D);

    return 0;
}
