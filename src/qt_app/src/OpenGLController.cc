#include "OpenGLController.h"

#include <QFileInfo>
#include <QMouseEvent>

void OpenGLController::mousePressEvent(QMouseEvent *e) {
  if (e->button() == Qt::LeftButton) {
    LMB_pressed = true;
    if (!cameraSpacer) return;
    cameraSpacer->mousePressSlot(e);
  }
}

void OpenGLController::mouseMoveEvent(QMouseEvent *e) {
  if (!LMB_pressed || !cameraSpacer) return;
  cameraSpacer->mouseMoveSlot(e);
  update();
}

void OpenGLController::mouseReleaseEvent(QMouseEvent *e) {
  if (e->button() == Qt::LeftButton) {
    LMB_pressed = false;
    if (cameraSpacer) cameraSpacer->mouseReleaseSlot(e);
  }
}

void OpenGLController::keyPressEvent(QKeyEvent *e) {
  if (cameraSpacer) cameraSpacer->keyPressSlot(e);
  update();
}
void OpenGLController::keyReleaseEvent(QKeyEvent *e) {
  if (cameraSpacer) cameraSpacer->keyReleaseSlot(e);
  update();
}

void OpenGLController::wheelEvent(QWheelEvent *e) {
  if (cameraSpacer) cameraSpacer->wheelEventSlot(e);
  update();
}
void OpenGLController::initializeGL() {
  initializeOpenGLFunctions();
  QSize winSize = this->size();
  calcSizes(winSize.width(), winSize.height());
  glClearColor(0, 0, 0, 1);
  glEnable(GL_PROGRAM_POINT_SIZE);
  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  engine = &s21::Engine::Instance();
  GLfloat lineWidthRange[2] = {0.0f, 0.0f};
  glGetFloatv(GL_ALIASED_LINE_WIDTH_RANGE, lineWidthRange);
  qDebug() << "Max width: " << lineWidthRange[1];

  auto cam = engine->GetCurrentCamera();
  if (cam) {
    cam->SetVh(vh);
    cam->SetVw(vh);
  }
  emit initialized();
}

void OpenGLController::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
  calcSizes(w, h);
  update();
}
void OpenGLController::paintGL() { engine->Cycle(); }
void OpenGLController::calcSizes(int w, int h) {
  vw = w;
  vh = h;
  ratio = vw / vh;
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
void OpenGLController::importObjFile(QString filename) {
  if (!engine) return;
  makeCurrent();
  engine->importObj(filename);
  QFileInfo fileInfo(filename);
  update();
  emit importComleted(engine->verticesN, engine->verticesN / 3 * 2,
                      fileInfo.fileName());
}
OpenGLController::~OpenGLController() {}
