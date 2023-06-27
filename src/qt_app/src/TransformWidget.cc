#include "TransformWidget.h"

#include "ui_transformwidget.h"

TransformWidget::TransformWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::TransformWidget) {
  ui->setupUi(this);
  connect(ui->TranslationTriplet, SIGNAL(InputsChanged(QVector3D)), this,
          SLOT(SetTranslation(QVector3D)));
  connect(ui->RotationTriplet, SIGNAL(InputsChanged(QVector3D)), this,
          SLOT(SetRotation(QVector3D)));
  connect(ui->ScaleTriplet, SIGNAL(InputsChanged(QVector3D)), this,
          SLOT(SetScale(QVector3D)));
}

TransformWidget::~TransformWidget() { delete ui; }

void TransformWidget::LinkTranform(Transform *transform) {
  if (!transform) return;
  this->transform = transform;
  ui->TranslationTriplet->SetValues(this->transform->translate);
  ui->RotationTriplet->SetValues(this->transform->rotation);
  ui->ScaleTriplet->SetValues(this->transform->scale);
}

void TransformWidget::LinkMesh(Mesh *mesh) {
  if (!mesh) return;
  this->mesh = mesh;
//  LinkTranform(this->mesh->GetTransformLink());
}

void TransformWidget::ResetValues() {
  ui->TranslationTriplet->ResetValues();
  ui->RotationTriplet->ResetValues();
  ui->ScaleTriplet->ResetValues();
}

void TransformWidget::SetTranslation(const QVector3D translate) {
  if (!transform) return;
  transform->translate = translate;
//  mesh->UpdateTransform();
  emit TransformUpdated();
}

void TransformWidget::SetRotation(const QVector3D rotation) {
  if (!transform) return;
  transform->rotation = rotation;
//  mesh->UpdateTransform();
  emit TransformUpdated();
}

void TransformWidget::SetScale(const QVector3D scale) {
  if (!transform) return;
  transform->scale = scale;
//  mesh->UpdateTransform();
  emit TransformUpdated();
}
