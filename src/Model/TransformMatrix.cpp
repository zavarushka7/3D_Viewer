#include "Model.h"
using namespace s21;
TransformMatrix::TransformMatrix() : matrix_() {
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      matrix_[i][j] = (i == j) ? 1.0 : 0.0;
    }
  }
}

void TransformMatrix::setMatrixElement(int row, int col, double value) {
  matrix_[row][col] = value;
}

TransformMatrix TransformMatrix::operator*(const TransformMatrix& other) const {
  TransformMatrix result;

  result.matrix_[0][0] = matrix_[0][0] * other.matrix_[0][0] +
                         matrix_[0][1] * other.matrix_[1][0] +
                         matrix_[0][2] * other.matrix_[2][0] +
                         matrix_[0][3] * other.matrix_[3][0];

  result.matrix_[0][1] = matrix_[0][0] * other.matrix_[0][1] +
                         matrix_[0][1] * other.matrix_[1][1] +
                         matrix_[0][2] * other.matrix_[2][1] +
                         matrix_[0][3] * other.matrix_[3][1];

  result.matrix_[0][2] = matrix_[0][0] * other.matrix_[0][2] +
                         matrix_[0][1] * other.matrix_[1][2] +
                         matrix_[0][2] * other.matrix_[2][2] +
                         matrix_[0][3] * other.matrix_[3][2];

  result.matrix_[0][3] = matrix_[0][0] * other.matrix_[0][3] +
                         matrix_[0][1] * other.matrix_[1][3] +
                         matrix_[0][2] * other.matrix_[2][3] +
                         matrix_[0][3] * other.matrix_[3][3];

  result.matrix_[1][0] = matrix_[1][0] * other.matrix_[0][0] +
                         matrix_[1][1] * other.matrix_[1][0] +
                         matrix_[1][2] * other.matrix_[2][0] +
                         matrix_[1][3] * other.matrix_[3][0];

  result.matrix_[1][1] = matrix_[1][0] * other.matrix_[0][1] +
                         matrix_[1][1] * other.matrix_[1][1] +
                         matrix_[1][2] * other.matrix_[2][1] +
                         matrix_[1][3] * other.matrix_[3][1];

  result.matrix_[1][2] = matrix_[1][0] * other.matrix_[0][2] +
                         matrix_[1][1] * other.matrix_[1][2] +
                         matrix_[1][2] * other.matrix_[2][2] +
                         matrix_[1][3] * other.matrix_[3][2];

  result.matrix_[1][3] = matrix_[1][0] * other.matrix_[0][3] +
                         matrix_[1][1] * other.matrix_[1][3] +
                         matrix_[1][2] * other.matrix_[2][3] +
                         matrix_[1][3] * other.matrix_[3][3];

  result.matrix_[2][0] = matrix_[2][0] * other.matrix_[0][0] +
                         matrix_[2][1] * other.matrix_[1][0] +
                         matrix_[2][2] * other.matrix_[2][0] +
                         matrix_[2][3] * other.matrix_[3][0];

  result.matrix_[2][1] = matrix_[2][0] * other.matrix_[0][1] +
                         matrix_[2][1] * other.matrix_[1][1] +
                         matrix_[2][2] * other.matrix_[2][1] +
                         matrix_[2][3] * other.matrix_[3][1];

  result.matrix_[2][2] = matrix_[2][0] * other.matrix_[0][2] +
                         matrix_[2][1] * other.matrix_[1][2] +
                         matrix_[2][2] * other.matrix_[2][2] +
                         matrix_[2][3] * other.matrix_[3][2];

  result.matrix_[2][3] = matrix_[2][0] * other.matrix_[0][3] +
                         matrix_[2][1] * other.matrix_[1][3] +
                         matrix_[2][2] * other.matrix_[2][3] +
                         matrix_[2][3] * other.matrix_[3][3];

  result.matrix_[3][0] = matrix_[3][0] * other.matrix_[0][0] +
                         matrix_[3][1] * other.matrix_[1][0] +
                         matrix_[3][2] * other.matrix_[2][0] +
                         matrix_[3][3] * other.matrix_[3][0];

  result.matrix_[3][1] = matrix_[3][0] * other.matrix_[0][1] +
                         matrix_[3][1] * other.matrix_[1][1] +
                         matrix_[3][2] * other.matrix_[2][1] +
                         matrix_[3][3] * other.matrix_[3][1];

  result.matrix_[3][2] = matrix_[3][0] * other.matrix_[0][2] +
                         matrix_[3][1] * other.matrix_[1][2] +
                         matrix_[3][2] * other.matrix_[2][2] +
                         matrix_[3][3] * other.matrix_[3][2];

  result.matrix_[3][3] = matrix_[3][0] * other.matrix_[0][3] +
                         matrix_[3][1] * other.matrix_[1][3] +
                         matrix_[3][2] * other.matrix_[2][3] +
                         matrix_[3][3] * other.matrix_[3][3];

  return result;
}

ThreeDPoint TransformMatrix::TransformPoint(const ThreeDPoint& point) const {
  ThreeDPoint result(0, 0, 0);

  result.x = matrix_[0][0] * point.x + matrix_[0][1] * point.y +
             matrix_[0][2] * point.z + matrix_[0][3];
  result.y = matrix_[1][0] * point.x + matrix_[1][1] * point.y +
             matrix_[1][2] * point.z + matrix_[1][3];
  result.z = matrix_[2][0] * point.x + matrix_[2][1] * point.y +
             matrix_[2][2] * point.z + matrix_[2][3];

  return result;
}
float TransformMatrix::getMatrixElement(int row, int col) const {
  return matrix_[row][col];
}
