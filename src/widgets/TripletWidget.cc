#include "TripletWidget.h"

#include "ui_TripletWidget.h"
namespace s21 {
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

void TripletWidget::SetValues(const Vector3D& values) {
  if (values == this->values) return;
  this->values = values;
  UpdateInputs();
}

void TripletWidget::SetStep(double step) {
  static constexpr double EPS = 1e-2;
  if (step < EPS) return;
  ui->firstV->setSingleStep(step);
  ui->secondV->setSingleStep(step);
  ui->thirdV->setSingleStep(step);
}

Vector3D TripletWidget::GetValues() const { return values; }

void TripletWidget::ResetValues() {
  ui->firstV->setRange(-10000, 10000);
  ui->secondV->setRange(-10000, 10000);
  ui->thirdV->setRange(-10000, 10000);
  values.SetX(0);
  values.SetY(0);
  values.SetZ(0);
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

void TripletWidget::SetRangeMin(double min) {
  ui->firstV->setMinimum(min);
  ui->secondV->setMinimum(min);
  ui->thirdV->setMinimum(min);
}

void TripletWidget::SetRangeMax(double max) {
  ui->firstV->setMaximum(max);
  ui->secondV->setMaximum(max);
  ui->thirdV->setMaximum(max);
}

void TripletWidget::SetRange(double min, double max) {
  if (min > max) std::swap(min, max);
  SetRangeMin(min);
  SetRangeMax(max);
}

void TripletWidget::UpdateInputs() {
  ui->firstV->setValue(values.X());
  ui->secondV->setValue(values.Y());
  ui->thirdV->setValue(values.Z());
  emit InputsChanged(values);
}

void TripletWidget::ReadInput(double val) {
  QDoubleSpinBox* wid = (QDoubleSpinBox*)sender();
  if (!wid) return;
  if (wid == ui->firstV) values.SetX(val);
  if (wid == ui->secondV) values.SetY(val);
  if (wid == ui->thirdV) values.SetZ(val);
  emit InputsChanged(values);
}
}  // namespace s21
