#ifndef TRIPLETWIDGET_H
#define TRIPLETWIDGET_H

#include <QVector3D>
#include <QWidget>
namespace Ui {
class TripletWidget;
}

class TripletWidget : public QWidget {
  Q_OBJECT

 public:
  explicit TripletWidget(QWidget *parent = nullptr);
  ~TripletWidget();
  void SetValues(const QVector3D &values);
  QVector3D GetValues() const;

 public slots:
  void ResetValues();
  void Lock();
  void Unlock();
  void SetRangeMin(double min);
  void SetRangeMax(double max);
  void SetRange(double min, double max);
 signals:
  void InputsChanged(const QVector3D values);
 private slots:
  void UpdateInputs();
  void ReadInput(double val);

 private:
  QVector3D values = QVector3D(0, 0, 0);
  Ui::TripletWidget *ui;
};

#endif  // TRIPLETWIDGET_H