#include "TripletWidget.h"

#include "ui_TripletWidget.h"
namespace s21 {
TripletWidget::TripletWidget(QWidget *parent)
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

void TripletWidget::SetValues(const Vector3D &values) {
  if (values == this->values_) return;
  this->values_ = values;
  UpdateInputs();
}

void TripletWidget::SetStep(double step) {
  static constexpr double EPS = 1e-2;
  if (step < EPS) return;
  ui->firstV->setSingleStep(step);
  ui->secondV->setSingleStep(step);
  ui->thirdV->setSingleStep(step);
}

Vector3D TripletWidget::GetValues() const { return values_; }

void TripletWidget::ResetValues() {
  ui->firstV->setRange(-10000, 10000);
  ui->secondV->setRange(-10000, 10000);
  ui->thirdV->setRange(-10000, 10000);
  values_.SetX(0);
  values_.SetY(0);
  values_.SetZ(0);
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

void TripletWidget::SetDecimals(size_t count) {
  ui->firstV->setDecimals(count);
  ui->secondV->setDecimals(count);
  ui->thirdV->setDecimals(count);
}

void TripletWidget::SetTexts(const char *first, const char *second,
                             const char *third) {
  SetFirstText(first);
  SetSecondText(second);
  SetThirdText(third);
}

void TripletWidget::SetFirstText(const char *text) {
  ui->firstL->setText(text);
}

void TripletWidget::SetSecondText(const char *text) {
  ui->secondL->setText(text);
}

void TripletWidget::SetThirdText(const char *text) {
  ui->thirdL->setText(text);
}

void TripletWidget::UpdateInputs() {
  ui->firstV->setValue(values_.X());
  ui->secondV->setValue(values_.Y());
  ui->thirdV->setValue(values_.Z());
  emit InputsChanged(values_);
}

void TripletWidget::ReadInput(double val) {
  QDoubleSpinBox *wid = (QDoubleSpinBox *)sender();
  if (!wid) return;
  if (wid == ui->firstV) values_.SetX(val);
  if (wid == ui->secondV) values_.SetY(val);
  if (wid == ui->thirdV) values_.SetZ(val);
  emit InputsChanged(values_);
}
}  // namespace s21
