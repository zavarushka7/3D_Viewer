#ifndef QTSCENEDRAWE_H
#define QTSCENEDRAWE_H

#include <QApplication>
#include <QBuffer>
#include <QByteArray>
#include <QFile>
#include <QFileInfo>
#include <QOpenGLFunctions>
#include <QPixmap>
#include <QScreen>
#include <QWidget>

#include "SceneDrawerBase.h"
#include "myglwidget.h"
namespace s21 {
class QTSceneDrawer : public SceneDrawerBase, protected QOpenGLFunctions {
  Q_OBJECT
 public:
  explicit QTSceneDrawer(){};
  void DrawScene(Scene scene, const QColor& edgeColor = Qt::white) override;

  QByteArray getScreenshot(QWidget* widget, const char* format,
                           int quality = -1);
};
}  // namespace s21

#endif