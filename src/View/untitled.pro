QT += core gui opengl widgets
LIBS += -lGLU -lgif
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20
QMAKE_CXXFLAGS += -msse -mavx
SOURCES += \
    main.cpp \
    mainwindow.cpp \
    ../Controller/Facade.cpp \
    ../Model/Edge.cpp \
    ../Model/Figure.cpp \
    ../Model/TransformMatrix.cpp \
    ../Model/TransformMatrixBuilder.cpp \
    ../Model/Vertex.cpp \
    ../Model/FileReader.cpp \
    QTSceneDrawer.cpp \
    myglwidget.cpp \
    GifRecorder.cpp \
    ../Model/ThreeDPoint.cpp


    

HEADERS += \
    mainwindow.h \
    ../Model/Model.h \
    ../Controller/Facade.h \
    QTSceneDrawer.h \
    SceneDrawerBase.h \
    myglwidget.h \
    GifRecorder.h

FORMS += \
    mainwindow.ui

# Добавление шрифтов в ресурсы
RESOURCES += resources.qrc


