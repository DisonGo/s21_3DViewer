#include "camerawidget.h"
#include "ui_camerawidget.h"

CameraWidget::CameraWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::CameraWidget)
{
  ui->setupUi(this);
  SetupConnects();
}

CameraWidget::CameraWidget(Camera *camera, QWidget *parent) :
  QWidget(parent),
  ui(new Ui::CameraWidget)
{
  ui->setupUi(this);
  SetCamera(camera);
  SetupConnects();
}

CameraWidget::~CameraWidget()
{
  delete ui;
}

void CameraWidget::SetCamera(Camera *camera)
{
  this->camera = camera;
  if (!camera) return;
  SetValuesFromConfig(camera->assembleConfig());
  connect(camera, SIGNAL(ConfigUpdated(Camera::CameraConfig)), this, SLOT(SetValuesFromConfig(Camera::CameraConfig)));
}

void CameraWidget::SetValuesFromConfig(const Camera::CameraConfig &config)
{
  this->config = config;
  ui->PositionTriplet->SetValues(config.Position);
  ui->OrientationTriplet->SetValues(config.Orientation);
  ui->FocusPointTriplet->SetValues(config.FocusPoint);

  ui->zRangeXV->setValue(config.zRange.x());
  ui->zRangeYV->setValue(config.zRange.y());

  switch(config.Mode) {
    case Camera::Free:
      ui->CameraModeFree->setChecked(true);
      break;
    case Camera::Focus:
      ui->CameraModeFocus->setChecked(true);
      break;
  }

  switch(config.viewMode) {
    case Camera::Perspective:
      ui->ViewModePerspective->setChecked(true);
      break;
    case Camera::Orthographic:
      ui->ViewModeParallel->setChecked(true);
      break;
  }
  ui->LeftV->setValue(config.boxLeft);
  ui->RightV->setValue(config.boxRight);
  ui->BottomV->setValue(config.boxBottom);
  ui->TopV->setValue(config.boxTop);
}

void CameraWidget::SetPosition(const QVector3D &position)
{
  if (!camera) return;
  config.Position = position;
  camera->SetConfig(config);
}

void CameraWidget::SetOrientation(const QVector3D &orientation)
{
  if (!camera) return;
  config.Orientation = orientation;
  camera->SetConfig(config);
}

void CameraWidget::SetFocusPoint(const QVector3D &focusPoint)
{
  if (!camera) return;
  config.FocusPoint = focusPoint;
  camera->SetConfig(config);
}

void CameraWidget::SetCameraMode(QAbstractButton *but)
{
  if (!camera) return;
  if (but == ui->CameraModeFocus)
    config.Mode = Camera::Focus;
  if (but == ui->CameraModeFree)
    config.Mode = Camera::Free;
  camera->SetConfig(config);
}

void CameraWidget::SetViewMode(QAbstractButton *but)
{
  if (!camera) return;
  if (but == ui->ViewModePerspective)
    config.viewMode = Camera::Perspective;
  if (but == ui->ViewModeParallel)
    config.viewMode = Camera::Orthographic;
  camera->SetConfig(config);
}

void CameraWidget::SetZNear(double val)
{
  if (!camera) return;
  config.zRange.setX(val);
  camera->SetConfig(config);
}

void CameraWidget::SetZFar(double val)
{
  if (!camera) return;
  config.zRange.setY(val);
  camera->SetConfig(config);
}

void CameraWidget::SetBoxLeft(double val)
{
  if (!camera) return;
  config.boxLeft = val;
  camera->SetConfig(config);
}

void CameraWidget::SetBoxRight(double val)
{
  if (!camera) return;
  config.boxRight = val;
  camera->SetConfig(config);
}

void CameraWidget::SetBoxBottom(double val)
{
  if (!camera) return;
  config.boxBottom = val;
  camera->SetConfig(config);
}

void CameraWidget::SetBoxTop(double val)
{
  if (!camera) return;
  config.boxTop = val;
  camera->SetConfig(config);
}

void CameraWidget::SetupConnects()
{
  connect(ui->PositionTriplet ,SIGNAL(InputsChanged(QVector3D)), this, SLOT(SetPosition(QVector3D)));
  connect(ui->OrientationTriplet ,SIGNAL(InputsChanged(QVector3D)), this, SLOT(SetOrientation(QVector3D)));
  connect(ui->FocusPointTriplet ,SIGNAL(InputsChanged(QVector3D)), this, SLOT(SetFocusPoint(QVector3D)));
  connect(ui->CameraModeG ,SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(SetCameraMode(QAbstractButton*)));
  connect(ui->ViewModeG ,SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(SetViewMode(QAbstractButton*)));
  connect(ui->zRangeXV ,SIGNAL(valueChanged(double)), this, SLOT(SetZNear(double)));
  connect(ui->zRangeYV ,SIGNAL(valueChanged(double)), this, SLOT(SetZFar(double)));
  connect(ui->LeftV ,SIGNAL(valueChanged(double)), this, SLOT(SetBoxLeft(double)));
  connect(ui->RightV ,SIGNAL(valueChanged(double)), this, SLOT(SetBoxRight(double)));
  connect(ui->BottomV ,SIGNAL(valueChanged(double)), this, SLOT(SetBoxBottom(double)));
  connect(ui->TopV ,SIGNAL(valueChanged(double)), this, SLOT(SetBoxTop(double)));
}

void CameraWidget::on_ResetBut_clicked()
{
  if (!camera) return;
  camera->SetConfig(Camera::CameraConfig());
  SetValuesFromConfig(Camera::CameraConfig());

}

