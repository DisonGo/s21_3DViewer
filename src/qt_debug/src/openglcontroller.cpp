#include "openglcontroller.h"
//#include "glm/glm.hpp"
//#include <glm/gtc/matrix_transform.hpp>
#include <QMouseEvent>

void OpenGLController::mousePressEvent(QMouseEvent *e)
{
  if (e->button() == Qt::LeftButton) {
    LMB_pressed = true;
    mPos = e->pos();
  }
}

void OpenGLController::mouseMoveEvent(QMouseEvent *e)
{
  if (!LMB_pressed) return;
  QPoint ePos = e->pos();
  QVector2D mouseDif(ePos.x() - mPos.x(), ePos.y() - mPos.x());
  rotationVec = QVector3D(mouseDif, 0);
  update();
}

void OpenGLController::mouseReleaseEvent(QMouseEvent *e)
{
  if (e->button() == Qt::LeftButton) {
    LMB_pressed = false;
    mPos = e->pos();
  }
}
void OpenGLController::wheelEvent(QWheelEvent *e) {
  float increment = e->angleDelta().ry()/15.0f;
  rotation_angle += increment;
  update();
}

void OpenGLController::keyPressEvent(QKeyEvent *e)
{
  float inc = 0.1;
  if (e->key() == Qt::Key_Up) {
    translationVec += QVector3D(0,inc,0);
  }
  if (e->key() == Qt::Key_Down) {
    translationVec += QVector3D(0,-inc,0);
  }
  if (e->key() == Qt::Key_Right) {
    translationVec += QVector3D(inc,0,0);
  }
  if (e->key() == Qt::Key_Left) {
    translationVec += QVector3D(-inc,0,0);
  }
  update();
}
void OpenGLController::initShaders()
{
   program = new Shader(":/vshader.glsl", ":/fshader.glsl", this);
}
void OpenGLController::initializeGL()
{
  initializeOpenGLFunctions();
  QSize window_size = this->size();
  float width = window_size.width();
  float height = window_size.height();
  float aspectRatio = width / height;

  glClearColor(0,0,0,1);
  initShaders();
  //  glEnable(GL_DEPTH_TEST);
  //  glEnable(GL_CULL_FACE);
  glEnable(GL_PROGRAM_POINT_SIZE);
  geometries = new GeometryEngine(program);

  // Matrices initialization
  modelMatrix.setToIdentity();
  viewMatrix.setToIdentity();
  projectionMatrix.setToIdentity();
}

void OpenGLController::resizeGL(int w, int h)
{
  glViewport(0,0,w,h);
  update();
}

void OpenGLController::paintGL()
{
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);
  program->Activate();
  QMatrix4x4 model = modelMatrix;
  QMatrix4x4 view = viewMatrix;
  QMatrix4x4 projection = projectionMatrix;
  QSize window_size = this->size();
  float width = window_size.width();
  float height = window_size.height();
  float aspectRatio = width / height;

  model.rotate(rotation_angle, rotationVec);
  view.translate(translationVec);
  projection.perspective(FOV, aspectRatio, zNear, zFar);
  // Outputs the matrices into the Vertex Shader

  int modelLoc = glGetUniformLocation(program->ID, "model");
  glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model.data());

  int viewLoc = glGetUniformLocation(program->ID, "view");
  glUniformMatrix4fv(viewLoc, 1, GL_FALSE, view.data());

  int projLoc = glGetUniformLocation(program->ID, "proj");
  glUniformMatrix4fv(projLoc, 1, GL_FALSE, projection.data());

  GLuint uniID = glGetUniformLocation(program->ID, "scale");
  glUniform1f(uniID, scale);
  qDebug() << "Proj" << projection;
  qDebug() << "View" << view;
  qDebug() << "Model" << model;
  geometries->drawCubeGeometry();
  glDrawElements(GL_LINES, geometries->indiciesN, GL_UNSIGNED_SHORT, nullptr);
  glDrawElements(GL_POINTS, geometries->indiciesN, GL_UNSIGNED_SHORT, nullptr);
  glDrawElements(GL_TRIANGLE_STRIP, geometries->indiciesN, GL_UNSIGNED_SHORT, nullptr);
}
