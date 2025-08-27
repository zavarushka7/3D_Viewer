#ifndef MODEL_H
#define MODEL_H
#include <algorithm>
#include <array>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <limits>
#include <memory>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

namespace s21 {

// структура для передачи информации о загруженной сцене
struct SceneInfo {
  int vertex_count;
  int edge_count;
  string file_name;
};

class ThreeDPoint {
 public:
  ThreeDPoint(float x, float y, float z) : x(x), y(y), z(z) {}
  float x;
  float y;
  float z;
  bool operator==(const ThreeDPoint& other) const;
  bool operator<(const ThreeDPoint& other) const;
  bool operator>(const ThreeDPoint& other) const;
};

class TransformMatrix {
 public:
  TransformMatrix();
  TransformMatrix operator*(const TransformMatrix& other) const;
  ThreeDPoint TransformPoint(const ThreeDPoint& point) const;

  void setMatrixElement(int row, int col, double value);
  float getMatrixElement(int row, int col) const;

 private:
  std::array<std::array<float, 4>, 4> matrix_;
};

class NormalizationParameters {
 public:
  float minX;
  float maxX;
  float minY;
  float maxY;
  float minZ;
  float maxZ;
};

// базовый класс для обьектов сцены
class SceneObject {
 public:
  virtual ~SceneObject() = default;
};

class Vertex : public SceneObject {
 public:
  Vertex(const ThreeDPoint& position) : position_(position) {}
  ThreeDPoint GetPosition() const;
  void Transform(TransformMatrix matrix);
  void setPosition(const ThreeDPoint& position);
  bool operator==(const Vertex& other) const {
    return position_.x == other.position_.x &&
           position_.y == other.position_.y && position_.z == other.position_.z;
  }
  bool operator!=(const Vertex& other) const { return !(*this == other); }
  bool operator<(const Vertex& other) const;
  bool operator>(const Vertex& other) const;

 private:
  ThreeDPoint position_;
};

class Edge {
 public:
  Vertex* GetBegin() const;
  Vertex* GetEnd() const;

  void setBegin(Vertex* v);
  void setEnd(Vertex* v);

  bool operator==(const Edge& other) const;
  bool operator<(const Edge& other) const;
  bool operator>(const Edge& other) const;

 private:
  Vertex* begin_;
  Vertex* end_;
};

class Figure : public SceneObject {
 public:
  Figure() {
    vertices_.reserve(1000000);
    dataVertices_.reserve(1000000);
    rotate_[0] = 0;
    rotate_[1] = 0;
    rotate_[2] = 0;
    move_[0] = 0;
    move_[1] = 0;
    move_[2] = 0;
    scale_[0] = 1;
    scale_[1] = 1;
    scale_[2] = 1;
  }
  vector<shared_ptr<Vertex>> GetVertices();
  vector<Edge> GetEdges();
  void Transform();
  void setEdges(const Edge& edge);
  void setVertices(const shared_ptr<Vertex>& vertex);
  void setDataVertices(const Vertex& vertex);
  void setRotate(float x, float y, float z);
  void setMove(float x, float y, float z);
  void setScale(float x);
  vector<Edge> GetEdges() const { return edges_; }
  vector<shared_ptr<Vertex>> GetVertices() const { return vertices_; }
  vector<Vertex> GetDataVertices() const { return dataVertices_; }

 private:
  vector<shared_ptr<Vertex>> vertices_;
  vector<Vertex> dataVertices_;
  vector<Edge> edges_;

 public:
  array<float, 3> rotate_;
  array<float, 3> move_;
  array<float, 3> scale_;
};

class Scene {
 public:
  const std::vector<std::shared_ptr<Figure>>& GetFigures() const {
    return figures_;
  }
  void TransformFigures(TransformMatrix);

  void setFigures(const std::shared_ptr<Figure>& figure) {
    figures_.push_back(figure);
  }

 private:
  std::vector<std::shared_ptr<Figure>> figures_;
};

class BaseFileReader {
 public:
  // абстрактный метод должен быть реализован в наследниках
  virtual Scene ReadScene(string path,
                          NormalizationParameters normalization_parameters) = 0;
  virtual ~BaseFileReader() = default;
};

// конкретная реализация BaseFileReader для загрузки сцены
class FileReader : public BaseFileReader {
 public:
  Scene ReadScene(string path,
                  NormalizationParameters normalization_parameters);
};

// паттер строитель
class TransformMatrixBuilder {
 public:
  static TransformMatrix CreateRotationMatrix(double x, double y, double z);
  static TransformMatrix CreateMoveMatrix(double x, double y, double z);
  static TransformMatrix CreateScaleMatrix(double x, double y, double z);
};

}  // namespace s21

#endif
