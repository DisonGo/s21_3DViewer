#include "Object3DConfig/Object3DConfigView.h"

#include "ui_Object3DConfigView.h"

Object3DConfigView::Object3DConfigView(QWidget *parent)
    : QWidget(parent), ui(new Ui::Object3DConfigView) {
  Setup();
}

Object3DConfigView::~Object3DConfigView() { delete ui; }

void Object3DConfigView::Setup()
{
  ui->setupUi(this);
  ui->LineColorTriplet->SetRange(0,256);
  ui->PointColorTriplet->SetRange(0,256);

  ui->LineColorTriplet->SetStep(1);
  ui->PointColorTriplet->SetStep(1);
  SetupConnects();
}

void Object3DConfigView::SetupConnects()
{
  connect(ui->LineColorTriplet, &TripletWidget::InputsChanged, this, &Object3DConfigView::SetColor);
  connect(ui->PointColorTriplet, &TripletWidget::InputsChanged, this, &Object3DConfigView::SetColor);
  for (auto& but : ui->PointTypeG->buttons())
    connect(but, &QRadioButton::toggled, this, &Object3DConfigView::SetPointType);
  for (auto& but : ui->LineTypeG->buttons())
    connect(but, &QRadioButton::toggled, this, &Object3DConfigView::SetLineType);
  connect(ui->LineWidthSB, &QDoubleSpinBox::valueChanged, this, &Object3DConfigView::SetLineWidth);
  connect(ui->PointSizeSB, &QDoubleSpinBox::valueChanged, this, &Object3DConfigView::SetPointSize);
}

void Object3DConfigView::SetValuesFromConfig()
{

}

void Object3DConfigView::SetColor(const QVector3D &color)
{

}

void Object3DConfigView::SetLineType(bool checked)
{

}

void Object3DConfigView::SetPointType(bool checked)
{

}

void Object3DConfigView::SetLineWidth(double width)
{

}

void Object3DConfigView::SetPointSize(double size)
{

}
