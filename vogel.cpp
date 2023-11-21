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

pair<double, int> max_element_in_array (double arr[], int n) {
    double maxx = -1;
    int ind = -1;
    for (int i = 0; i < n; i++) {
        if (arr[i] > maxx && arr[i] != INT_MAX) {
            maxx = arr[i];
            ind = i;
        }
    }
    return pair<double, int>(maxx, ind);
}

pair<double, int> getByRows(Matrix A) {
    double rowDiff[SOURCES];
    double min1 = INT_MAX;
    double min2 = INT_MAX;
    int ind;
    for (int i = 0; i < SOURCES; i++) {
        for(int j = 0; j < DEST; j++) {
            if (A.matrix[i][j] < min1 && A.matrix[i][j] != -1) {
                min1 = A.matrix[i][j];
                ind = j;
            }
        }
        for(int j = 0; j < DEST; j++) {
            if (A.matrix[i][j] < min2 && j != ind && A.matrix[i][j] != -1) {
                min2 = A.matrix[i][j];
            }
        }
        if (min1 != INT_MAX && min2 != INT_MAX) {
            rowDiff[i] = min2 - min1;
        } else {
            rowDiff[i] = INT_MAX;
        }
        min1 = INT_MAX;
        min2 = INT_MAX;
    }
    return max_element_in_array(rowDiff, SOURCES);
}

pair<double, int> getByCols(Matrix A) {
    double colDiff[DEST];
    double min1 = INT_MAX;
    double min2 = INT_MAX;
    int ind;
    for (int j = 0; j < DEST; j++) {
        for (int i = 0; i < SOURCES; i++) {
            if (A.matrix[i][j] < min1 && A.matrix[i][j] != -1) {
                min1 = A.matrix[i][j];
                ind = i;
            }
        }
        for (int i = 0; i < SOURCES; i++) {
            if (A.matrix[i][j] < min2 && i != ind && A.matrix[i][j] != -1) {
                min2 = A.matrix[i][j];
            }
        }
        if (min1 != INT_MAX && min2 != INT_MAX) {
            colDiff[j] = min2 - min1;
        } else {
            colDiff[j] = INT_MAX;
        }

        min1 = INT_MAX;
        min2 = INT_MAX;
    }
    return max_element_in_array(colDiff, DEST);
}



void vogel_approximation(Matrix S, Matrix C, Matrix D) {
    if (!(isBalanced(S, D))) {
        return;
    }
    Matrix A = createTable(S, C, D);
    cout << "Input parameter table:" << endl;
    cout << A;

    double answer = 0;
    while (true) {
        pair<double, int> maxRowPenalty = getByRows(A);
        pair<double, int> maxColPenalty = getByCols(A);

        if (maxRowPenalty.first == -1 && maxColPenalty.first == -1) {
            break;
        }

        if (maxRowPenalty.first >= maxColPenalty.first) {
            int row = maxRowPenalty.second;
            int minColIndex = -1;
            double minVal = INT_MAX;

            for (int j = 0; j < DEST; j++) {
                if (A.matrix[row][j] < minVal && A.matrix[row][j] != -1) {
                    minVal = A.matrix[row][j];
                    minColIndex = j;
                }
            }

            if (minColIndex != -1) {
                double units = min(S.matrix[row][0], D.matrix[minColIndex][0]);
                answer += units * A.matrix[row][minColIndex];
                S.matrix[row][0] -= units;
                D.matrix[minColIndex][0] -= units;
                A.matrix[row][minColIndex] = -1;
            }
        } else {
            int col = maxColPenalty.second;
            int minRowIndex = -1;
            double minVal = INT_MAX;

            for (int i = 0; i < SOURCES; i++) {
                if (A.matrix[i][col] < minVal && A.matrix[i][col] != -1) {
                    minVal = A.matrix[i][col];
                    minRowIndex = i;
                }
            }

            if (minRowIndex != -1) {
                double units = min(S.matrix[minRowIndex][0], D.matrix[col][0]);
                answer += units * A.matrix[minRowIndex][col];
                S.matrix[minRowIndex][0] -= units;
                D.matrix[col][0] -= units;
                A.matrix[minRowIndex][col] = -1;
            }
        }
    }

    cout << "Answer: " << answer << endl;
}

int main() {
    Matrix S(SOURCES, 1);
    cin >> S;

    Matrix C(SOURCES, DEST);
    cin >> C;

    Matrix D(DEST, 1);
    cin >> D;

    vogel_approximation(S, C, D);

    
    return 0;
}