#ifndef OPENGLCONTROLLER_H
#define OPENGLCONTROLLER_H

#include <QObject>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QTimer>
#include <QMatrix4x4>
#include <QSurfaceFormat>
#include "geometryengine.h"
#include "shader.h"
class OpenGLController : public QOpenGLWidget, protected QOpenGLFunctions
{
  Q_OBJECT
public:
  using QOpenGLWidget::QOpenGLWidget;
protected:
  void mousePressEvent(QMouseEvent *e) override;
  void mouseMoveEvent(QMouseEvent *e) override;
  void mouseReleaseEvent(QMouseEvent *e) override;
  void wheelEvent(QWheelEvent *e) override;
  void keyPressEvent(QKeyEvent *e) override;

  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
private:
  QPoint mPos = QPoint(0,0);

  bool LMB_pressed = false;
  bool RMB_pressed = false;

  QString filename;

  float rotation_angle = 0.2;
  float scale = 0.1;

  QVector3D rotationVec = QVector3D(0,1,0);
  QVector3D translationVec = QVector3D(0,-1,-20);

  qreal zNear = 0.1f, zFar = 100.0f, FOV = 60.0f;

  float color_back_r = 255, color_back_g = 0, color_back_b = 0;
  float color_facet_r = 0, color_facet_g = 0, color_facet_b = 0;
  int width_line = 1;

  QMatrix4x4 projectionMatrix;
  QMatrix4x4 modelMatrix;
  QMatrix4x4 viewMatrix;

  Shader* program = nullptr;
  GeometryEngine *geometries = nullptr;
  void initShaders();
};

#endif // OPENGLCONTROLLER_H
