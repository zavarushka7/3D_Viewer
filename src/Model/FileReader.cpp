#include "Model.h"
using namespace s21;
using namespace std;

Scene FileReader::ReadScene(string path, NormalizationParameters params) {
  Scene scene;
  Figure figure;
  vector<shared_ptr<Vertex>> vertices;
  vertices.reserve(1000000);
  ifstream in(path);
  string line;
  params.minX = std::numeric_limits<float>::max();
  params.minY = std::numeric_limits<float>::max();
  params.minZ = std::numeric_limits<float>::max();
  params.maxX = std::numeric_limits<float>::lowest();
  params.maxY = std::numeric_limits<float>::lowest();
  params.maxZ = std::numeric_limits<float>::lowest();
  if (in.is_open()) {
    set<Edge> edges_;
    while (getline(in, line)) {
      if (line.empty()) continue;
      if (line[0] == 'v' && line.size() > 1 && line[1] == ' ') {
        istringstream iss(line.substr(1));
        array<double, 3> ver;
        bool valid = true;
        for (int i = 0; i < 3; ++i) {
          if (!(iss >> ver[i])) {
            valid = false;
            break;
          }
        }
        if (valid) {
          auto vertex =
              make_shared<Vertex>(ThreeDPoint(ver[0], ver[1], ver[2]));
          vertices.emplace_back(std::move(vertex));
          params.minX = std::min(params.minX, (float)ver[0]);
          params.maxX = std::max(params.maxX, (float)ver[0]);
          params.minY = std::min(params.minY, (float)ver[1]);
          params.maxY = std::max(params.maxY, (float)ver[1]);
          params.minZ = std::min(params.minZ, (float)ver[2]);
          params.maxZ = std::max(params.maxZ, (float)ver[2]);
        }

      } else if (line[0] == 'f' && line.size() > 1 && line[1] == ' ') {
        for (size_t i = 0; i < line.length(); ++i) {
          if (line[i] == '/') {
            size_t j = i;
            while (j < line.length() && line[j] != ' ') {
              line[j] = ' ';
              j++;
            }
            i = j - 1;
          }
        }

        istringstream iss(line.substr(1));
        vector<int> indices;
        indices.reserve(5);
        int number;
        while (iss >> number) {
          int idx = number - 1;
          if (idx >= 0 && static_cast<size_t>(idx) < vertices.size()) {
            indices.push_back(idx);
          }
        }

        if (indices.size() >= 2) {
          for (size_t i = 0; i < indices.size(); ++i) {
            Edge e;
            size_t next = (i + 1) % indices.size();
            size_t j = std::min(indices[i], indices[next]);
            size_t k = std::max(indices[i], indices[next]);
            e.setBegin(vertices[j].get());
            e.setEnd(vertices[k].get());
            edges_.emplace(std::move(e));
          }
        }
      }
    }

    in.clear();
    in.seekg(0);
    for (auto& e : edges_) {
      figure.setEdges(e);
    }

    double centrX = params.minX + (params.maxX - params.minX) / 2;
    double centrY = params.minY + (params.maxY - params.minY) / 2;
    double centrZ = params.minZ + (params.maxZ - params.minZ) / 2;

    for (size_t i = 0; i < vertices.size(); i++) {
      ThreeDPoint dpoint(vertices[i]->GetPosition().x - centrX,
                         vertices[i]->GetPosition().y - centrY,
                         vertices[i]->GetPosition().z - centrZ);

      vertices[i]->setPosition(dpoint);
      figure.setVertices(vertices[i]);
      figure.setDataVertices(dpoint);
    }
    if (!figure.GetVertices().empty()) {
      scene.setFigures(std::make_shared<s21::Figure>(figure));
    }
    in.close();
  }

  return scene;
}
