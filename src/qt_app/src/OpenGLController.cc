#include "OpenGLController.h"

#include <QFileInfo>
#include <QMouseEvent>
#include <QThread>
#include <QTimer>
void OpenGLController::mousePressEvent(QMouseEvent *e) {
  if (e->button() == Qt::LeftButton) {
    LMB_pressed = true;
    if (!cameraSpacer) return;
    cameraSpacer->mousePressSlot(e);
    //    RequestUpdate();
  }
}

void OpenGLController::mouseMoveEvent(QMouseEvent *e) {
  if (!LMB_pressed || !cameraSpacer) return;
  cameraSpacer->mouseMoveSlot(e);
  //  RequestUpdate();
  update();
}

void OpenGLController::mouseReleaseEvent(QMouseEvent *e) {
  if (e->button() == Qt::LeftButton) {
    LMB_pressed = false;
    if (cameraSpacer) cameraSpacer->mouseReleaseSlot(e);
    //    RequestUpdate();
  }
}

void OpenGLController::keyPressEvent(QKeyEvent *e) {
  if (cameraSpacer) cameraSpacer->keyPressSlot(e);
  //  RequestUpdate();
  update();
}
void OpenGLController::keyReleaseEvent(QKeyEvent *e) {
  if (cameraSpacer) cameraSpacer->keyReleaseSlot(e);
  //  RequestUpdate();
  update();
}

void OpenGLController::wheelEvent(QWheelEvent *e) {
  if (cameraSpacer) cameraSpacer->wheelEventSlot(e);
  //  RequestUpdate();
  update();
}
void OpenGLController::initializeGL() {
  setAutoFillBackground(false);
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
    cam->SetVw(vw);
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
  if (cameraSpacer) cameraSpacer->SetVh(vh);
  if (cameraSpacer) cameraSpacer->SetVw(vw);
  ratio = vw / vh;
}
void OpenGLController::capture() {
  QImage frame = grabFramebuffer().scaled(gifResolution);
  captureBuffer.push_back(frame);
}

void OpenGLController::PopUpdateSchedule() {
  if (update_schedule_.empty()) return;
  update_schedule_.pop_back();
  update();
}
void OpenGLController::startScreenCapture(int FPS) {
  connect(&captureTimer, SIGNAL(timeout()), this, SLOT(capture()));
  captureTimer.start(1000 / FPS);
}
std::vector<QImage> OpenGLController::stopScreenCapture() {
  captureTimer.stop();
  return captureBuffer;
}

void OpenGLController::SetCameraSpacer(s21::CameraSpacer *spacer) {
  cameraSpacer = spacer;
  if (!cameraSpacer) return;
  engine->SetCurrentCamera(cameraSpacer->GetCamera());
  cameraSpacer->SetVh(vh);
  cameraSpacer->SetVw(vw);
  update();
}
void OpenGLController::importObjFile(QString filename) {
  if (!engine) return;
  makeCurrent();
  engine->importObj(filename);
  QFileInfo fileInfo(filename);
  update();
}

void OpenGLController::RequestUpdate() { update_schedule_.push_back(1); }
OpenGLController::~OpenGLController() {}
