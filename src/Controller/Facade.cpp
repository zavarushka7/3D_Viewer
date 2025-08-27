#include "Facade.h"

using namespace s21;

void Facade::LoadScene(string path, NormalizationParameters params) {
  Scene scene = fileReader_->ReadScene(path, params);
  *scene_ = scene;
  SceneInfo info;
  info.vertex_count = 0;
  info.edge_count = 0;

  for (auto& figure : scene.GetFigures()) {
    info.vertex_count += figure->GetVertices().size();
    info.edge_count += figure->GetEdges().size();
  }
  info.file_name = path;

  emit sceneLoaded(info);  // создает сигнал о том, что сцена загружена
}

// слот обрабатывает сигнал loadSceneRequested от MainWindow
void Facade::onLoadSceneRequested(const QString& path,
                                  NormalizationParameters params) {
  LoadScene(path.toStdString(), params);
}

void Facade::MoveScene(double x, double y, double z) {
  for (auto& figure : scene_->GetFigures()) {
    figure->setMove(x, y, z);
    figure->Transform();
  }
}
void Facade::RotateScene(double x, double y, double z) {
  for (auto& figure : scene_->GetFigures()) {
    figure->setRotate(x, y, z);
    figure->Transform();
  }
}
void Facade::ScaleScene(double x) {
  for (auto& figure : scene_->GetFigures()) {
    figure->setScale(x);
    figure->Transform();
  }
}

Scene* Facade::getScene() { return scene_; }
