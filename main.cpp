#include <iostream>
#include "transportation_matrix.cpp"
#include "northwest.cpp"
#include "russell.cpp"
#include "vogel.cpp"

using namespace std;

int main() {
  int height, width;
  cin >> height >> width;
  TransportationMatrix matrix = TransportationMatrix(height, width);

  cin >> matrix; 
  matrix.enter_supply(cin);
  matrix.enter_demand(cin);

  cout << "Northwest" << endl;
  Northwest northwest = Northwest();
  northwest.generate_bfs(matrix);

  cout << "Russell's" << endl;
  Russell russell = Russell();
  russell.generate_bfs(matrix);

  cout << "Vogel's" << endl;
  Vogels vogel = Vogels();
  vogel.generate_bfs(matrix);
}
