#ifndef TRANSPORTATION_MATRIX
#define TRANSPORTATION_MATRIX

#include <iostream>
#include <set>
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

  friend istream &operator>>(istream &in, cell &c) {
    in >> c.cost;
    return in;
  }
};

class TransportationMatrix {
private:
  vector<int> cleanDemand;
  vector<int> cleanSupply;

public:
  int height;
  int width;
  vector<vector<cell>> matrix;
  vector<int> demand;
  vector<int> supply;
  vector<int> u;
  vector<int> v;
  set<int> crossedOutRows = set<int>();
  set<int> crossedOutColumns = set<int>();

  TransportationMatrix(int height, int width) : height(height), width(width) {
    this->matrix = vector<vector<cell>>(height, vector<cell>(width, cell()));
    this->demand = vector<int>(width, 0);
    this->supply = vector<int>(height, 0);
    this->cleanDemand = vector<int>(width, 0);
    this->cleanSupply = vector<int>(height, 0);
    this->v = vector<int>(width, 0);
    this->u = vector<int>(height, 0);
  }

  cell &operator()(int row, int col) { return matrix[row][col]; }
  const cell &operator()(int row, int col) const { return matrix[row][col]; }

  friend ostream &operator<<(ostream &out, const TransportationMatrix &m) {
    for (int i = 0; i < m.height; i++) {
      for (int j = 0; j < m.width; j++) {
        out << m(i, j);
        if (j != m.width - 1)
          out << " ";
      }
      out << " | " << m.cleanSupply[i] << endl;
    }
    for (int i = 0; i < m.width; i++)
      out << m.cleanDemand[i] << " ";
    cout << endl;
    return out;
  }

  friend istream &operator>>(istream &in, TransportationMatrix &m) {
    for (int i = 0; i < m.height; i++)
      for (int j = 0; j < m.width; j++) {
        in >> m(i, j);
      }
    return in;
  }

  void crossOutRow(int rowIdx) { crossedOutRows.insert(rowIdx); }
  bool isCrossedRow(int rowIdx) {return crossedOutRows.find(rowIdx) != crossedOutRows.end();}

  void crossOutColumn(int colIdx) { crossedOutColumns.insert(colIdx); }
  bool isCrossedColumn(int colIdx) {return crossedOutColumns.find(colIdx) != crossedOutColumns.end();}

  bool isCrossedOutCell(int i, int j) {return isCrossedRow(i) || isCrossedColumn(j);}

  void resetCrossings() {
    this->crossedOutRows = set<int>();
    this->crossedOutColumns = set<int>();
  }

  void enter_supply(istream &in) {
     for (int i = 0; i < height; i++)
      in >> supply[i];
    cleanSupply = supply;
  }

  void enter_demand(istream &in) {
     for (int i = 0; i < width; i++)
      in >> demand[i];
    cleanDemand = demand;
  }

  int c(int i, int j) const { return (*this)(i, j).cost; }
};
#endif // !TRANSPORTATION_MATRIX
