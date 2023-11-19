#ifndef TRANSPORATION_MATRIX
#define TRANSPORATION_MATRIX

#include <ostream>
#include <vector>

using namespace std;

class cell {
public:
  int cost;
  int allocated;

  cell() : cost(0), allocated(0) {}
  cell(int cost, int allocated) : cost(cost), allocated(allocated) {}

  friend ostream &operator<<(ostream &out, const cell &c) {
    out << "["
        << "c:" << c.cost << ";"
        << "a:" << c.allocated << "]";
    return out;
  }
};

class TrasportationMatrix {
public:
  int height;
  int width;
  vector<vector<cell>> matrix;
  vector<int> demand;
  vector<int> supply;
  vector<int> u;
  vector<int> v;

  TrasportationMatrix(int height, int width) {
    this->matrix = vector<vector<cell>>(height, vector<cell>(width, cell()));
    this->demand = vector<int>(width, 0);
    this->supply = vector<int>(height, 0);
    this->v = vector<int>(width, 0);
    this->u = vector<int>(height, 0);
  }

  cell operator()(int row, int col) { return matrix[row][col]; }
  const cell &operator()(int row, int col) const { return matrix[row][col]; }

  friend ostream &operator<<(ostream &out, const TrasportationMatrix &m) {
    for (int i = 0; i < m.height; i++) {
      for (int j = 0; j < m.width; j++) {
        out << m(i, j);
        if (j != m.width - 1)
          out << " ";
      }
      out << endl;
    }
    return out;
  }
};

#endif // !TRANSPORATION_MATRIX
