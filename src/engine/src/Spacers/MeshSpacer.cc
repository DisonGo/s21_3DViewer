#include "Spacers/MeshSpacer.h"
namespace s21 {
bool MeshSpacer::GetBufferToogleValue(OBJImportStrategyType type) {
  return mesh_.GetBufferToggle(type);
};
void MeshSpacer::SetBufferToogleValue(OBJImportStrategyType type, bool value) {
  mesh_.SetBufferToggle(type, value);
};
}  // namespace s21