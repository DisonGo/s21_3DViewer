#ifndef LIGHT_H
#define LIGHT_H
#include "E/EObject.h"
#include "godison/Vectors.h"
namespace s21 {
class Light : public EObject {
 public:
  virtual EObjectType GetType() const override { return type_; }
  const godison::vectors::Vector3D& GetColor() const { return color_; }
  const godison::vectors::Vector3D& GetPosition() const { return position_; }
  float GetStrength() const { return strength_; }

  void SetColor(const godison::vectors::Vector3D& color) { color_ = color; }
  void SetPosition(const godison::vectors::Vector3D& position) {
    position_ = position;
  }
  void SetStrength(float strength) { strength_ = strength; }

 protected:
  godison::vectors::Vector3D position_{255, 255, 255};
  godison::vectors::Vector3D color_{255, 255, 255};
  float strength_{1};
  EObjectType type_ = kLight;
};
}  // namespace s21
#endif  // LIGHT_H