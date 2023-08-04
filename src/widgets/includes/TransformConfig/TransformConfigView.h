#ifndef TRANSFORMCONFIGVIEW_H
#define TRANSFORMCONFIGVIEW_H

#include <godison/Vectors.h>
using godison::vectors::Vector3D;
#include "ConfigWidget.h"
#include "Spacers/TransformSpacer.h"
namespace Ui {
class TransformConfigView;
}
namespace s21 {

class TransformConfigView : public ConfigWidget {
  Q_OBJECT

 public:
  explicit TransformConfigView(QWidget* parent = nullptr);
  explicit TransformConfigView(s21::TransformSpacer* transform,
                               QWidget* parent = nullptr);
  ~TransformConfigView();

 public slots:
  void ResetValues();
  void SetValuesFromConfig();
  void SetTranformSpacer(s21::TransformSpacer* transform);
  void SetTranslation(const Vector3D);
  void SetRotation(const Vector3D);
  void SetScale(const Vector3D);
 signals:
  void TransformUpdated();

 private:
  void Setup();
  s21::TransformSpacer* transform_spacer_ = nullptr;
  ::Ui::TransformConfigView* ui;
};
}  // namespace s21
#endif  // TRANSFORMCONFIGVIEW_H
