#include "OGLWidget.h"

#include <QApplication>
#include <QFileInfo>
#include <QMouseEvent>
#include <QThread>
#include <QTimer>
namespace s21 {
void OGLWidget::mousePressEvent(QMouseEvent *e) {
  if (e->button() == Qt::LeftButton) {
    LMB_pressed_ = true;
    if (!camera_spacer_) return;
    camera_spacer_->mousePressSlot(e);
  }
}

void OGLWidget::mouseMoveEvent(QMouseEvent *e) {
  if (!LMB_pressed_ || !camera_spacer_) return;
  camera_spacer_->mouseMoveSlot(e);
}

void OGLWidget::mouseReleaseEvent(QMouseEvent *e) {
  if (e->button() == Qt::LeftButton) {
    LMB_pressed_ = false;
    if (camera_spacer_) camera_spacer_->mouseReleaseSlot(e);
  }
}

void OGLWidget::keyPressEvent(QKeyEvent *e) {
  if (camera_spacer_) camera_spacer_->keyPressSlot(e);
}
void OGLWidget::keyReleaseEvent(QKeyEvent *e) {
  if (camera_spacer_) camera_spacer_->keyReleaseSlot(e);
}

void OGLWidget::wheelEvent(QWheelEvent *e) {
  if (camera_spacer_) camera_spacer_->wheelEventSlot(e);
}
void OGLWidget::initializeGL() {
  setAutoFillBackground(false);
  initializeOpenGLFunctions();
  connect(&capture_timer_, &QTimer::timeout, this, &OGLWidget::CaptureBuffer);
  makeCurrent();
  QSize winSize = this->size();
  CalcSizes(winSize.width(), winSize.height());
  engine_spacer_.InitializeEngine();
  auto cam = engine_spacer_.GetCurrentCamera();
  if (cam) {
    cam->SetVh(vh_);
    cam->SetVw(vw_);
  }
  emit Initialized();
}

void OGLWidget::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
  CalcSizes(w, h);
  update();
}
void OGLWidget::paintGL() {
  makeCurrent();
  engine_spacer_.RequestRenderCycle();
  doneCurrent();
}
void OGLWidget::CalcSizes(int w, int h) {
  vw_ = w;
  vh_ = h;
  if (camera_spacer_) camera_spacer_->SetVh(vh_);
  if (camera_spacer_) camera_spacer_->SetVw(vw_);
}
void OGLWidget::CaptureBuffer() {
  QCoreApplication::processEvents();
  makeCurrent();
  if (fps_count_ < gif_fps_ * gif_length_) {
    if (gif_animation_) {
      auto obj = engine_spacer_.GetLastObject3D();
      if (obj) {
        auto &transform = obj->GetTrasform();
        auto rot = transform.GetRotation();
        transform.SetRotation(rot + 360.0 / gif_length_ / gif_fps_);
      }
    }
    this->context()->functions()->glFinish();
    capture_buffer_.push_back(grabFramebuffer().scaled(gif_resolution_));
    fps_count_++;
    update();
  } else {
    capture_timer_.stop();
  }
  doneCurrent();
}

void OGLWidget::StartScreenCapture(unsigned FPS, unsigned length,
                                   bool animated) {
  capture_buffer_.clear();
  fps_count_ = 0;
  gif_fps_ = FPS;
  gif_length_ = length;
  gif_animation_ = animated;
  capture_timer_.start(1000 / gif_fps_);
}

QImage OGLWidget::GetScreenShot() {
  makeCurrent();
  this->context()->functions()->glFinish();
  return grabFramebuffer();
}
std::vector<QImage> OGLWidget::StopScreenCapture() {
  capture_timer_.stop();
  gif_animation_ = false;
  return capture_buffer_;
}

void OGLWidget::SetCameraSpacer(CameraSpacer *spacer) {
  camera_spacer_ = spacer;
  if (!camera_spacer_) return;
  engine_spacer_.SetCurrentCamera(camera_spacer_->GetCamera());
  camera_spacer_->SetVh(vh_);
  camera_spacer_->SetVw(vw_);
  update();
}
OGLWidget::~OGLWidget() {}
}  // namespace s21
