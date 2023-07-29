#include "CameraConfig/CameraConfigView.h"

#include "ui_CameraConfigView.h"
namespace s21 {
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
  if (camera_spacer_) delete camera_spacer_;
  delete ui;
}

s21::CameraSpacer *CameraConfigView::GetCameraSpacer() { return camera_spacer_; }

void CameraConfigView::SetCameraSpacer(s21::CameraSpacer *cameraSpacer) {
  camera_spacer_ = cameraSpacer;
  if (!cameraSpacer) return;
  connect(camera_spacer_, SIGNAL(ConfigUpdated()), this,
          SLOT(SetValuesFromConfig()));
  SetValuesFromConfig();
}

void CameraConfigView::SetValuesFromConfig() {
  if (!camera_spacer_) return;
  ui->PositionTriplet->SetValues(camera_spacer_->GetPosition());
  ui->OrientationTriplet->SetValues(camera_spacer_->GetOrientation());
  ui->FocusPointTriplet->SetValues(camera_spacer_->GetFocusPoint());

  auto zRange = camera_spacer_->GetZRange();

  ui->zRangeXV->setValue(zRange.X());
  ui->zRangeYV->setValue(zRange.Y());

  switch (camera_spacer_->GetMode()) {
    case s21::Camera::kFree:
      ui->CameraModeFree->setChecked(true);
      break;
    case s21::Camera::kFocus:
      ui->CameraModeFocus->setChecked(true);
      break;
  }

  switch (camera_spacer_->GetViewMode()) {
    case s21::Camera::kPerspective:
      ui->ViewModePerspective->setChecked(true);
      break;
    case s21::Camera::kOrthographic:
      ui->ViewModeParallel->setChecked(true);
      break;
  }
  auto box = camera_spacer_->GetBox();
  ui->FOV_V->setValue(camera_spacer_->GetFOV());
  ui->TopV->setValue(box.top_);
  ui->RightV->setValue(box.right_);
  ui->BottomV->setValue(box.bottom_);
  ui->LeftV->setValue(box.left_);
  emit UpdateRequest();
}

void CameraConfigView::SetPosition(const Vector3D &position) {
  if (!camera_spacer_) return;
  camera_spacer_->SetPosition(position);
  emit UpdateRequest();
}

void CameraConfigView::SetOrientation(const Vector3D &orientation) {
  if (!camera_spacer_) return;
  camera_spacer_->SetOrientation(orientation);
  emit UpdateRequest();
}

void CameraConfigView::SetFocusPoint(const Vector3D &focusPoint) {
  if (!camera_spacer_) return;
  camera_spacer_->SetFocusPoint(focusPoint);
  emit UpdateRequest();
}

void CameraConfigView::SetCameraMode(QAbstractButton *but) {
  if (!camera_spacer_) return;
  if (but == ui->CameraModeFocus) camera_spacer_->SetMode(s21::Camera::kFocus);
  if (but == ui->CameraModeFree) camera_spacer_->SetMode(s21::Camera::kFree);
  emit UpdateRequest();
}

void CameraConfigView::SetViewMode(QAbstractButton *but) {
  if (!camera_spacer_) return;
  if (but == ui->ViewModePerspective)
    camera_spacer_->SetViewMode(s21::Camera::kPerspective);
  if (but == ui->ViewModeParallel)
    camera_spacer_->SetViewMode(s21::Camera::kOrthographic);
  emit UpdateRequest();
}

void CameraConfigView::SetFOV(int val) {
  if (!camera_spacer_) return;
  camera_spacer_->SetFOV(val);
  emit UpdateRequest();
}

void CameraConfigView::SetZNear(double val) {
  if (!camera_spacer_) return;
  auto zRange = camera_spacer_->GetZRange();
  zRange.SetX(val);
  camera_spacer_->SetZRange(zRange);
  emit UpdateRequest();
}

void CameraConfigView::SetZFar(double val) {
  if (!camera_spacer_) return;
  auto zRange = camera_spacer_->GetZRange();
  zRange.SetY(val);
  camera_spacer_->SetZRange(zRange);
  emit UpdateRequest();
}

void CameraConfigView::SetBoxLeft(double val) {
  if (!camera_spacer_) return;
  auto box = camera_spacer_->GetBox();
  box.left_ = val;
  camera_spacer_->SetBox(box);
  emit UpdateRequest();
}

void CameraConfigView::SetBoxRight(double val) {
  if (!camera_spacer_) return;
  auto box = camera_spacer_->GetBox();
  box.right_ = val;
  camera_spacer_->SetBox(box);
  emit UpdateRequest();
}

void CameraConfigView::SetBoxBottom(double val) {
  if (!camera_spacer_) return;
  auto box = camera_spacer_->GetBox();
  box.bottom_ = val;
  camera_spacer_->SetBox(box);
  emit UpdateRequest();
}

void CameraConfigView::SetBoxTop(double val) {
  if (!camera_spacer_) return;
  auto box = camera_spacer_->GetBox();
  box.top_ = val;
  camera_spacer_->SetBox(box);
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
}  // namespace s21
