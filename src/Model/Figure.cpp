#include "Model.h"

using namespace s21;

void Figure::Transform() {
  TransformMatrix matrixFinale;
  matrixFinale =
      TransformMatrixBuilder::CreateMoveMatrix(move_[0], move_[1], move_[2]) *
      TransformMatrixBuilder::CreateRotationMatrix(rotate_[0], rotate_[1],
                                                   rotate_[2]) *
      TransformMatrixBuilder::CreateScaleMatrix(scale_[0], scale_[1],
                                                scale_[2]);
  for (size_t i = 0; i < dataVertices_.size(); i++) {
    vertices_[i]->setPosition(
        matrixFinale.TransformPoint(dataVertices_[i].GetPosition()));
  }
}

void Figure::setEdges(const Edge& edge) {
  edges_.emplace_back(std::move(edge));
}

void Figure::setVertices(const shared_ptr<Vertex>& vertex) {
  vertices_.emplace_back(std::move(vertex));
}
void Figure::setDataVertices(const Vertex& vertex) {
  dataVertices_.emplace_back(std::move(vertex));
}

vector<Edge> Figure::GetEdges() { return edges_; }

vector<shared_ptr<Vertex>> Figure::GetVertices() { return vertices_; }

void Figure::setRotate(float x, float y, float z) {
  rotate_[0] = x;
  rotate_[1] = y;
  rotate_[2] = z;
}
void Figure::setMove(float x, float y, float z) {
  move_[0] = x;
  move_[1] = y;
  move_[2] = z;
}
void Figure::setScale(float x) {
  scale_[0] = x;
  scale_[1] = x;
  scale_[2] = x;
}
