#include "CameraConfig/CameraConfigView.h"

#include "ui_CameraConfigView.h"
CameraConfigView::CameraConfigView(QWidget *parent, CameraSpacer *cameraSpacer)
    : QWidget(parent), ui(new Ui::CameraConfigView) {
  ui->setupUi(this);
  SetCameraSpacer(cameraSpacer);
  SetupConnects();
}

CameraConfigView::~CameraConfigView() { delete ui; }

void CameraConfigView::SetCameraSpacer(CameraSpacer *cameraSpacer) {
  cameraSpacer_ = cameraSpacer;
  if (!cameraSpacer) return;
  connect(cameraSpacer_, SIGNAL(ConfigUpdated()), this,
          SLOT(SetValuesFromConfig()));
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
    case Camera::Free:
      ui->CameraModeFree->setChecked(true);
      break;
    case Camera::Focus:
      ui->CameraModeFocus->setChecked(true);
      break;
  }

  switch (cameraSpacer_->GetViewMode()) {
    case Camera::Perspective:
      ui->ViewModePerspective->setChecked(true);
      break;
    case Camera::Orthographic:
      ui->ViewModeParallel->setChecked(true);
      break;
  }
  auto box = cameraSpacer_->GetBox();
  ui->TopV->setValue(box.top);
  ui->RightV->setValue(box.right);
  ui->BottomV->setValue(box.bottom);
  ui->LeftV->setValue(box.left);
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
  if (but == ui->CameraModeFocus) cameraSpacer_->SetMode(Camera::Focus);
  if (but == ui->CameraModeFree) cameraSpacer_->SetMode(Camera::Free);
  emit UpdateRequest();
}

void CameraConfigView::SetViewMode(QAbstractButton *but) {
  if (!cameraSpacer_) return;
  if (but == ui->ViewModePerspective)
    cameraSpacer_->SetViewMode(Camera::Perspective);
  if (but == ui->ViewModeParallel)
    cameraSpacer_->SetViewMode(Camera::Orthographic);
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
  box.left = val;
  cameraSpacer_->SetBox(box);
  emit UpdateRequest();
}

void CameraConfigView::SetBoxRight(double val) {
  if (!cameraSpacer_) return;
  auto box = cameraSpacer_->GetBox();
  box.right = val;
  cameraSpacer_->SetBox(box);
  emit UpdateRequest();
}

void CameraConfigView::SetBoxBottom(double val) {
  if (!cameraSpacer_) return;
  auto box = cameraSpacer_->GetBox();
  box.bottom = val;
  cameraSpacer_->SetBox(box);
  emit UpdateRequest();
}

void CameraConfigView::SetBoxTop(double val) {
  if (!cameraSpacer_) return;
  auto box = cameraSpacer_->GetBox();
  box.top = val;
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
}

// void CameraConfigView::on_ResetBut_clicked() {
//   if (!camera_) return;
//   camera->SetConfig(Camera::CameraConfig());
//   SetValuesFromConfig(Camera::CameraConfig());
// }
