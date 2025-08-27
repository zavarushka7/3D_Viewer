#ifndef SCENEDRAWERBASE_H
#define SCENEDRAWERBASE_H

#include <QObject>

#include "../Controller/Facade.h"

namespace s21 {
// базовый класс для отрисовки сцены. реализация в QtSceneDrawer
class SceneDrawerBase : public QObject {
  Q_OBJECT
 public:
  virtual void DrawScene(Scene scene, const QColor& edgeColor) = 0;
  virtual ~SceneDrawerBase() = default;
};
}  // namespace s21

#endif