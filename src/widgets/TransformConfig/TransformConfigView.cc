#include "TransformConfig/TransformConfigView.h"

#include "ui_TransformConfigView.h"

TransformConfigView::TransformConfigView(QWidget *parent)
    : QWidget(parent), ui(new Ui::TransformConfigView) {
  Setup();
}

TransformConfigView::TransformConfigView(s21::TransformSpacer *transform,
                                         QWidget *parent)
    : TransformConfigView(parent){
  SetTranformSpacer(transform);
}
void TransformConfigView::Setup() {
  ui->setupUi(this);
  connect(ui->TranslationTriplet, SIGNAL(InputsChanged(QVector3D)), this,
          SLOT(SetTranslation(QVector3D)));
  connect(ui->RotationTriplet, SIGNAL(InputsChanged(QVector3D)), this,
          SLOT(SetRotation(QVector3D)));
  connect(ui->ScaleTriplet, SIGNAL(InputsChanged(QVector3D)), this,
          SLOT(SetScale(QVector3D)));
  ui->TranslationTriplet->SetRange(-10000, 10000);
  ui->ScaleTriplet->SetRange(-10000, 10000);
  ui->ScaleTriplet->SetStep(0.1);
  ui->RotationTriplet->SetStep(5);
  ui->RotationTriplet->SetRange(-10000, 10000);
}
TransformConfigView::~TransformConfigView() {
  if (transformSpacer_) delete transformSpacer_;
  delete ui;
}

void TransformConfigView::ResetValues() {
  ui->TranslationTriplet->ResetValues();
  ui->RotationTriplet->ResetValues();
  ui->ScaleTriplet->ResetValues();
}

void TransformConfigView::SetValuesFromConfig() {
  if (!transformSpacer_) return;
  ui->TranslationTriplet->SetValues(transformSpacer_->GetTranslate());
  ui->RotationTriplet->SetValues(transformSpacer_->GetRotation());
  ui->ScaleTriplet->SetValues(transformSpacer_->GetScale());
}

void TransformConfigView::SetTranformSpacer(s21::TransformSpacer *transformSpacer) {
  transformSpacer_ = transformSpacer;
  if (!transformSpacer_) return;
  connect(transformSpacer_, &s21::TransformSpacer::ConfigUpdated, this,
          &TransformConfigView::SetValuesFromConfig);
  SetValuesFromConfig();
}

void TransformConfigView::SetTranslation(const QVector3D translate) {
  if (!transformSpacer_) return;
  transformSpacer_->SetTranslate(translate);
  emit UpdateRequest();
}

void TransformConfigView::SetRotation(const QVector3D rotation) {
  if (!transformSpacer_) return;
  transformSpacer_->SetRotation(rotation);
  emit UpdateRequest();
}

void TransformConfigView::SetScale(const QVector3D scale) {
  if (!transformSpacer_) return;
  transformSpacer_->SetScale(scale);
  emit UpdateRequest();
}
