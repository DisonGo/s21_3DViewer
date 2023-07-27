#include "CameraConfig/CameraConfigView.h"

#include "ui_CameraConfigView.h"
CameraConfigView::CameraConfigView(s21::CameraSpacer *cameraSpacer,
                                   QWidget *parent)
    : ConfigWidget(parent), ui(new Ui::CameraConfigView) {
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

s21::CameraSpacer *CameraConfigView::GetCameraSpacer() { return cameraSpacer_; }

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

  ui->zRangeXV->setValue(zRange.X());
  ui->zRangeYV->setValue(zRange.Y());

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

void CameraConfigView::SetPosition(const Vector3D &position) {
  if (!cameraSpacer_) return;
  cameraSpacer_->SetPosition(position);
  emit UpdateRequest();
}

void CameraConfigView::SetOrientation(const Vector3D &orientation) {
  if (!cameraSpacer_) return;
  cameraSpacer_->SetOrientation(orientation);
  emit UpdateRequest();
}

void CameraConfigView::SetFocusPoint(const Vector3D &focusPoint) {
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
  zRange.SetX(val);
  cameraSpacer_->SetZRange(zRange);
  emit UpdateRequest();
}

void CameraConfigView::SetZFar(double val) {
  if (!cameraSpacer_) return;
  auto zRange = cameraSpacer_->GetZRange();
  zRange.SetY(val);
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
  connect(ui->PositionTriplet, SIGNAL(InputsChanged(Vector3D)), this,
          SLOT(SetPosition(Vector3D)));
  connect(ui->OrientationTriplet, SIGNAL(InputsChanged(Vector3D)), this,
          SLOT(SetOrientation(Vector3D)));
  connect(ui->FocusPointTriplet, SIGNAL(InputsChanged(Vector3D)), this,
          SLOT(SetFocusPoint(Vector3D)));
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
