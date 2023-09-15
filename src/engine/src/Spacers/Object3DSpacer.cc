#include "Spacers/Object3DSpacer.h"

void s21::Object3DSpacer::SetEdgesColorValue(QColor new_color) {
  if (object_.GetEdgesColor() == new_color) return;
  object_.SetEdgesColor(new_color);
  emit ConfigUpdated();
}

void s21::Object3DSpacer::SetBaseColorValue(QColor new_color) {
  if (object_.GetBaseColor() == new_color) return;
  object_.SetBaseColor(new_color);
  emit ConfigUpdated();
}

void s21::Object3DSpacer::SetEdgesThicknessValue(double new_thickness) {
  if (object_.GetEdgesThickness() == new_thickness) return;
  object_.SetEdgesThickness(new_thickness);
  emit ConfigUpdated();
}

void s21::Object3DSpacer::SetVerticesColorValue(QColor new_color) {
  if (object_.GetVerticesColor() == new_color) return;
  object_.SetVerticesColor(new_color);
  emit ConfigUpdated();
}

void s21::Object3DSpacer::SetVerticesSizeValue(double new_size) {
  if (object_.GetVerticesSize() == new_size) return;
  object_.SetVerticesSize(new_size);
  emit ConfigUpdated();
}

void s21::Object3DSpacer::SetDisplayMethodValue(PointDisplayType new_method) {
  if (object_.GetPointDisplayMethod() == new_method) return;
  object_.SetDisplayMethod(new_method);
  emit ConfigUpdated();
}

void s21::Object3DSpacer::SetUITypeValue(LineDisplayType new_type) {
  if (object_.GetLineDisplayType() == new_type) return;
  object_.SetLineDisplayType(new_type);
  emit ConfigUpdated();
}

void s21::Object3DSpacer::SetDisplayTypeValue(ObjectDisplayType new_type)
{
    if (object_.GetObjectDisplayType() == new_type) return;
    object_.SetObjectDisplayType(new_type);
    emit ConfigUpdated();
}
