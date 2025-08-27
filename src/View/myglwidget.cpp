#include "myglwidget.h"

using namespace s21;
MyGLWidget::MyGLWidget(QWidget* parent)
    : QOpenGLWidget(parent),
      isRotating(false),
      isMoving(false),
      xRot(0),
      yRot(0),
      xMove(0),
      yMove(0),
      currentScale(1.0f),
      facade(nullptr) {
  sceneDrawer = new QTSceneDrawer();
  setMouseTracking(true);
  setFocusPolicy(Qt::StrongFocus);
}

MyGLWidget::~MyGLWidget() {
  makeCurrent();
  delete sceneDrawer;
  doneCurrent();
}

void MyGLWidget::setScene(const s21::Scene& scene) {
  currentScene = scene;
  update();
}

void MyGLWidget::initializeGL() {
  initializeOpenGLFunctions();
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // Устанавливаем цвет фона
  glEnable(GL_DEPTH_TEST);  // Включаем тест глубины (важно для 3D)
  glEnable(GL_LINE_SMOOTH);
  glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
}

void MyGLWidget::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
  updateProjection();
}

void MyGLWidget::updateProjection() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  float aspect = float(width()) / float(height());

  if (projection_style_ == PERSPECTIVE) {
    float fov = 45.0f;
    float near = 0.1f;
    float far = 100.0f;
    gluPerspective(fov, aspect, near, far);
  } else {
    float scale = 2.0f;
    glOrtho(-scale * aspect, scale * aspect, -scale, scale, -100.0f, 100.0f);
  }

  glMatrixMode(GL_MODELVIEW);
}

void MyGLWidget::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();  // сбрасываем моцификации матрицы

  if (projection_style_ == PERSPECTIVE) {
    gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
  } else {
    glTranslatef(0.0f, 0.0f, -5.0f);
  }

  // Применяем перемещение
  glTranslatef(xMove, yMove, 0.0f);

  // применяем вращение
  glRotatef(xRot, 1.0f, 0.0f, 0.0f);
  glRotatef(yRot, 0.0f, 1.0f, 0.0f);

  // Применяем масштабирование
  glScalef(currentScale, currentScale, currentScale);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  float aspect = float(width()) / float(height());

  if (projection_style_ == PERSPECTIVE) {
    gluPerspective(45.0f, aspect, 0.1f, 100.0f);
  } else {
    float scale = 2.0f;
    glOrtho(-scale * aspect, scale * aspect, -scale, scale, -100.0f, 100.0f);
  }

  glMatrixMode(GL_MODELVIEW);

  if (edge_style_ == DOTTED) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00FF);
  } else {
    glDisable(GL_LINE_STIPPLE);
  }

  glLineWidth(edge_size_);

  if (sceneDrawer) {
    sceneDrawer->DrawScene(currentScene, edge_color_);
  }
  if (vertex_style_ != INVISIBLE) {
    glPointSize(vertex_size_);

    if (vertex_style_ == CIRCLE) {
      glEnable(GL_POINT_SMOOTH);
    } else {
      glDisable(GL_POINT_SMOOTH);
    }

    glBegin(GL_POINTS);
    glColor3f(vertex_color_.redF(), vertex_color_.greenF(),
              vertex_color_.blueF());
    for (auto& figure : currentScene.GetFigures()) {
      for (auto& vertex : figure->GetVertices()) {
        ThreeDPoint p = vertex->GetPosition();
        glVertex3f(p.x, p.y, p.z);
      }
    }
    glEnd();
  }
}

QByteArray MyGLWidget::getWidgetScreenshot(const char* format, int quality) {
  QByteArray screenshot_data;
  QPixmap px = this->grab();

  QBuffer buffer(&screenshot_data);
  buffer.open(QIODevice::WriteOnly);
  px.save(&buffer, format, quality);

  return screenshot_data;
}

void MyGLWidget::setBackgroundColor(const QColor& color) {
  if (!isValid()) return;

  background_color_ = color;

  if (isVisible()) {
    makeCurrent();
    glClearColor(color.redF(), color.greenF(), color.blueF(), color.alphaF());
    doneCurrent();
  }
}

void MyGLWidget::setEdgeColor(const QColor& color) {
  edge_color_ = color;
  update();
}

QColor MyGLWidget::getEdgeColor() const { return edge_color_; }

QColor MyGLWidget::getBackgroundColor() const { return background_color_; }

void MyGLWidget::setVertexColor(const QColor& color) {
  vertex_color_ = color;
  update();
}

QColor MyGLWidget::getVertexColor() const { return vertex_color_; }
double MyGLWidget::getVertexSize() const { return vertex_size_; }
double MyGLWidget::getEdgeSize() const { return edge_size_; }
void MyGLWidget::setVertexStyle(VertexStyle style) {
  vertex_style_ = style;
  update();
}
void MyGLWidget::setEdgeStyle(EdgeStyle style) {
  edge_style_ = style;
  update();
}
MyGLWidget::VertexStyle MyGLWidget::getVertexStyle() { return vertex_style_; }
MyGLWidget::EdgeStyle MyGLWidget::getEdgeStyle() { return edge_style_; }

void MyGLWidget::setVertexSize(double size) {
  vertex_size_ = size;
  update();
}

void MyGLWidget::setEdgeSize(double size) {
  edge_size_ = size;
  update();
}

//    void MyGLWidget::setIncrease(double scale){

//    }

MyGLWidget::ProjectionStyle MyGLWidget::getProjectionStyle() {
  return projection_style_;
}
void MyGLWidget::setProjectionStyle(ProjectionStyle style) {
  if (projection_style_ != style) {
    projection_style_ = style;
    updateProjection();
    update();
  }
}

void MyGLWidget::mousePressEvent(QMouseEvent* event) {
  if (event->button() == Qt::LeftButton) {
    lastMousePos = event->pos();  // сохраняем текущую позицию мыши
    isRotating = true;
  } else if (event->button() == Qt::RightButton) {
    lastRightMousePos = event->pos();
    isMoving = true;
  }
  QOpenGLWidget::mousePressEvent(event);  // передаем событие родителю
}

void MyGLWidget::mouseMoveEvent(QMouseEvent* event) {
  if (isRotating && (event->buttons() & Qt::LeftButton)) {
    QPoint delta = event->pos() - lastMousePos;

    // Чувствительность вращения
    float sensitivity = 0.5f;

    yRot += delta.x() * sensitivity;
    xRot -= delta.y() *
            sensitivity;  // Инвертируем для более естественного вращения

    xRot = qBound(-90.0f, xRot, 90.0f);  // ограничение угла по Х

    lastMousePos = event->pos();  // обновляем позицию

    if (facade) {
      facade->RotateScene(xRot, yRot, 0);  // передаем контроллеру
    }
    update();
  } else if (isMoving && (event->buttons() & Qt::RightButton)) {
    QPoint delta = event->pos() - lastRightMousePos;

    // Чувствительность перемещения
    float sensitivity = 0.01f;

    xMove += delta.x() * sensitivity;
    yMove -= delta.y() * sensitivity;  // Инвертируем ось Y

    lastRightMousePos = event->pos();

    if (facade) {
      facade->MoveScene(xMove, yMove, 0);
    }
    update();
  }
  QOpenGLWidget::mousePressEvent(event);
}

void MyGLWidget::wheelEvent(QWheelEvent* event) {
  QPoint numDegrees = event->angleDelta() / 8;

  if (!numDegrees.isNull()) {
    float zoomFactor = 1.1f;
    if (numDegrees.y() > 0) {
      currentScale *= zoomFactor;
    } else {
      currentScale /= zoomFactor;
    }

    // Ограничиваем масштаб
    currentScale = qBound(0.1f, currentScale, 10.0f);

    if (facade) {
      facade->ScaleScene(currentScale);
    }
    update();
  }
  event->accept();
}