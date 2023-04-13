#ifndef TRIPLETCONTROLLER_H
#define TRIPLETCONTROLLER_H

#include <QWidget>
#include <QVector3D>
namespace Ui {
class TripletController;
}

class TripletController : public QWidget
{
    Q_OBJECT

public:
    explicit TripletController(QWidget *parent = nullptr);
    ~TripletController();
    void SetValues(const QVector3D values);
    QVector3D GetValues() const;

public slots:
    void ResetValues();
signals:
    void InputsChanged(const QVector3D values);
private slots:
    void UpdateInputs();
    void ReadInput(double val);
private:
    QVector3D values = QVector3D(0,0,0);
    Ui::TripletController *ui;
};

#endif // TRIPLETCONTROLLER_H
