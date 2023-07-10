#ifndef OBJECT3DCONFIGVIEW_H
#define OBJECT3DCONFIGVIEW_H

#include <QWidget>
#include <TripletWidget.h>
namespace Ui {
class Object3DConfigView;
}

class Object3DConfigView : public QWidget {
  Q_OBJECT

 public:
  explicit Object3DConfigView(QWidget *parent = nullptr);
  ~Object3DConfigView();
 signals:
  void UpdateRequest();
 private:
  void Setup();
  void SetupConnects();
  void SetValuesFromConfig();
 private slots:
  void SetColor(const QVector3D& color);
  void SetLineType(bool checked);
  void SetPointType(bool checked);
  void SetLineWidth(double width);
  void SetPointSize(double size);
  Ui::Object3DConfigView *ui;
};

#endif  // OBJECT3DCONFIGVIEW_H
