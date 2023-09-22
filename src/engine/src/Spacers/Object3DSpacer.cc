#include "Spacers/Object3DSpacer.h"
namespace s21 {
void Object3DSpacer::SetObjectDisplayType(ObjectDisplayType new_type) {
  if (object_.GetMaterial().object_display_type == new_type) return;
  object_.SetObjectDisplayType(new_type);
  emit ConfigUpdated();
}
}  // namespace s21
