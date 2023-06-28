#include "TripletWidget.h"

#include "ui_TripletWidget.h"

TripletWidget::TripletWidget(QWidget* parent)
    : QWidget(parent), ui(new Ui::TripletWidget) {
  ui->setupUi(this);
  connect(ui->firstV, SIGNAL(valueChanged(double)), this,
          SLOT(ReadInput(double)));
  connect(ui->secondV, SIGNAL(valueChanged(double)), this,
          SLOT(ReadInput(double)));
  connect(ui->thirdV, SIGNAL(valueChanged(double)), this,
          SLOT(ReadInput(double)));
}

TripletWidget::~TripletWidget() { delete ui; }

void TripletWidget::SetValues(const QVector3D& values) {
  if (values == this->values) return;
  this->values = values;
  UpdateInputs();
}

QVector3D TripletWidget::GetValues() const { return values; }

void TripletWidget::ResetValues() {
  values.setX(0);
  values.setY(0);
  values.setZ(0);
  UpdateInputs();
}

void TripletWidget::Lock() {
  ui->firstV->setDisabled(true);
  ui->secondV->setDisabled(true);
  ui->thirdV->setDisabled(true);
}

void TripletWidget::Unlock() {
  ui->firstV->setEnabled(true);
  ui->secondV->setEnabled(true);
  ui->thirdV->setEnabled(true);
}

void TripletWidget::UpdateInputs() {
  ui->firstV->setValue(values.x());
  ui->secondV->setValue(values.y());
  ui->thirdV->setValue(values.z());
  emit InputsChanged(values);
}

void TripletWidget::ReadInput(double val) {
  QDoubleSpinBox* wid = (QDoubleSpinBox*)sender();
  if (!wid) return;
  if (wid == ui->firstV) values.setX(val);
  if (wid == ui->secondV) values.setY(val);
  if (wid == ui->thirdV) values.setZ(val);
  emit InputsChanged(values);
}
