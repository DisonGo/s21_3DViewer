#ifndef OPENGLCONTROLLER_H
#define OPENGLCONTROLLER_H
#include <QOpenGLExtraFunctions>
#include <QOpenGLWidget>
#include <QTimer>
#include "Spacers/CameraSpacer.h"
#include "Spacers/EngineSpacer.h"
class OpenGLController : public QOpenGLWidget, protected QOpenGLExtraFunctions {
  Q_OBJECT
 public:
  OpenGLController(s21::EngineSpacer& engine_spacer, QWidget* parent = nullptr) : QOpenGLWidget(parent), engine_spacer_(engine_spacer) {};
  ~OpenGLController();

  void StartScreenCapture(int FPS);
  std::vector<QImage> StopScreenCapture();
  void SetCameraSpacer(s21::CameraSpacer *spacer);
 signals:
  void Initialized();

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
  void CaptureBuffer();

 private:
  s21::CameraSpacer *camera_spacer_ = nullptr;
  s21::EngineSpacer& engine_spacer_;
  void CalcSizes(int w, int h);
  QTimer captureTimer;
  bool LMB_pressed = false;
  int vw = 0, vh = 0, ratio = 0;
  std::vector<QImage> captureBuffer;
  QSize gifResolution = QSize(640, 480);
  int gifFps = 10;
  int gifLength = 5;
};

#endif  // OPENGLCONTROLLER_H
