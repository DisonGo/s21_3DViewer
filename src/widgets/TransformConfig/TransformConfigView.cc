#include "TransformConfig/TransformConfigView.h"

#include "ui_TransformConfigView.h"

TransformConfigView::TransformConfigView(QWidget *parent)
    : QWidget(parent), ui(new Ui::TransformConfigView) {
  ui->setupUi(this);
  connect(ui->TranslationTriplet, SIGNAL(InputsChanged(QVector3D)), this,
          SLOT(SetTranslation(QVector3D)));
  connect(ui->RotationTriplet, SIGNAL(InputsChanged(QVector3D)), this,
          SLOT(SetRotation(QVector3D)));
  connect(ui->ScaleTriplet, SIGNAL(InputsChanged(QVector3D)), this,
          SLOT(SetScale(QVector3D)));
}

TransformConfigView::~TransformConfigView() { delete ui; }

void TransformConfigView::ResetValues() {
  ui->TranslationTriplet->ResetValues();
  ui->RotationTriplet->ResetValues();
  ui->ScaleTriplet->ResetValues();
}

void TransformConfigView::SetTranformSpacer(TransformSpacer *transformSpacer) {
  transformSpacer_ = transformSpacer;
  if (!transformSpacer_) return;
  SetTranslation(transformSpacer_->GetTranslate());
  SetRotation(transformSpacer_->GetRotation());
  SetScale(transformSpacer_->GetScale());
}

void TransformConfigView::SetTranslation(const QVector3D translate) {
  if (!transformSpacer_) return;
  transformSpacer_->SetTranslate(translate);
  emit TransformUpdated();
}

void TransformConfigView::SetRotation(const QVector3D rotation) {
  if (!transformSpacer_) return;
  transformSpacer_->SetRotation(rotation);
  emit TransformUpdated();
}

void TransformConfigView::SetScale(const QVector3D scale) {
  if (!transformSpacer_) return;
  transformSpacer_->SetScale(scale);
  emit TransformUpdated();
}
