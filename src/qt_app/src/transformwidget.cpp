#include "transformwidget.h"
#include "ui_transformwidget.h"

TransformWidget::TransformWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TransformWidget)
{
    ui->setupUi(this);
    connect(ui->TranslationTriplet, SIGNAL(InputsChanged(const QVector3D)), this, SIGNAL(TranslationChanged(const QVector3D)));
}

TransformWidget::~TransformWidget()
{
    delete ui;
}

void TransformWidget::ResetValues()
{
    ui->TranslationTriplet->ResetValues();
    ui->RotationTriplet->ResetValues();
    ui->ScaleTriplet->ResetValues();
}
