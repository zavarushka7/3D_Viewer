#include "QTSceneDrawer.h"

using namespace s21;

void QTSceneDrawer::DrawScene(Scene scene, const QColor& edgeColor) {
  initializeOpenGLFunctions();
  glBegin(GL_LINES);
  glColor3f(edgeColor.redF(), edgeColor.greenF(), edgeColor.blueF());

  for (auto& figure : scene.GetFigures()) {
    for (auto& edge : figure->GetEdges()) {
      auto v1 = edge.GetBegin();
      auto v2 = edge.GetEnd();
      if (v1 && v2) {
        ThreeDPoint p1 = v1->GetPosition();
        ThreeDPoint p2 = v2->GetPosition();
        glVertex3f(p1.x, p1.y, p1.z);
        glVertex3f(p2.x, p2.y, p2.z);
      }
    }
  }
  glEnd();
}

QByteArray QTSceneDrawer::getScreenshot(QWidget* widget, const char* format,
                                        int quality) {
  QByteArray screenshot_data;
  if (widget) {
    QPixmap px = widget->grab();
    QBuffer buffer(&screenshot_data);
    buffer.open(QIODevice::WriteOnly);
    px.save(&buffer, format, quality);
  }

  return screenshot_data;
}
