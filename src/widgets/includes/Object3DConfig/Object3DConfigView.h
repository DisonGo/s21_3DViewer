#ifndef OBJECT3DCONFIGVIEW_H
#define OBJECT3DCONFIGVIEW_H

#include <TripletWidget.h>

#include "ConfigWidget.h"
#include "Spacers/Object3DSpacer.h"
namespace Ui {
class Object3DConfigView;
}
namespace s21 {

class Object3DConfigView : public ConfigWidget {
  Q_OBJECT

 public:
  explicit Object3DConfigView(QWidget* parent = nullptr);
  explicit Object3DConfigView(s21::Object3DSpacer* object_spacer,
                              QWidget* parent = nullptr);
  ~Object3DConfigView();

 private:
  ::Ui::Object3DConfigView* ui;
  s21::Object3DSpacer* object_spacer_ = nullptr;
  void Setup();
  void SetupSpacer(s21::Object3DSpacer* object_spacer);
  void SetupConnects();
 private slots:
  void SetValuesFromConfig();
  void SetColor(const Vector3D& color);
  void SetLineType(bool checked);
  void SetPointType(bool checked);
  void SetLineWidth(double width);
  void SetPointSize(double size);
};
}
#endif  // OBJECT3DCONFIGVIEW_H
