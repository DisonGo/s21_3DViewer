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
  PointDisplayType GetDisplayMethodValue() {
    return object_.GetPointDisplayMethod();
  };
  LineDisplayType GetUITypeValue() { return object_.GetLineDisplayType(); };
  ObjectDisplayType GetDisplayTypeValue() {
    return object_.GetObjectDisplayType();
  };
  godison::vectors::Vector3D GetBaseColorValue() {
    return object_.GetBaseColor();
  };
  godison::vectors::Vector3D GetEdgesColorValue() {
    return object_.GetEdgesColor();
  };
  double GetEdgesThicknessValue() { return object_.GetEdgesThickness(); };
  godison::vectors::Vector3D GetVerticesColorValue() {
    return object_.GetVerticesColor();
  };
  double GetVerticesSizeValue() { return object_.GetVerticesSize(); };
  bool GetTextureToggle() { return object_.GetTextureToggle(); };
  bool GetLightingToggle() { return object_.GetLightingToggle(); };

  void SetBaseColorValue(godison::vectors::Vector3D new_color);
  void SetEdgesColorValue(godison::vectors::Vector3D new_color);
  void SetEdgesThicknessValue(double new_thickness);
  void SetVerticesColorValue(godison::vectors::Vector3D new_color);
  void SetVerticesSizeValue(double new_size);
  void SetDisplayMethodValue(PointDisplayType new_method);
  void SetUITypeValue(LineDisplayType new_type);
  void SetDisplayTypeValue(ObjectDisplayType new_type);
  void SetTextureToggle(bool on);
  void SetLightingToggle(bool on);
 signals:
  void ConfigUpdated();

 private:
  Object3D& object_;
};
}  // namespace s21
#endif  // OBJECT_3D_SPACER_H
