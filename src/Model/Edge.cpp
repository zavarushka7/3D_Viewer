#include "Model.h"
using namespace s21;

void Edge::setBegin(Vertex* v) { begin_ = v; }

void Edge::setEnd(Vertex* v) { end_ = v; }

Vertex* Edge::GetBegin() const { return begin_; }
Vertex* Edge::GetEnd() const { return end_; }

bool Edge::operator<(const Edge& other) const {
  if (*begin_ != *other.begin_) {
    return *begin_ < *other.begin_;
  }
  return *end_ < *other.end_;
}

bool Edge::operator>(const Edge& other) const {
  if (*begin_ != *other.begin_) {
    return *begin_ > *other.begin_;
  }
  return *end_ > *other.end_;
}

bool Edge::operator==(const Edge& other) const {
  return (*begin_ == *other.begin_ && *end_ == *other.end_);
}