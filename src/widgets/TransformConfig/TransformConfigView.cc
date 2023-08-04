#include "TransformConfig/TransformConfigView.h"

#include "ui_TransformConfigView.h"
namespace s21 {
TransformConfigView::TransformConfigView(QWidget *parent)
    : ConfigWidget(parent), ui(new Ui::TransformConfigView) {
  Setup();
}

TransformConfigView::TransformConfigView(s21::TransformSpacer *transform,
                                         QWidget *parent)
    : TransformConfigView(parent) {
  SetTranformSpacer(transform);
}
void TransformConfigView::Setup() {
  ui->setupUi(this);
  connect(ui->TranslationTriplet, SIGNAL(InputsChanged(Vector3D)), this,
          SLOT(SetTranslation(Vector3D)));
  connect(ui->RotationTriplet, SIGNAL(InputsChanged(Vector3D)), this,
          SLOT(SetRotation(Vector3D)));
  connect(ui->ScaleTriplet, SIGNAL(InputsChanged(Vector3D)), this,
          SLOT(SetScale(Vector3D)));
  ui->TranslationTriplet->SetRange(-10000, 10000);
  ui->ScaleTriplet->SetRange(-10000, 10000);
  ui->ScaleTriplet->SetStep(0.1);
  ui->RotationTriplet->SetStep(5);
  ui->RotationTriplet->SetRange(-10000, 10000);
}
TransformConfigView::~TransformConfigView() {
  if (transform_spacer_) delete transform_spacer_;
  delete ui;
}

void TransformConfigView::ResetValues() {
  ui->TranslationTriplet->ResetValues();
  ui->RotationTriplet->ResetValues();
  ui->ScaleTriplet->ResetValues();
}

void TransformConfigView::SetValuesFromConfig() {
  if (!transform_spacer_) return;
  ui->TranslationTriplet->SetValues(transform_spacer_->GetTranslate());
  ui->RotationTriplet->SetValues(transform_spacer_->GetRotation());
  ui->ScaleTriplet->SetValues(transform_spacer_->GetScale());
}

void TransformConfigView::SetTranformSpacer(
    s21::TransformSpacer *transformSpacer) {
  transform_spacer_ = transformSpacer;
  if (!transform_spacer_) return;
  connect(transform_spacer_, &s21::TransformSpacer::ConfigUpdated, this,
          &TransformConfigView::SetValuesFromConfig);
  SetValuesFromConfig();
}

void TransformConfigView::SetTranslation(const Vector3D translate) {
  if (!transform_spacer_) return;
  transform_spacer_->SetTranslate(translate);
  emit UpdateRequest();
}

void TransformConfigView::SetRotation(const Vector3D rotation) {
  if (!transform_spacer_) return;
  transform_spacer_->SetRotation(rotation);
  emit UpdateRequest();
}

void TransformConfigView::SetScale(const Vector3D scale) {
  if (!transform_spacer_) return;
  transform_spacer_->SetScale(scale);
  emit UpdateRequest();
}
}  // namespace s21
