#include "Spacers/CameraSpacer.h"
using godison::vectors::Vector3D;
using godison::vectors::Vector2D;
namespace s21 {
CameraSpacer::CameraSpacer(Camera &camera, QObject *parent)
    : QObject(parent), camera_(camera) {}

void CameraSpacer::SetMode(Camera::CameraMode newMode) {
  camera_.SetMode(newMode);
  SetOrientation(-GetOrientation());
  emit ConfigUpdated();
}

void CameraSpacer::SetViewMode(Camera::ViewMode newViewMode) {
  camera_.SetViewMode(newViewMode);
  emit ConfigUpdated();
}

void CameraSpacer::SetFocusPoint(const Vector3D &newFocusPoint) {
  camera_.SetFocusPoint(newFocusPoint);
  emit ConfigUpdated();
}

void CameraSpacer::SetPosition(const Vector3D &newPosition) {
  camera_.SetPosition(newPosition);
  emit ConfigUpdated();
}

void CameraSpacer::SetOrientation(const Vector3D &newOrientation) {
  camera_.SetOrientation(newOrientation);
  emit ConfigUpdated();
}

void CameraSpacer::SetZRange(const Vector2D &newZRange) {
  camera_.SetZRange(newZRange);
  emit ConfigUpdated();
}

void CameraSpacer::SetFOV(float newFOV) {
  camera_.SetFOV(newFOV);
  emit ConfigUpdated();
}

void CameraSpacer::SetVw(int newVw) {
  camera_.SetVw(newVw);
  emit ConfigUpdated();
}

void CameraSpacer::SetVh(int newVh) {
  camera_.SetVh(newVh);
  emit ConfigUpdated();
}

void CameraSpacer::SetMoveSpeed(float newMoveSpeed) {
  camera_.SetMoveSpeed(newMoveSpeed);
  emit ConfigUpdated();
}

void CameraSpacer::SetRotationSpeed(float newRotationSpeed) {
  camera_.SetRotationSpeed(newRotationSpeed);
  emit ConfigUpdated();
}
void CameraSpacer::SetBox(const Camera::ParallelBox &newBox) {
  camera_.SetBox(newBox);
  emit ConfigUpdated();
}

void CameraSpacer::SetLineWidth(double newLineWidth) {
  camera_.SetLineWidth(newLineWidth);
  emit ConfigUpdated();
}
Camera::CameraMode CameraSpacer::GetMode() const { return camera_.GetMode(); }

Camera::ViewMode CameraSpacer::GetViewMode() const {
  return camera_.GetViewMode();
}

const Vector3D &CameraSpacer::GetFocusPoint() const {
  return camera_.GetFocusPoint();
}

const Vector3D &CameraSpacer::GetPosition() const {
  return camera_.GetPosition();
}

const Vector3D &CameraSpacer::GetOrientation() const {
  return camera_.GetOrientation();
}

const Vector2D &CameraSpacer::GetZRange() const { return camera_.GetZRange(); }

float CameraSpacer::GetFOV() const { return camera_.GetFOV(); }

int CameraSpacer::GetVw() const { return camera_.GetVw(); }

int CameraSpacer::GetVh() const { return camera_.GetVh(); }

float CameraSpacer::GetMoveSpeed() const { return camera_.GetMoveSpeed(); }

float CameraSpacer::GetRotationSpeed() const {
  return camera_.GetRotationSpeed();
}

const Camera::ParallelBox &CameraSpacer::GetBox() const {
  return camera_.GetBox();
}

double CameraSpacer::GetLineWidth() { return camera_.GetLineWidth(); }
}  // namespace s21
