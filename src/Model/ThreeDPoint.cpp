#include "Model.h"
using namespace s21;
bool ThreeDPoint::operator==(const ThreeDPoint& other) const {
  return x == other.x && y == other.y && z == other.z;
}

bool ThreeDPoint::operator<(const ThreeDPoint& other) const {
  if (x != other.x) {
    return x < other.x;
  }
  if (y != other.y) {
    return y < other.y;
  }
  if (z != other.z) {
    return z < other.z;
  }
  return false;
}
bool ThreeDPoint::operator>(const ThreeDPoint& other) const {
  if (x != other.x) {
    return x > other.x;
  }
  if (y != other.y) {
    return y > other.y;
  }
  if (z != other.z) {
    return z > other.z;
  }
  return false;
}