#include "openglcontroller.h"
//#include "glm/glm.hpp"
//#include <glm/gtc/matrix_transform.hpp>
#include <QMouseEvent>
#include <QFileInfo>

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
  program = new Shader(":/Shaders/vshader.glsl", ":/Shaders/fshader.glsl", this);
}
void OpenGLController::initializeGL()
{
  initializeOpenGLFunctions();
  QSize winSize = this->size();
  calcSizes(winSize.width(), winSize.height());
  glClearColor(0,0,0,1);
  initShaders();
  glEnable(GL_PROGRAM_POINT_SIZE);
  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_MULTISAMPLE);
  glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
  geometries = new Engine(program);
  camera = new Camera(vw, vh, cameraConf.Position);
  camera->setMode(cameraConf.Mode);
  camera->setFocusPoint(cameraConf.FocusPoint);
  camera->setOrientation(cameraConf.Orientation);
}

void OpenGLController::resizeGL(int w, int h)
{
  glViewport(0, 0, w, h);
  calcSizes(w, h);
  camera->setVw(vw);
  camera->setVh(vh);
  update();
}
void OpenGLController::setColorUniform(int id, QColor in) {
  makeCurrent();
  glUniform3f(id, in.redF(),in.greenF(),in.blueF());
}
void OpenGLController::setPointUniform(bool circle, float size) {
  makeCurrent();
  int pointSizeLoc = glGetUniformLocation(program->ID, "aPointSize");
  glUniform1f(pointSizeLoc, size);
  int pointCircleLoc = glGetUniformLocation(program->ID, "roundCircle");
  glUniform1i(pointCircleLoc, circle);

}
void OpenGLController::setLineDash(bool on) {
  makeCurrent();
  int dashedLoc = glGetUniformLocation(program->ID, "dashed");
  glUniform1i(dashedLoc, on);
  if (on) {
    int patternLoc = glGetUniformLocation(program->ID, "dash_pattern");
    glUniform2f(patternLoc, 0.1, 0.1);
    int lineWidthLoc = glGetUniformLocation(program->ID, "line_width");
    glUniform1f(lineWidthLoc, drawArrConf.Line_width);
  }
}
void OpenGLController::paintGL()
{
  glClearColor(BackColor.redF(), BackColor.greenF(), BackColor.blueF(), 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  program->Activate();
  camera->setViewMode(cameraConf.viewMode);
  camera->Matrix(cameraConf.FOV,
                 cameraConf.zRange.x(),
                 cameraConf.zRange.y(),
                 *program,
                 "camMatrix");
  QMatrix4x4 modelRotX;
  QMatrix4x4 modelRotY;
  QMatrix4x4 modelRotZ;
  QMatrix4x4 modelTranslate;
  QMatrix4x4 modelScale;
  modelTranslate.setToIdentity();
  modelScale.setToIdentity();
  
  translate_matrix(modelTranslate.data(), translationVec.x(), translationVec.y(), translationVec.z());
  scale_matrix(modelScale.data(), scale);
  rotate_matrix(modelRotX.data(), rotationVec.x(), 1, 0, 0);
  rotate_matrix(modelRotY.data(), rotationVec.y(), 0, 1, 0);
  rotate_matrix(modelRotZ.data(), rotationVec.z(), 0, 0, 1);
  QMatrix4x4 modelRot(modelRotX * modelRotY * modelRotZ);
  int modelLoc = glGetUniformLocation(program->ID, "model");
  glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (modelTranslate * modelRot * modelScale).data());
  int ColorLoc = glGetUniformLocation(program->ID, "aColor");
  if (drawArrConf.Points) {
    setPointUniform(drawArrConf.roundCircle, drawArrConf.Point_size);
    setColorUniform(ColorLoc, DotColor);
    geometries->drawGeometry(GL_POINTS);
    setPointUniform(false, drawArrConf.Point_size);
  }
  if (drawArrConf.Triangles) {
    setColorUniform(ColorLoc, FragmentColor);
    geometries->drawGeometry(GL_TRIANGLES);
  }
  if (drawArrConf.Lines) {
    if (drawArrConf.dashedLines)
      setLineDash(true);
    setColorUniform(ColorLoc, LineColor);
    geometries->drawGeometry(GL_LINES);
    if (drawArrConf.dashedLines)
      setLineDash(false);
  }
}
void OpenGLController::setLineWidth(float width)
{
  makeCurrent();
  drawArrConf.Line_width = width;
  glLineWidth(width);
  update();
}

void OpenGLController::setScale(float scale)
{
  this->scale = scale;
  update();
}

void OpenGLController::setTranslation(QVector3D translation)
{
  translationVec = translation;
  update();
}

void OpenGLController::setRotation(QVector3D rotation)
{
  rotationVec = rotation;
  update();
}
void OpenGLController::calcSizes(int w, int h)
{
  vw = w;
  vh = h;
  ratio = vw / vh;
}

void OpenGLController::setDrawArrConfig(struct glDrawArraysConfig config)
{
  drawArrConf = config;
  update();
}

void OpenGLController::setCameraConfig(struct cameraConfig config)
{
  cameraConf = config;
  if (camera) {
    camera->setMode(cameraConf.Mode);
    camera->setFocusPoint(cameraConf.FocusPoint);
    camera->setPosition(cameraConf.Position);
    update();
  }
}
std::vector<QImage> OpenGLController::getScreencast() {
  std::vector<QImage> gifFrames;
  int totalFrames = gifFps * gifLength;

  float animationAnglePerSecond = 360 / totalFrames;
  float animationCurentAngle = rotationVec.y();
  float rememberAngle = animationCurentAngle;
  for (int currentFrame = 0; currentFrame < totalFrames; currentFrame++) {
    QImage frame = grabFramebuffer();
    frame = frame.scaled(gifResolution);
    gifFrames.push_back(frame);
    animationCurentAngle += animationAnglePerSecond;
    rotationVec.setY(animationCurentAngle);
    update();
  }
  rotationVec.setY(rememberAngle);
  update();
  return gifFrames;
}
void OpenGLController::capture() {
  QImage frame = grabFramebuffer();
  frame = frame.scaled(gifResolution);
  captureBuffer.push_back(frame);
}
void OpenGLController::startScreenCapture(int FPS) {
  connect(&captureTimer, SIGNAL(timeout()), this, SLOT(capture()));
  captureTimer.start(1000 / FPS);
}
std::vector<QImage> OpenGLController::stopScreenCapture() {
  captureTimer.stop();
  return captureBuffer;
}
void OpenGLController::importObjFile(QString filename)
{
  if (!geometries) return;
  makeCurrent();
  geometries->importObj(filename);
  QFileInfo fileInfo(filename);
  update();
  emit importComleted(geometries->verticesN, geometries->verticesN/3 * 2, fileInfo.fileName());
}
OpenGLController::~OpenGLController() {
  delete geometries;
  delete program;
  delete camera;
}
