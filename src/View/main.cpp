#include <QApplication>
#include <QSettings>

#include "../Controller/Facade.h"
#include "QTSceneDrawer.h"
#include "mainwindow.h"
using namespace s21;

int main(int argc, char *argv[]) {
  Scene scene;                // модель
  Facade facade(&scene);      // контроллер
  QTSceneDrawer sceneDrawer;  // представление

  QApplication a(argc, argv);  // инициализация приложения Qt
  QCoreApplication::setOrganizationName("YourCompany");
  QCoreApplication::setApplicationName("3DViewer");
  MainWindow w;  // создание главного окна
  w.setFacade(&facade);
  /*
  установка соединения между сигналом и слотом (паттерн наблюдатель).
  сигнал loadSceneRequested из обьекта w создается, когда пользователь
  запрашивает загрузку сцены (при выборе файла через кнопку).
  слот onLoadSceneRequested в обьекте facade вызывается при
  получении сигнала и обрабатывает запрос на загрузку сцены,
  вызывая метод LoadScene.
  => представление MainWindow уведомлят контроллер о необходимости загрузки
  сцены
  */
  QObject::connect(&w, &MainWindow::loadSceneRequested, &facade,
                   &Facade::onLoadSceneRequested);
  // уведомление представления об успешной загрузке сцены, чтобы обновить
  // интерфейс
  QObject::connect(&facade, &Facade::sceneLoaded, &w,
                   &MainWindow::onSceneLoaded);
  w.show();
  return a.exec();
}