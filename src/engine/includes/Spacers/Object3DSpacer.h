#ifndef OBJECT_3D_SPACER_H
#define OBJECT_3D_SPACER_H

#include <QObject>

#include "E/Object3D.h"
namespace s21 {
class Object3DSpacer : public QObject {
  Q_OBJECT
 public:
  Object3DSpacer(Object3D& object, QObject* parent = nullptr)
      : QObject(parent), object_(object){};
  DisplayMethod GetDisplayMethodValue() { return object_.GetDisplayMethod(); };
  UIType GetUITypeValue() { return object_.GetUIType(); };
  QColor GetEdgesColorValue() { return object_.GetEdgesColor(); };
  double GetEdgesThicknessValue() { return object_.GetEdgesThickness(); };
  QColor GetVerticesColorValue() { return object_.GetVerticesColor(); };
  size_t GetVerticesSizeValue() { return object_.GetVerticesSize(); };

  void SetEdgesColorValue(QColor new_color);
  void SetEdgesThicknessValue(double new_thickness);
  void SetVerticesColorValue(QColor new_color);
  void SetVerticesSizeValue(size_t new_size);
  void SetDisplayMethodValue(int new_method);
  void SetUITypeValue(int new_type);

 private:
  Object3D& object_;
};
}  // namespace s21
#endif  // OBJECT_3D_SPACER_H
