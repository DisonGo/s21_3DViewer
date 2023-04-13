#include "tripletcontroller.h"
#include "ui_tripletcontroller.h"

TripletController::TripletController(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TripletController)
{
    ui->setupUi(this);
    connect(ui->firstV, SIGNAL(valueChanged(double)), this, SLOT(ReadInput(double)));
    connect(ui->secondV, SIGNAL(valueChanged(double)), this, SLOT(ReadInput(double)));
    connect(ui->thirdV, SIGNAL(valueChanged(double)), this, SLOT(ReadInput(double)));
}

TripletController::~TripletController()
{
    delete ui;
}

void TripletController::SetValues(const QVector3D values)
{
    this->values = values;
    UpdateInputs();
}

QVector3D TripletController::GetValues() const
{
    return values;
}

void TripletController::ResetValues()
{
    values.setX(0);
    values.setY(0);
    values.setZ(0);
    UpdateInputs();
}

void TripletController::UpdateInputs()
{
    ui->firstV->setValue(values.x());
    ui->secondV->setValue(values.y());
    ui->thirdV->setValue(values.z());
    emit InputsChanged(values);
}

void TripletController::ReadInput(double val)
{
    QDoubleSpinBox* wid = (QDoubleSpinBox*) sender();
    if (!wid) return;
    if (wid == ui->firstV) values.setX(val);
    if (wid == ui->secondV) values.setY(val);
    if (wid == ui->thirdV) values.setZ(val);
    emit InputsChanged(values);
}
