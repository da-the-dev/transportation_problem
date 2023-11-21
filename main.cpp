#include <iostream>
#include "transportation_matrix.cpp"
#include "northwest.cpp"

using namespace std;

int main() {
  int height, width;
  cin >> height >> width;
  TransportationMatrix matrix = TransportationMatrix(height, width);

  cin >> matrix; 
  matrix.enter_supply(cin);
  matrix.enter_demand(cin);

  Northwest northwest = Northwest();
  northwest.generate_bfs(matrix);
}
