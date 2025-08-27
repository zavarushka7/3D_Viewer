#include "Model.h"

using namespace s21;

ThreeDPoint Vertex::GetPosition() const { return position_; }
void Vertex::setPosition(const ThreeDPoint& position) { position_ = position; }

bool Vertex::operator<(const Vertex& other) const {
  return position_ < other.position_;
}
bool Vertex::operator>(const Vertex& other) const {
  return position_ > other.position_;
}
