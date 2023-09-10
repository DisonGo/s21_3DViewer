#include "Spacers/LightSpacer.h"
namespace s21 {

LightSpacer::LightSpacer(Light &light, QObject *parent)
    : QObject(parent), light_(light) {}

void LightSpacer::SetPosition(const Vector3D &new_position) {
  light_.SetPosition(new_position);
  emit ConfigUpdated();
}

void LightSpacer::SetColor(const Vector3D &new_color) {
  light_.SetColor(new_color);
  emit ConfigUpdated();
}

void LightSpacer::SetStrength(float new_strength) {
  light_.SetStrength(new_strength);
  emit ConfigUpdated();
}

const LightSpacer::Vector3D &LightSpacer::GetPosition() const {
  return light_.GetPosition();
}

const LightSpacer::Vector3D &LightSpacer::GetColor() const {
  return light_.GetColor();
}

float LightSpacer::GetStrength() const { return light_.GetStrength(); }

}  // namespace s21
