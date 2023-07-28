#ifndef TRIPLETWIDGET_H
#define TRIPLETWIDGET_H

#include <godison/Vectors.h>
using godison::vectors::Vector3D;
#include <QWidget>
namespace Ui {
class TripletWidget;
}
namespace s21 {

class TripletWidget : public QWidget {
  Q_OBJECT

 public:
  explicit TripletWidget(QWidget *parent = nullptr);
  ~TripletWidget();
  void SetValues(const Vector3D &values);
  void SetStep(double step);
  Vector3D GetValues() const;

 public slots:
  void ResetValues();
  void Lock();
  void Unlock();
  void SetRangeMin(double min);
  void SetRangeMax(double max);
  void SetRange(double min, double max);
 signals:
  void InputsChanged(const Vector3D values);
 private slots:
  void UpdateInputs();
  void ReadInput(double val);

 private:
  Vector3D values = Vector3D(0, 0, 0);
  ::Ui::TripletWidget *ui;
};
}  // namespace s21
#endif  // TRIPLETWIDGET_H
