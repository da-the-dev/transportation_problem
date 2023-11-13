#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
using namespace std;

class Matrix {
public:
  int width;
  double **matrix;
  int height;
  Matrix(int height, int width);

  double& operator()(int row, int col);
  const double& operator()(int row, int col) const; // 
  friend ostream &operator<<(ostream &out, const Matrix &m);
  friend istream &operator>>(istream &in, Matrix &m);

  Matrix operator+(const Matrix &matrixEntity) const;
  Matrix operator-(const Matrix &matrixEntity) const;
  Matrix operator*(const Matrix &matrixEntity) const;

  virtual void operator=(const Matrix &matrixEntity);

  void permute(int first, int second);
  void rowSubtract(int first, int second, double coeff);
  double getValue(int i, int j);
};

#endif // !MATRIX_H
