#include "CameraConfig/CameraConfigView.h"

#include "ui_CameraConfigView.h"
CameraConfigView::CameraConfigView(QWidget *parent, s21::CameraSpacer *cameraSpacer)
    : QWidget(parent), ui(new Ui::CameraConfigView) {
  ui->setupUi(this);
  ui->PositionTriplet->SetRange(-10000, 10000);
  ui->FocusPointTriplet->SetRange(-10000, 10000);
  ui->OrientationTriplet->SetRange(-10000, 10000);
  ui->zRangeYV->setSingleStep(100);
  ui->zRangeXV->setSingleStep(0.1);
  SetCameraSpacer(cameraSpacer);
  SetupConnects();
}

CameraConfigView::~CameraConfigView() {
  if (cameraSpacer_) delete cameraSpacer_;
  delete ui;
}

void CameraConfigView::SetCameraSpacer(s21::CameraSpacer *cameraSpacer) {
  cameraSpacer_ = cameraSpacer;
  if (!cameraSpacer) return;
  connect(cameraSpacer_, SIGNAL(ConfigUpdated()), this,
          SLOT(SetValuesFromConfig()));
  SetValuesFromConfig();
}

void CameraConfigView::SetValuesFromConfig() {
  if (!cameraSpacer_) return;
  ui->PositionTriplet->SetValues(cameraSpacer_->GetPosition());
  ui->OrientationTriplet->SetValues(cameraSpacer_->GetOrientation());
  ui->FocusPointTriplet->SetValues(cameraSpacer_->GetFocusPoint());

  auto zRange = cameraSpacer_->GetZRange();

  ui->zRangeXV->setValue(zRange.x());
  ui->zRangeYV->setValue(zRange.y());

  switch (cameraSpacer_->GetMode()) {
    case s21::Camera::kFree:
      ui->CameraModeFree->setChecked(true);
      break;
    case s21::Camera::kFocus:
      ui->CameraModeFocus->setChecked(true);
      break;
  }

  switch (cameraSpacer_->GetViewMode()) {
    case s21::Camera::kPerspective:
      ui->ViewModePerspective->setChecked(true);
      break;
    case s21::Camera::kOrthographic:
      ui->ViewModeParallel->setChecked(true);
      break;
  }
  auto box = cameraSpacer_->GetBox();
  ui->FOV_V->setValue(cameraSpacer_->GetFOV());
  ui->TopV->setValue(box.top_);
  ui->RightV->setValue(box.right_);
  ui->BottomV->setValue(box.bottom_);
  ui->LeftV->setValue(box.left_);
  emit UpdateRequest();
}

void CameraConfigView::SetPosition(const QVector3D &position) {
  if (!cameraSpacer_) return;
  cameraSpacer_->SetPosition(position);
  emit UpdateRequest();
}

void CameraConfigView::SetOrientation(const QVector3D &orientation) {
  if (!cameraSpacer_) return;
  cameraSpacer_->SetOrientation(orientation);
  emit UpdateRequest();
}

void CameraConfigView::SetFocusPoint(const QVector3D &focusPoint) {
  if (!cameraSpacer_) return;
  cameraSpacer_->SetFocusPoint(focusPoint);
  emit UpdateRequest();
}

void CameraConfigView::SetCameraMode(QAbstractButton *but) {
  if (!cameraSpacer_) return;
  if (but == ui->CameraModeFocus) cameraSpacer_->SetMode(s21::Camera::kFocus);
  if (but == ui->CameraModeFree) cameraSpacer_->SetMode(s21::Camera::kFree);
  emit UpdateRequest();
}

void CameraConfigView::SetViewMode(QAbstractButton *but) {
  if (!cameraSpacer_) return;
  if (but == ui->ViewModePerspective)
    cameraSpacer_->SetViewMode(s21::Camera::kPerspective);
  if (but == ui->ViewModeParallel)
    cameraSpacer_->SetViewMode(s21::Camera::kOrthographic);
  emit UpdateRequest();
}

void CameraConfigView::SetFOV(int val) {
  if (!cameraSpacer_) return;
  cameraSpacer_->SetFOV(val);
  emit UpdateRequest();
}

void CameraConfigView::SetZNear(double val) {
  if (!cameraSpacer_) return;
  auto zRange = cameraSpacer_->GetZRange();
  zRange.setX(val);
  cameraSpacer_->SetZRange(zRange);
  emit UpdateRequest();
}

void CameraConfigView::SetZFar(double val) {
  if (!cameraSpacer_) return;
  auto zRange = cameraSpacer_->GetZRange();
  zRange.setY(val);
  cameraSpacer_->SetZRange(zRange);
  emit UpdateRequest();
}

void CameraConfigView::SetBoxLeft(double val) {
  if (!cameraSpacer_) return;
  auto box = cameraSpacer_->GetBox();
  box.left_ = val;
  cameraSpacer_->SetBox(box);
  emit UpdateRequest();
}

void CameraConfigView::SetBoxRight(double val) {
  if (!cameraSpacer_) return;
  auto box = cameraSpacer_->GetBox();
  box.right_ = val;
  cameraSpacer_->SetBox(box);
  emit UpdateRequest();
}

void CameraConfigView::SetBoxBottom(double val) {
  if (!cameraSpacer_) return;
  auto box = cameraSpacer_->GetBox();
  box.bottom_ = val;
  cameraSpacer_->SetBox(box);
  emit UpdateRequest();
}

void CameraConfigView::SetBoxTop(double val) {
  if (!cameraSpacer_) return;
  auto box = cameraSpacer_->GetBox();
  box.top_ = val;
  cameraSpacer_->SetBox(box);
  emit UpdateRequest();
}

void CameraConfigView::SetupConnects() {
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
  connect(ui->FOV_V, SIGNAL(valueChanged(int)), this, SLOT(SetFOV(int)));
}

// void CameraConfigView::on_ResetBut_clicked() {
//   if (!camera_) return;
//   camera->SetConfig(Camera::CameraConfig());
//   SetValuesFromConfig(Camera::CameraConfig());
// }
