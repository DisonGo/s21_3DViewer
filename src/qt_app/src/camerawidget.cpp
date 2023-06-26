#include "camerawidget.h"

#include "ui_camerawidget.h"
CameraWidget::CameraWidget(QWidget *parent, CameraSpacer *cameraSpacer)
    : QWidget(parent), ui(new Ui::CameraWidget) {
  ui->setupUi(this);
  SetCameraSpacer(cameraSpacer);
  SetupConnects();
}

CameraWidget::~CameraWidget() { delete ui; }

void CameraWidget::SetCameraSpacer(CameraSpacer *cameraSpacer) {
  cameraSpacer_ = cameraSpacer;
  config_ = nullptr;
  if (!cameraSpacer) return;
  SetConfig(&cameraSpacer_->GetConfig());
  connect(cameraSpacer_, SIGNAL(ConfigUpdated()), this,
          SLOT(SetValuesFromConfig()));
}

void CameraWidget::SetValuesFromConfig() {
  if (!config_) return;
  ui->PositionTriplet->SetValues(config_->Position);
  ui->OrientationTriplet->SetValues(config_->Orientation);
  ui->FocusPointTriplet->SetValues(config_->FocusPoint);

  ui->zRangeXV->setValue(config_->zRange.x());
  ui->zRangeYV->setValue(config_->zRange.y());

  switch (config_->Mode) {
    case Camera::Free:
      ui->CameraModeFree->setChecked(true);
      break;
    case Camera::Focus:
      ui->CameraModeFocus->setChecked(true);
      break;
  }

  switch (config_->viewMode) {
    case Camera::Perspective:
      ui->ViewModePerspective->setChecked(true);
      break;
    case Camera::Orthographic:
      ui->ViewModeParallel->setChecked(true);
      break;
  }
  ui->TopV->setValue(config_->box.top);
  ui->RightV->setValue(config_->box.right);
  ui->BottomV->setValue(config_->box.bottom);
  ui->LeftV->setValue(config_->box.left);
}

void CameraWidget::SetPosition(const QVector3D &position) {
  if (!cameraSpacer_) return;
  config_->Position = position;
}

void CameraWidget::SetOrientation(const QVector3D &orientation) {
  if (!cameraSpacer_) return;
  config_->Orientation = orientation;
}

void CameraWidget::SetFocusPoint(const QVector3D &focusPoint) {
  if (!cameraSpacer_) return;
  config_->FocusPoint = focusPoint;
}

void CameraWidget::SetCameraMode(QAbstractButton *but) {
  if (!cameraSpacer_) return;
  if (but == ui->CameraModeFocus) config_->Mode = Camera::Focus;
  if (but == ui->CameraModeFree) config_->Mode = Camera::Free;
}

void CameraWidget::SetViewMode(QAbstractButton *but) {
  if (!cameraSpacer_) return;
  if (but == ui->ViewModePerspective) config_->viewMode = Camera::Perspective;
  if (but == ui->ViewModeParallel) config_->viewMode = Camera::Orthographic;
}

void CameraWidget::SetZNear(double val) {
  if (!cameraSpacer_) return;
  config_->zRange.setX(val);
}

void CameraWidget::SetZFar(double val) {
  if (!cameraSpacer_) return;
  config_->zRange.setY(val);
}

void CameraWidget::SetBoxLeft(double val) {
  if (!cameraSpacer_) return;
  config_->box.left = val;
}

void CameraWidget::SetBoxRight(double val) {
  if (!cameraSpacer_) return;
  config_->box.right = val;
}

void CameraWidget::SetBoxBottom(double val) {
  if (!cameraSpacer_) return;
  config_->box.bottom = val;
}

void CameraWidget::SetBoxTop(double val) {
  if (!cameraSpacer_) return;
  config_->box.top = val;
}

void CameraWidget::SetupConnects() {
  connect(ui->PositionTriplet, SIGNAL(InputsChanged(QVector3D)), this,
          SLOT(SetPosition(QVector3D)));
  connect(ui->OrientationTriplet, SIGNAL(InputsChanged(QVector3D)), this,
          SLOT(SetOrientation(QVector3D)));
  connect(ui->FocusPointTriplet, SIGNAL(InputsChanged(QVector3D)), this,
          SLOT(SetFocusPoint(QVector3D)));
  connect(ui->CameraModeG, SIGNAL(buttonClicked(QAbstractButton *)), this,
          SLOT(SetCameraMode(QAbstractButton *)));
  connect(ui->ViewModeG, SIGNAL(buttonClicked(QAbstractButton *)), this,
          SLOT(SetViewMode(QAbstractButton *)));
  connect(ui->zRangeXV, SIGNAL(valueChanged(double)), this,
          SLOT(SetZNear(double)));
  connect(ui->zRangeYV, SIGNAL(valueChanged(double)), this,
          SLOT(SetZFar(double)));
  connect(ui->LeftV, SIGNAL(valueChanged(double)), this,
          SLOT(SetBoxLeft(double)));
  connect(ui->RightV, SIGNAL(valueChanged(double)), this,
          SLOT(SetBoxRight(double)));
  connect(ui->BottomV, SIGNAL(valueChanged(double)), this,
          SLOT(SetBoxBottom(double)));
  connect(ui->TopV, SIGNAL(valueChanged(double)), this,
          SLOT(SetBoxTop(double)));
}

// void CameraWidget::on_ResetBut_clicked() {
//   if (!camera_) return;
//   camera->SetConfig(Camera::CameraConfig());
//   SetValuesFromConfig(Camera::CameraConfig());
// }

void CameraWidget::SetConfig(Camera::CameraConfig *config) {
  if (!config) return;
  config_ = config;
  SetValuesFromConfig();
}
