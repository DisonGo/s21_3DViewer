#ifndef LIGHTSPACER_H
#define LIGHTSPACER_H
#include <QObject>

#include "E/Light/Light.h"
namespace s21 {
class LightSpacer : public QObject {
  Q_OBJECT
  using Vector3D = godison::vectors::Vector3D;

 public:
  LightSpacer(Light &light, QObject *parent = nullptr);
  void SetPosition(const Vector3D &new_position);
  void SetColor(const Vector3D &new_color);
  void SetStrength(float new_strength);
  const Vector3D &GetPosition() const;
  const Vector3D &GetColor() const;
  float GetStrength() const;
 signals:
  void ConfigUpdated();

 private:
  Light &light_;
};
}  // namespace s21

#endif  // LIGHTSPACER_H
