#ifndef OPENGLCONTROLLER_H
#define OPENGLCONTROLLER_H
#include <QOpenGLExtraFunctions>
#include <QOpenGLWidget>
#include <QTimer>

#include "Spacers/CameraSpacer.h"
#include "Spacers/EngineSpacer.h"
namespace s21 {
class OGLWidget : public QOpenGLWidget, protected QOpenGLExtraFunctions {
  Q_OBJECT
 public:
  OGLWidget(EngineSpacer &engine_spacer, QWidget *parent = nullptr)
      : QOpenGLWidget(parent), engine_spacer_(engine_spacer){};
  ~OGLWidget();

  void StartScreenCapture(unsigned FPS, unsigned length, bool animated = false);
  QImage GetScreenShot();
  std::vector<QImage> StopScreenCapture();
  void SetCameraSpacer(CameraSpacer *spacer);
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
  void CalcSizes(int w, int h);

  int fps_count_ = 0;
  int gif_length_ = 5;
  int gif_fps_ = 0;
  bool gif_animation_ = false;
  std::vector<QImage> capture_buffer_;
  QSize gif_resolution_ = QSize(640, 480);
  QTimer capture_timer_;

  CameraSpacer *camera_spacer_ = nullptr;
  EngineSpacer &engine_spacer_;

  bool LMB_pressed_ = false;
  int vw_ = 0, vh_ = 0;
};

}  // namespace s21

#endif  // OPENGLCONTROLLER_H
