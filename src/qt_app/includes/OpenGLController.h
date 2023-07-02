#ifndef OPENGLCONTROLLER_H
#define OPENGLCONTROLLER_H
#include <QMatrix4x4>
#include <QObject>
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLWidget>
#include <QSurfaceFormat>
#include <QTimer>

#include "Engine.h"
#include "Shader.h"
#include "Spacers/CameraSpacer.h"

class OpenGLController : public QOpenGLWidget, protected QOpenGLExtraFunctions {
  Q_OBJECT
 public:
  using QOpenGLWidget::QOpenGLWidget;
  ~OpenGLController();
  struct glDrawArraysConfig {
    bool Points = true;
    bool Lines = true;
    bool Triangles = false;
    bool Triangles_strip = false;
    float Point_size = 1;
    float Line_width = 1;
    bool roundCircle = false;
    bool dashedLines = false;
  };
  CameraSpacer *cameraSpacer = nullptr;
  QColor FragmentColor = QColor(255, 255, 255);
  QColor LineColor = QColor(255, 255, 255);
  QColor DotColor = QColor(255, 255, 255);
  QColor BackColor = QColor(0, 0, 0);
  glDrawArraysConfig drawArrConf;
  void startScreenCapture(int FPS);
  std::vector<QImage> stopScreenCapture();
  std::vector<Transform *> GetMeshTransforms();
  std::vector<Mesh *> GetMeshes();
 public slots:
  void setDrawArrConfig(struct glDrawArraysConfig config);
  void importObjFile(QString filename);
  std::vector<QImage> getScreencast();
 signals:
  void initialized();
  void importComleted(long int vertN, long int edgesN, QString filename);
  void FOVChanged();
  void zNearChanged();
  void zFarChanged();

 protected:
  void mousePressEvent(QMouseEvent *e) override;
  void mouseMoveEvent(QMouseEvent *e) override;
  void mouseReleaseEvent(QMouseEvent *e) override;
  void keyPressEvent(QKeyEvent *e) override;
  void keyReleaseEvent(QKeyEvent *e) override;

  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
 private slots:
  void capture();

 private:
  void calcSizes(int w, int h);
  QPoint mPos = QPoint(0, 0);

  QTimer captureTimer;
  bool LMB_pressed = false;
  bool RMB_pressed = false;

  QString filename;
  QVector3D rotationVec = QVector3D(0, 0, 0);
  QVector3D translationVec = QVector3D(0, 0, 0);

  int vw = 0, vh = 0, ratio = 0;
  float scale = 1;
  int width_line = 1;

  std::vector<QImage> captureBuffer;
  QSize gifResolution = QSize(640, 480);
  int gifFps = 10;
  int gifLength = 5;

  Shader *program = nullptr;
  Engine *engine;
};

#endif  // OPENGLCONTROLLER_H
