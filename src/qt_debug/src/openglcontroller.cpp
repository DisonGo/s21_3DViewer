#include "openglcontroller.h"
//#include "glm/glm.hpp"
//#include <glm/gtc/matrix_transform.hpp>
#include <QMouseEvent>

void OpenGLController::mousePressEvent(QMouseEvent *e)
{
  if (e->button() == Qt::LeftButton) {
    LMB_pressed = true;
    mPos = e->pos();
    camera->mousePressSlot(e);
  }
}

void OpenGLController::mouseMoveEvent(QMouseEvent *e)
{
  if (!LMB_pressed) return;
  QPoint ePos = e->pos();
  QLine mouseLine(mPos, ePos);
  QVector2D mouseDif(-mouseLine.dx(), mouseLine.dy());
  rotationVec = QVector3D(mouseDif, 0);
  camera->mouseMoveSlot(e);
  update();
}

void OpenGLController::mouseReleaseEvent(QMouseEvent *e)
{
  if (e->button() == Qt::LeftButton) {
    LMB_pressed = false;
    mPos = e->pos();
    if (camera) camera->mouseReleaseSlot(e);
  }
}
void OpenGLController::wheelEvent(QWheelEvent *e) {
  if (camera) camera->wheelSlot(e);
  update();
}

void OpenGLController::keyPressEvent(QKeyEvent *e)
{
  if (camera) camera->keyPressSlot(e);
  update();
}
void OpenGLController::keyReleaseEvent(QKeyEvent *e)
{
  if (camera) camera->keyReleaseSlot(e);
  update();
}
void OpenGLController::initShaders()
{
   program = new Shader(":/vshader.glsl", ":/fshader.glsl", this);
}
void OpenGLController::initializeGL()
{
  initializeOpenGLFunctions();
  QSize winSize = this->size();
  calcSizes(winSize.width(), winSize.height());
  glClearColor(0,0,0,1);
  initShaders();
  glEnable(GL_PROGRAM_POINT_SIZE);
  // Enables the Depth Buffer
//  glEnable(GL_DEPTH_TEST);
//  // Enables Cull Facing
//  glEnable(GL_CULL_FACE);
//  // Keeps front faces
//  glCullFace(GL_FRONT);
//  glFrontFace(GL_CCW);
  geometries = new GeometryEngine(program);
  QVector3D cameraInitPos(0, 0, 2);
  camera = new Camera(vw, vh, cameraInitPos);
  connect(camera, SIGNAL(dataUpdated(CameraData)), parent()->parent(), SLOT(updateLabels(CameraData)));
  modelMatrix.setToIdentity();
  viewMatrix.setToIdentity();
  projectionMatrix.setToIdentity();
}

void OpenGLController::resizeGL(int w, int h)
{
  glViewport(0, 0, w, h);
  calcSizes(w, h);
  update();
}

void OpenGLController::paintGL()
{
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT |  GL_DEPTH_BUFFER_BIT);
  program->Activate();
  QMatrix4x4 model;
  model.setToIdentity();
  model.rotate(30, QVector3D(1,0,0));
  camera->setMode(Camera::Focus);
  camera->setFocusPoint(QVector3D(0.894,0,0.447));
  camera->Matrix(FOV, zNear, zFar, *program, "camMatrix");
  int modelLoc = glGetUniformLocation(program->ID, "model");
  glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model.constData());
//  qDebug() << FOV << zNear << zFar;
  geometries->drawCubeGeometry();
  glDrawElements(GL_POINTS, geometries->indiciesN, GL_UNSIGNED_SHORT, nullptr);
  glDrawElements(GL_LINES, geometries->indiciesN, GL_UNSIGNED_SHORT, nullptr);
//  glDrawElements(GL_TRIANGLES, geometries->indiciesN, GL_UNSIGNED_SHORT, nullptr);
//  glDrawElements(GL_TRIANGLES, geometries->indiciesN, GL_UNSIGNED_SHORT, nullptr);
}

void OpenGLController::calcSizes(int w, int h)
{
  vw = w;
  vh = h;
  ratio = vw / vh;
}

qreal OpenGLController::getZFar() const
{
  return zFar;
}

void OpenGLController::setZFar(qreal newZFar)
{
  if (qFuzzyCompare(zFar, newZFar))
    return;
  zFar = newZFar;
  emit zFarChanged();
}

void OpenGLController::resetZFar()
{
  setZFar(100); // TODO: Adapt to use your actual default value
}

qreal OpenGLController::getZNear() const
{
  return zNear;
}

void OpenGLController::setZNear(qreal newZNear)
{
  if (qFuzzyCompare(zNear, newZNear))
    return;
  zNear = newZNear;
  emit zNearChanged();
}

void OpenGLController::resetZNear()
{
  setZNear(0.1); // TODO: Adapt to use your actual default value
}

qreal OpenGLController::getFOV() const
{
  return FOV;
}

void OpenGLController::setFOV(qreal newFOV)
{
  if (qFuzzyCompare(FOV, newFOV))
    return;
  FOV = newFOV;
  emit FOVChanged();
}

void OpenGLController::resetFOV()
{
  setFOV(45); // TODO: Adapt to use your actual default value
}
