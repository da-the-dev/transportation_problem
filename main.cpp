#include <iostream>
#include "transportation_matrix.cpp"

using namespace std;

int main() {
  int height, width;
  cin >> height >> width;
  TrasportationMatrix matrix = TrasportationMatrix(height, width);

  cin >> matrix; 

  cout << matrix;
}
