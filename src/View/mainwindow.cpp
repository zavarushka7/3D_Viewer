#include "mainwindow.h"

#include "GifRecorder.h"

using namespace s21;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  this->setWindowTitle("3D Viewer");

  moveX = 0;
  moveY = 0;
  moveZ = 0;
  turnX = 0;
  turnY = 0;
  turnZ = 0;
  scale = 1;

  // Загрузка шрифта
  int fontId =
      QFontDatabase::addApplicationFont(":/style/fonts/Orbitron-Regular.ttf");
  if (fontId == -1) {
    qWarning() << "Failed to load PressStart2P font!";
  } else {
    QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont pressStartFont(fontFamily, 9);

    // Установка шрифта для всего приложения
    QApplication::setFont(pressStartFont);

    this->setFont(pressStartFont);
    ui->centralwidget->setFont(pressStartFont);
    ui->label->setFont(pressStartFont);
    ui->chooseFileButton->setFont(pressStartFont);
  }

  // Загрузка стилей
  QFile styleFile(":/style/pink_theme.qss");
  if (styleFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
    QString styleSheet = QLatin1String(styleFile.readAll());
    this->setStyleSheet(styleSheet);
    styleFile.close();

    ui->label->setProperty("class", "info-label");
    ui->chooseFileButton->setProperty("class", "special-button");
  } else {
    qWarning() << "Could not open stylesheet file";
  }

  connect(ui->sliderX, &QSlider::valueChanged, this,
          &MainWindow::on_sliderX_valueChanged);
  connect(ui->spinBoxX, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
          this, &MainWindow::on_spinBoxX_valueChanged);

  connect(ui->sliderY, &QSlider::valueChanged, this,
          &MainWindow::on_sliderY_valueChanged);
  connect(ui->spinBoxY, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
          this, &MainWindow::on_spinBoxY_valueChanged);

  connect(ui->sliderZ, &QSlider::valueChanged, this,
          &MainWindow::on_sliderZ_valueChanged);
  connect(ui->spinBoxZ, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
          this, &MainWindow::on_spinBoxZ_valueChanged);

  connect(ui->sliderMoveX, &QSlider::valueChanged, this,
          &MainWindow::on_sliderMoveX_valueChanged);
  connect(ui->spinBoxMoveX,
          QOverload<double>::of(&QDoubleSpinBox::valueChanged), this,
          &MainWindow::on_spinBoxMoveX_valueChanged);

  connect(ui->sliderMoveY, &QSlider::valueChanged, this,
          &MainWindow::on_sliderMoveY_valueChanged);
  connect(ui->spinBoxMoveY,
          QOverload<double>::of(&QDoubleSpinBox::valueChanged), this,
          &MainWindow::on_spinBoxMoveY_valueChanged);

  connect(ui->sliderMoveZ, &QSlider::valueChanged, this,
          &MainWindow::on_sliderMoveZ_valueChanged);
  connect(ui->spinBoxMoveZ,
          QOverload<double>::of(&QDoubleSpinBox::valueChanged), this,
          &MainWindow::on_spinBoxMoveZ_valueChanged);

  QSettings settings;

  QColor bgColor =
      settings.value("bgColor", QColor(255, 240, 245)).value<QColor>();
  QColor edgeColor =
      settings.value("edgeColor", QColor(100, 100, 100)).value<QColor>();
  QColor vertexColor =
      settings.value("vertexColor", QColor(255, 105, 180)).value<QColor>();

  double vertexSize = settings.value("vertexSize", 1.0).toDouble();
  double edgeSize = settings.value("edgeSize", 1.0).toDouble();

  MyGLWidget::VertexStyle vertexStyle = static_cast<MyGLWidget::VertexStyle>(
      settings.value("vertexStyle", MyGLWidget::CIRCLE).toInt());
  MyGLWidget::EdgeStyle edgeStyle = static_cast<MyGLWidget::EdgeStyle>(
      settings.value("edgeStyle", MyGLWidget::SOLID).toInt());
  MyGLWidget::ProjectionStyle projectionStyle =
      static_cast<MyGLWidget::ProjectionStyle>(
          settings.value("projectionStyle", MyGLWidget::PERSPECTIVE).toInt());

  ui->sizeVertexSlider->setValue(vertexSize);
  ui->sizeVertexSpinbox->setValue(vertexSize);

  ui->sizeEdgeSlider->setValue(edgeSize);
  ui->sizeEdgeSpinbox->setValue(edgeSize);

  connect(ui->sizeVertexSlider, &QSlider::valueChanged, this,
          &MainWindow::on_sizeVertexSlider_valueChanged);
  connect(ui->sizeVertexSpinbox,
          QOverload<double>::of(&QDoubleSpinBox::valueChanged), this,
          &MainWindow::on_sizeVertexSpinbox_valueChanged);

  connect(ui->sizeEdgeSlider, &QSlider::valueChanged, this,
          &MainWindow::on_sizeEdgeSlider_valueChanged);
  connect(ui->sizeEdgeSpinbox,
          QOverload<double>::of(&QDoubleSpinBox::valueChanged), this,
          &MainWindow::on_sizeEdgeSpinbox_valueChanged);

  ui->lineComboBox->addItem("SOLID LINE", MyGLWidget::SOLID);
  ui->lineComboBox->addItem("DOTTED LINE", MyGLWidget::DOTTED);
  connect(ui->lineComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
          this, &MainWindow::on_lineComboBox);

  ui->verticesComboBox->addItem("NONE", MyGLWidget::INVISIBLE);
  ui->verticesComboBox->addItem("CIRCLE", MyGLWidget::CIRCLE);
  ui->verticesComboBox->addItem("SQUARE", MyGLWidget::SQUARE);
  connect(ui->verticesComboBox,
          QOverload<int>::of(&QComboBox::currentIndexChanged), this,
          &MainWindow::on_verticesComboBox);

  ui->projectionComboBox->addItem("CENTRAL", MyGLWidget::PERSPECTIVE);
  ui->projectionComboBox->addItem("PARALLEL", MyGLWidget::ORTHOGRAPHIC);
  connect(ui->projectionComboBox,
          QOverload<int>::of(&QComboBox::currentIndexChanged), this,
          &MainWindow::on_projectionComboBox);

  QTimer::singleShot(0, this,
                     [this, bgColor, edgeColor, vertexColor, vertexSize,
                      edgeSize, edgeStyle, vertexStyle, projectionStyle]() {
                       if (ui->sceneWidget) {
                         ui->sceneWidget->setBackgroundColor(bgColor);
                         ui->sceneWidget->setEdgeColor(edgeColor);
                         ui->sceneWidget->setVertexColor(vertexColor);
                         ui->sceneWidget->setVertexSize(vertexSize);
                         ui->sceneWidget->setEdgeSize(edgeSize);
                         ui->sceneWidget->setEdgeStyle(edgeStyle);
                         ui->sceneWidget->setVertexStyle(vertexStyle);
                         ui->sceneWidget->setProjectionStyle(projectionStyle);
                       }
                     });
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::setFacade(Facade *facade) { this->facade = facade; }

void MainWindow::onSceneLoaded(const SceneInfo &info) {
  QString fileName = QString::fromStdString(info.file_name);

  ui->label->setText(QString("File name: %1\nVertices: %2\nEdges: %3")
                         .arg(fileName)
                         .arg(info.vertex_count)
                         .arg(info.edge_count));
}

void MainWindow::on_chooseFileButton_clicked() {
  fileName = QFileDialog::getOpenFileName(
      this, "Выберите файл", QDir::homePath(), "obj файлы (*.obj)");
  NormalizationParameters params;
  if (!fileName.isEmpty()) {
    emit loadSceneRequested(fileName, params);
  }
}

void MainWindow::on_openFileButton_clicked() {
  if (!fileName.isEmpty()) {
    if (facade) {
      Scene *scene_ptr = facade->getScene();
      if (scene_ptr) {
        ui->sceneWidget->setScene(*scene_ptr);
      }
    }
    ui->sceneWidget->update();
  }
}

void MainWindow::on_recordImageButton_clicked() {
  QByteArray screenshot_data = ui->sceneWidget->getWidgetScreenshot("BMP");

  QString default_path = QDir::homePath() + "/3DViewer_screenshot.bmp";
  QString file_name = QFileDialog::getSaveFileName(
      this, "Сохранить скриншот", default_path,
      "BMP Images (*.bmp);;JPEG Images (*.jpg *.jpeg);;All Files(*)");

  if (!file_name.isEmpty()) {
    if (!file_name.endsWith(".bmp", Qt::CaseInsensitive) &&
        !file_name.endsWith(".jpg", Qt::CaseInsensitive) &&
        !file_name.endsWith(".jpeg", Qt::CaseInsensitive)) {
      file_name += ".bmp";
    }

    QFile file(file_name);
    if (file.open(QIODevice::WriteOnly)) {
      file.write(screenshot_data);
      file.close();
      QMessageBox::information(this, "Успех", "Скриншот успешно сохранен");
    } else {
      QMessageBox::warning(this, "Ошибка",
                           "Не удалось сохранить файл: " + file.errorString());
    }
  }
}

void MainWindow::on_recordScreencastButton_clicked() {
  QString default_path = QDir::homePath() + "/3DViewer_screencast.gif";
  QString file_name = QFileDialog::getSaveFileName(
      this, "Сохранить GIF", default_path, "GIF Images (*.gif);;All Files (*)");

  if (!file_name.isEmpty()) {
    if (!file_name.endsWith(".gif", Qt::CaseInsensitive)) {
      file_name += ".gif";
    }

    GifRecorder *recorder = new GifRecorder(this);
    recorder->startRecording(ui->sceneWidget, file_name, 640, 480, 10, 5000);
  }
}

void MainWindow::on_chooseColorBackgroundButton_clicked() {
  QColor color = QColorDialog::getColor(
      Qt::white, this, "Выберете цвет фона",
      QColorDialog::DontUseNativeDialog | QColorDialog::ShowAlphaChannel);
  if (color.isValid()) {
    ui->sceneWidget->setBackgroundColor(color);
  }
}

void MainWindow::on_chooseColorEdgeButton_clicked() {
  QColor current_color = ui->sceneWidget->getEdgeColor();
  QColor color =
      QColorDialog::getColor(current_color, this, "Выберете цвет ребер",
                             QColorDialog::DontUseNativeDialog);
  if (color.isValid()) {
    ui->sceneWidget->setEdgeColor(color);
  }
}

void MainWindow::on_chooseColorVertexButton_clicked() {
  QColor current_color = ui->sceneWidget->getVertexColor();
  QColor color =
      QColorDialog::getColor(current_color, this, "Выберете цвет вершин",
                             QColorDialog::DontUseNativeDialog);
  if (color.isValid()) {
    ui->sceneWidget->setVertexColor(color);
  }
}

void MainWindow::closeEvent(QCloseEvent *event) {
  if (ui->sceneWidget) {
    QSettings settings;

    settings.setValue("bgColor", ui->sceneWidget->getBackgroundColor());
    settings.setValue("edgeColor", ui->sceneWidget->getEdgeColor());
    settings.setValue("vertexColor", ui->sceneWidget->getVertexColor());
    settings.setValue("vertexSize", ui->sceneWidget->getVertexSize());
    settings.setValue("edgeSize", ui->sceneWidget->getEdgeSize());
    settings.setValue("edgeStyle", ui->sceneWidget->getEdgeStyle());
    settings.setValue("vertexStyle", ui->sceneWidget->getVertexStyle());
    settings.setValue("projectionStyle", ui->sceneWidget->getProjectionStyle());

    settings.sync();
  }
  QMainWindow::closeEvent(event);
}

void MainWindow::on_verticesComboBox(int index) {
  Q_UNUSED(index);
  int style = ui->verticesComboBox->currentData().toInt();
  ui->sceneWidget->setVertexStyle(static_cast<MyGLWidget::VertexStyle>(style));
}

void MainWindow::on_sizeVertexSlider_valueChanged(int value) {
  ui->sizeVertexSpinbox->setValue(value);
  ui->sceneWidget->setVertexSize(value);
}

void MainWindow::on_sizeVertexSpinbox_valueChanged(double value) {
  ui->sizeVertexSlider->setValue(static_cast<int>(value));
  ui->sceneWidget->setVertexSize(value);
}

void MainWindow::on_sizeEdgeSlider_valueChanged(int value) {
  ui->sizeEdgeSpinbox->setValue(value);
  ui->sceneWidget->setEdgeSize(value);
}

void MainWindow::on_sizeEdgeSpinbox_valueChanged(double value) {
  ui->sizeEdgeSlider->setValue(static_cast<int>(value));
  ui->sceneWidget->setEdgeSize(value);
}

void MainWindow::on_lineComboBox(int index) {
  Q_UNUSED(index);
  int style = ui->lineComboBox->currentData().toInt();
  ui->sceneWidget->setEdgeStyle(static_cast<MyGLWidget::EdgeStyle>(style));
}

void MainWindow::on_projectionComboBox(int index) {
  Q_UNUSED(index);
  int style = ui->projectionComboBox->currentData().toInt();
  ui->sceneWidget->setProjectionStyle(
      static_cast<MyGLWidget::ProjectionStyle>(style));
}

void MainWindow::on_sliderIncrease_valueChanged(int value) {
  scale = value;
  ui->spinBoxIncrease->setValue(value);
  facade->ScaleScene(scale);
  ui->sceneWidget->update();
}

void MainWindow::on_spinBoxIncrease_valueChanged(double value) {
  scale = value;
  ui->sliderIncrease->setValue(static_cast<int>(value));
  facade->ScaleScene(scale);
  ui->sceneWidget->update();
}

void MainWindow::on_sliderX_valueChanged(int value) {
  ui->spinBoxX->blockSignals(true);
  ui->spinBoxX->setValue(value);
  ui->spinBoxX->blockSignals(false);
  turnX = value;
  facade->RotateScene(turnX, turnY, turnZ);
  ui->sceneWidget->update();
}

void MainWindow::on_spinBoxX_valueChanged(double value) {
  int scaledValue = static_cast<int>(value);
  ui->sliderX->blockSignals(true);
  ui->sliderX->setValue(scaledValue);
  ui->sliderX->blockSignals(false);
  turnX = scaledValue;
  facade->RotateScene(turnX, turnY, turnZ);
  ui->sceneWidget->update();
}

void MainWindow::on_sliderY_valueChanged(int value) {
  ui->spinBoxY->blockSignals(true);
  ui->spinBoxY->setValue(value);  // Преобразуем int к double
  ui->spinBoxY->blockSignals(false);
  turnY = value;
  facade->RotateScene(turnX, turnY, turnZ);
  ui->sceneWidget->update();
}

void MainWindow::on_spinBoxY_valueChanged(double value) {
  int scaledValue = static_cast<int>(value);
  ui->sliderY->blockSignals(true);
  ui->sliderY->setValue(scaledValue);
  ui->sliderY->blockSignals(false);
  turnY = scaledValue;
  facade->RotateScene(turnX, turnY, turnZ);
  ui->sceneWidget->update();
}

void MainWindow::on_sliderZ_valueChanged(int value) {
  ui->spinBoxZ->blockSignals(true);
  ui->spinBoxZ->setValue(value);
  ui->spinBoxZ->blockSignals(false);
  turnZ = value;
  facade->RotateScene(turnX, turnY, turnZ);
  ui->sceneWidget->update();
}

void MainWindow::on_spinBoxZ_valueChanged(double value) {
  int scaledValue = static_cast<int>(value);
  ui->sliderZ->blockSignals(true);
  ui->sliderZ->setValue(scaledValue);
  ui->sliderZ->blockSignals(false);
  turnZ = scaledValue;
  facade->RotateScene(turnX, turnY, turnZ);
  ui->sceneWidget->update();
}

void MainWindow::on_sliderMoveX_valueChanged(int value) {
  ui->spinBoxMoveX->blockSignals(true);
  ui->spinBoxMoveX->setValue(value);
  ui->spinBoxMoveX->blockSignals(false);
  moveX = value;
  facade->MoveScene(moveX, moveY, moveZ);
  ui->sceneWidget->update();
}

void MainWindow::on_spinBoxMoveX_valueChanged(double value) {
  int scaledValue = static_cast<int>(value);
  ui->sliderMoveX->blockSignals(true);
  ui->sliderMoveX->setValue(scaledValue);
  ui->sliderMoveX->blockSignals(false);
  moveX = scaledValue;
  facade->MoveScene(moveX, moveY, moveZ);
  ui->sceneWidget->update();
}

void MainWindow::on_sliderMoveY_valueChanged(int value) {
  ui->spinBoxMoveY->blockSignals(true);
  ui->spinBoxMoveY->setValue(value);
  ui->spinBoxMoveY->blockSignals(false);
  moveY = value;
  facade->MoveScene(moveX, moveY, moveZ);
  ui->sceneWidget->update();
}

void MainWindow::on_spinBoxMoveY_valueChanged(double value) {
  int scaledValue = static_cast<int>(value);
  ui->sliderMoveY->blockSignals(true);
  ui->sliderMoveY->setValue(scaledValue);
  ui->sliderMoveY->blockSignals(false);
  moveY = scaledValue;
  facade->MoveScene(moveX, moveY, moveZ);
  ui->sceneWidget->update();
}

void MainWindow::on_sliderMoveZ_valueChanged(int value) {
  ui->spinBoxMoveZ->blockSignals(true);
  ui->spinBoxMoveZ->setValue(value);
  ui->spinBoxMoveZ->blockSignals(false);
  moveZ = value;
  facade->MoveScene(moveX, moveY, moveZ);
  ui->sceneWidget->update();
}

void MainWindow::on_spinBoxMoveZ_valueChanged(double value) {
  int scaledValue = static_cast<int>(value);
  ui->sliderMoveZ->blockSignals(true);
  ui->sliderMoveZ->setValue(scaledValue);
  ui->sliderMoveZ->blockSignals(false);
  moveZ = scaledValue;
  facade->MoveScene(moveX, moveY, moveZ);
  ui->sceneWidget->update();
}
