#include "LightConfig/LightConfigView.h"

#include "ui_LightConfigView.h"

namespace s21 {
LightConfigView::LightConfigView(QWidget *parent)
    : ConfigWidget(parent), ui(new Ui::LightConfigView) {
  Setup();
}

LightConfigView::LightConfigView(s21::LightSpacer *light_spacer,
                                 QWidget *parent)
    : LightConfigView(parent) {
  SetLightSpacer(light_spacer);
}

LightConfigView::~LightConfigView() {
  if (light_spacer_) delete light_spacer_;
  delete ui;
}

void LightConfigView::SetLightSpacer(s21::LightSpacer *light_spacer) {
  if (light_spacer_) delete light_spacer_;
  light_spacer_ = light_spacer;
  if (!light_spacer_) return;
  SetValuesFromConfig();
}

void LightConfigView::SetValuesFromConfig() {
  if (!light_spacer_) return;
  ui->LightColorTriplet->SetValues(light_spacer_->GetColor());
  ui->LightPositionTriplet->SetValues(light_spacer_->GetPosition());
  ui->LightStrengthSB->setValue(light_spacer_->GetStrength());
}

void LightConfigView::SetPosition(const Vector3D &new_position) {
  if (!light_spacer_) return;
  light_spacer_->SetPosition(new_position);
  emit UpdateRequest();
}
void LightConfigView::SetColor(const Vector3D &new_color) {
  if (!light_spacer_) return;
  light_spacer_->SetColor(new_color);
  emit UpdateRequest();
}
void LightConfigView::SetStrength(float new_strength) {
  if (!light_spacer_) return;
  light_spacer_->SetStrength(new_strength);
  emit UpdateRequest();
}

void LightConfigView::Setup() {
  if (ui) ui->setupUi(this);
  ui->LightColorTriplet->SetTexts("r:", "g:", "b:");
  ui->LightPositionTriplet->SetTexts("x:", "y:", "z:");

  ui->LightColorTriplet->SetRange(0, 255);
  ui->LightPositionTriplet->SetRange(-100000, 100000);

  ui->LightColorTriplet->SetStep(1);
  ui->LightPositionTriplet->SetStep(1);
  ui->LightStrengthSB->setSingleStep(0.001);
  ui->LightStrengthSB->setDecimals(4);

  connect(ui->LightColorTriplet, &TripletWidget::InputsChanged, this,
          &LightConfigView::SetColor);
  connect(ui->LightPositionTriplet, &TripletWidget::InputsChanged, this,
          &LightConfigView::SetPosition);
  connect(ui->LightStrengthSB, &QDoubleSpinBox::valueChanged, this,
          &LightConfigView::SetStrength);
}
}  // namespace s21
