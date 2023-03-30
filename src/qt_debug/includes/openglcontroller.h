#ifndef OPENGLCONTROLLER_H
#define OPENGLCONTROLLER_H

#include <QObject>
#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QTimer>
#include <QMatrix4x4>
#include <QSurfaceFormat>
#include "geometryengine.h"
#include "shader.h"
#include "camera.h"

class OpenGLController : public QOpenGLWidget, protected QOpenGLExtraFunctions
{
  Q_OBJECT
public:
  using QOpenGLWidget::QOpenGLWidget;

  struct glDrawElementsConfig {
    bool Points = false;
    bool Lines = false;
    bool Triangles = false;
    bool Triangles_strip = false;
  };
  struct glDrawArraysConfig {
    bool Points = false;
    bool Lines = false;
    bool Triangles = false;
    bool Triangles_strip = false;
  };
  struct cameraConfig {
    Camera::CameraMode Mode = Camera::Free;
    QVector3D FocusPoint = QVector3D(0,0,0);
    QVector3D Position = QVector3D(0,0,0);
    QVector2D zRange = QVector2D(0.1, 1000);
    float FOV = 60;
  };
  Camera * camera = nullptr;
  glDrawElementsConfig drawElemConf;
  glDrawArraysConfig drawArrConf;
  cameraConfig cameraConf;
public:
  void setDrawElemConfig(glDrawElementsConfig config);
  void setDrawArrConfig(glDrawArraysConfig config);
  void setCameraConfig(cameraConfig config);

signals:
  void FOVChanged();

  void zNearChanged();

  void zFarChanged();

protected:
  void mousePressEvent(QMouseEvent *e) override;
  void mouseMoveEvent(QMouseEvent *e) override;
  void mouseReleaseEvent(QMouseEvent *e) override;
  void wheelEvent(QWheelEvent *e) override;
  void keyPressEvent(QKeyEvent *e) override;
  void keyReleaseEvent(QKeyEvent *e) override;

  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
private:

  void calcSizes(int w, int h);
  QPoint mPos = QPoint(0,0);

  int vw = 0, vh = 0, ratio = 0;

  bool LMB_pressed = false;
  bool RMB_pressed = false;

  QString filename;

  float rotation_angle = 0.2;
  float scale = 0.1;

  QVector3D rotationVec = QVector3D(0,1,0);
  QVector3D translationVec = QVector3D(0,-1,-20);

  int width_line = 1;

  Shader* program = nullptr;
  GeometryEngine *geometries = nullptr;
  void initShaders();

};

#endif // OPENGLCONTROLLER_H
