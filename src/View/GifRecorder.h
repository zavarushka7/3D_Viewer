#ifndef GIFRECORDER_H
#define GIFRECORDER_H

#include <QBuffer>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QImage>
#include <QMessageBox>
#include <QObject>
#include <QScopeGuard>
#include <QTimer>
#include <QVector>

extern "C" {
#include <gif_lib.h>
}
namespace s21 {
class GifRecorder : public QObject {
  Q_OBJECT
 public:
  explicit GifRecorder(QObject *parent = nullptr);
  ~GifRecorder();

  void startRecording(QWidget *widget, const QString &fileName, int width,
                      int height, int fps, int durationMs);
  void stopRecording();

 private slots:
  void captureFrame();

 private:
  void writeGif();

  QWidget *targetWidget;
  QString outputFileName;
  QTimer *timer;
  QVector<QImage> frames;
  int frameWidth;
  int frameHeight;
  int frameIntervalMs;
  int totalDurationMs;
  int frameCount;
};
}  // namespace s21

#endif  // GIFRECORDER_H