#ifndef OPENGLCONTROLLER_H
#define OPENGLCONTROLLER_H
#include <QObject>
#include <QOpenGLExtraFunctions>
#include <QOpenGLFramebufferObjectFormat>
#include <QOpenGLTexture>
#include <QOpenGLWidget>
#include <QSurfaceFormat>
#include <QTimer>

#include "Engine.h"
#include "Shaders/Program.h"
#include "Spacers/CameraSpacer.h"

class OpenGLController : public QOpenGLWidget, protected QOpenGLExtraFunctions {
  Q_OBJECT
 public:
  using QOpenGLWidget::QOpenGLWidget;
  ~OpenGLController();
  s21::CameraSpacer *cameraSpacer = nullptr;
  void startScreenCapture(int FPS);
  std::vector<QImage> stopScreenCapture();
  void SetCameraSpacer(s21::CameraSpacer *spacer);
 public slots:
  void importObjFile(QString filename);
  void RequestUpdate();
 signals:
  void initialized();

 protected:
  void mousePressEvent(QMouseEvent *e) override;
  void mouseMoveEvent(QMouseEvent *e) override;
  void mouseReleaseEvent(QMouseEvent *e) override;
  void keyPressEvent(QKeyEvent *e) override;
  void keyReleaseEvent(QKeyEvent *e) override;
  void wheelEvent(QWheelEvent *e) override;

  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
 private slots:
  void capture();
  void PopUpdateSchedule();

 private:
  void calcSizes(int w, int h);
  QTimer captureTimer;
  bool LMB_pressed = false;
  int vw = 0, vh = 0, ratio = 0;
  std::vector<int> update_schedule_;
  std::vector<QImage> captureBuffer;
  QSize gifResolution = QSize(640, 480);
  int gifFps = 10;
  int gifLength = 5;
  s21::Engine *engine;
};

#endif  // OPENGLCONTROLLER_H
