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
#include "camera.h"
class OpenGLController : public QOpenGLWidget, protected QOpenGLFunctions
{
  Q_OBJECT
public:
  using QOpenGLWidget::QOpenGLWidget;
  Camera * camera = nullptr;
  qreal getFOV() const;
  void setFOV(qreal newFOV);
  void resetFOV();

  qreal getZNear() const;
  void setZNear(qreal newZNear);
  void resetZNear();

  qreal getZFar() const;
  void setZFar(qreal newZFar);
  void resetZFar();

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

  qreal zNear = 10, zFar = 100.0f, FOV = 120.0f;

  float color_back_r = 255, color_back_g = 0, color_back_b = 0;
  float color_facet_r = 0, color_facet_g = 0, color_facet_b = 0;
  int width_line = 1;

  QMatrix4x4 projectionMatrix;
  QMatrix4x4 modelMatrix;
  QMatrix4x4 viewMatrix;


  Shader* program = nullptr;
  GeometryEngine *geometries = nullptr;
  void initShaders();
  Q_PROPERTY(qreal FOV READ getFOV WRITE setFOV RESET resetFOV NOTIFY FOVChanged)
  Q_PROPERTY(qreal zNear READ getZNear WRITE setZNear RESET resetZNear NOTIFY zNearChanged)
  Q_PROPERTY(qreal zFar READ getZFar WRITE setZFar RESET resetZFar NOTIFY zFarChanged)
};

#endif // OPENGLCONTROLLER_H
