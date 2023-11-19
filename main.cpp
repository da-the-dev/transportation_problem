#include <iostream>
#include "transportation_matrix.cpp"

using namespace std;

int main() {
  int height, width;
  cin >> height >> width;
  TransportationMatrix matrix = TransportationMatrix(height, width);

  cin >> matrix; 

  cout << matrix;
}
