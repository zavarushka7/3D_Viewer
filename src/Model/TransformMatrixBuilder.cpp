#include "Model.h"
using namespace s21;
TransformMatrix TransformMatrixBuilder::CreateRotationMatrix(double x, double y,
                                                             double z) {
  TransformMatrix final;

  double radX = x * M_PI / 180.0;
  double radY = y * M_PI / 180.0;
  double radZ = z * M_PI / 180.0;

  TransformMatrix rotationX;
  rotationX.setMatrixElement(0, 0, 1.0f);  // Добавил f для float
  rotationX.setMatrixElement(0, 1, 0.0f);
  rotationX.setMatrixElement(0, 2, 0.0f);
  rotationX.setMatrixElement(0, 3, 0.0f);
  rotationX.setMatrixElement(1, 0, 0.0f);
  rotationX.setMatrixElement(1, 1, cos(radX));
  rotationX.setMatrixElement(1, 2, -sin(radX));
  rotationX.setMatrixElement(1, 3, 0.0f);
  rotationX.setMatrixElement(2, 0, 0.0f);
  rotationX.setMatrixElement(2, 1, sin(radX));
  rotationX.setMatrixElement(2, 2, cos(radX));
  rotationX.setMatrixElement(2, 3, 0.0f);
  rotationX.setMatrixElement(3, 0, 0.0f);
  rotationX.setMatrixElement(3, 1, 0.0f);
  rotationX.setMatrixElement(3, 2, 0.0f);
  rotationX.setMatrixElement(3, 3, 1.0f);

  TransformMatrix rotationY;
  rotationY.setMatrixElement(0, 0, cos(radY));
  rotationY.setMatrixElement(0, 1, 0.0f);
  rotationY.setMatrixElement(0, 2, sin(radY));
  rotationY.setMatrixElement(0, 3, 0.0f);
  rotationY.setMatrixElement(1, 0, 0.0f);
  rotationY.setMatrixElement(1, 1, 1.0f);
  rotationY.setMatrixElement(1, 2, 0.0f);
  rotationY.setMatrixElement(1, 3, 0.0f);
  rotationY.setMatrixElement(2, 0, -sin(radY));
  rotationY.setMatrixElement(2, 1, 0.0f);
  rotationY.setMatrixElement(2, 2, cos(radY));
  rotationY.setMatrixElement(2, 3, 0.0f);
  rotationY.setMatrixElement(3, 0, 0.0f);
  rotationY.setMatrixElement(3, 1, 0.0f);
  rotationY.setMatrixElement(3, 2, 0.0f);
  rotationY.setMatrixElement(3, 3, 1.0f);

  TransformMatrix rotationZ;
  rotationZ.setMatrixElement(0, 0, cos(radZ));
  rotationZ.setMatrixElement(0, 1, -sin(radZ));
  rotationZ.setMatrixElement(0, 2, 0.0f);
  rotationZ.setMatrixElement(0, 3, 0.0f);
  rotationZ.setMatrixElement(1, 0, sin(radZ));
  rotationZ.setMatrixElement(1, 1, cos(radZ));
  rotationZ.setMatrixElement(1, 2, 0.0f);
  rotationZ.setMatrixElement(1, 3, 0.0f);
  rotationZ.setMatrixElement(2, 0, 0.0f);
  rotationZ.setMatrixElement(2, 1, 0.0f);
  rotationZ.setMatrixElement(2, 2, 1.0f);
  rotationZ.setMatrixElement(2, 3, 0.0f);
  rotationZ.setMatrixElement(3, 0, 0.0f);
  rotationZ.setMatrixElement(3, 1, 0.0f);
  rotationZ.setMatrixElement(3, 2, 0.0f);
  rotationZ.setMatrixElement(3, 3, 1.0f);

  final = rotationZ * rotationY * rotationX;
  return final;
}

TransformMatrix TransformMatrixBuilder::CreateMoveMatrix(double x, double y,
                                                         double z) {
  TransformMatrix final;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      final.setMatrixElement(i, j, (i == j) ? 1.0f : 0.0f);
    }
  }
  final.setMatrixElement(0, 3,
                         static_cast<float>(x));  // Явное приведение к float
  final.setMatrixElement(1, 3, static_cast<float>(y));
  final.setMatrixElement(2, 3, static_cast<float>(z));
  return final;
}

TransformMatrix TransformMatrixBuilder::CreateScaleMatrix(double x, double y,
                                                          double z) {
  TransformMatrix final;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      final.setMatrixElement(i, j, 0.0f);
    }
  }
  final.setMatrixElement(0, 0,
                         static_cast<float>(x));  // Явное приведение к float
  final.setMatrixElement(1, 1, static_cast<float>(y));
  final.setMatrixElement(2, 2, static_cast<float>(z));
  final.setMatrixElement(3, 3, 1.0f);

  return final;
}