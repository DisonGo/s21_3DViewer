#include "Spacers/Object3DSpacer.h"

void s21::Object3DSpacer::SetEdgesColorValue(QColor new_color) {
  object_.SetEdgesColor(new_color);
  emit ConfigUpdated();
}

void s21::Object3DSpacer::SetEdgesThicknessValue(double new_thickness) {
  object_.SetEdgesThickness(new_thickness);
  emit ConfigUpdated();
}

void s21::Object3DSpacer::SetVerticesColorValue(QColor new_color) {
  object_.SetVerticesColor(new_color);
  emit ConfigUpdated();
}

void s21::Object3DSpacer::SetVerticesSizeValue(size_t new_size) {
  object_.SetVerticesSize(new_size);
  emit ConfigUpdated();
}

void s21::Object3DSpacer::SetDisplayMethodValue(int new_method) {
  object_.SetDisplayMethod(new_method);
  emit ConfigUpdated();
}

void s21::Object3DSpacer::SetUITypeValue(int new_type) {
  object_.SetUIType(new_type);
  emit ConfigUpdated();
}
