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
  // Enables Cull Facing
  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
//  // Keeps front faces
//  glCullFace(GL_FRONT);
//  glFrontFace(GL_CCW);
//  glDisable(GL_CULL_FACE);

  geometries = new GeometryEngine(program);
  qDebug() << geometries->verticesN;
  qDebug() << geometries->indicesN;

  camera = new Camera(vw, vh, cameraConf.Position);
  camera->setMode(cameraConf.Mode);
  camera->setFocusPoint(cameraConf.FocusPoint);

  connect(camera, SIGNAL(dataUpdated(CameraData)), window(), SLOT(updateLabels(CameraData)));
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
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  program->Activate();
  camera->Matrix(cameraConf.FOV,
                 cameraConf.zRange.x(),
                 cameraConf.zRange.y(),
                 *program,
                 "camMatrix");

//  QMatrix4x4 model;
//  model.setToIdentity();
//  int modelLoc = glGetUniformLocation(program->ID, "model");
//  glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model.constData());


  if (drawElemConf.Points)
    geometries->drawGeometry(GL_POINTS);
  if (drawElemConf.Lines)
    geometries->drawGeometry(GL_LINES);
  if (drawElemConf.Triangles)
    geometries->drawGeometry(GL_TRIANGLES);
  if (drawElemConf.Triangles_strip)
    geometries->drawGeometry(GL_TRIANGLE_STRIP);

  // Draw arrays
//  if (drawArrConf.Points)
//    glDrawArrays(GL_POINTS, 0, geometries->verticesN);
//  if (drawArrConf.Lines)
//    glDrawArrays(GL_LINES, 0, geometries->indicesN);
//  if (drawArrConf.Triangles)
//    glDrawArrays(GL_TRIANGLES, 0, geometries->indicesN);
//  if (drawArrConf.Triangles_strip)
//    glDrawArrays(GL_TRIANGLE_STRIP, 0, geometries->indicesN);

}

void OpenGLController::calcSizes(int w, int h)
{
  vw = w;
  vh = h;
  ratio = vw / vh;
}

void OpenGLController::setDrawElemConfig(glDrawElementsConfig config)
{
  drawElemConf = config;
  update();
}

void OpenGLController::setDrawArrConfig(glDrawArraysConfig config)
{
  drawArrConf = config;
  update();
}

void OpenGLController::setCameraConfig(cameraConfig config)
{
  cameraConf = config;
  if (camera) {
    camera->setMode(cameraConf.Mode);
    camera->setFocusPoint(cameraConf.FocusPoint);
    camera->setPosition(cameraConf.Position);
    update();
  }
}
