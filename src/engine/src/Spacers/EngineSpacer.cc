#include "Spacers/EngineSpacer.h"

namespace s21 {
void EngineSpacer::InitializeEngine() { engine_.Initialize(); }

void EngineSpacer::RequestRenderCycle() { engine_.Cycle(); }

void EngineSpacer::ImportOBJFile(std::string file_path) {
  engine_.ImportOBJFile(file_path);
  auto stats = engine_.GetObject3DStats(2);
  auto name = engine_.GetObject3DFileName(2);
  emit ObjectImported(stats.first, stats.second, name);
}
void EngineSpacer::ImportTextureFile(std::string file_path) {
  engine_.ImportTextureFile(file_path);
}

void EngineSpacer::UnloadTexture() { engine_.UnloadTexture(); }

EObjectItemModel &EngineSpacer::GetEObjectItemModel() {
  return engine_.GetEObjectItemModel();
}

Camera *EngineSpacer::GetCurrentCamera() { return engine_.GetCurrentCamera(); }

void EngineSpacer::SetCurrentCamera(Camera *camera) {
  engine_.SetCurrentCamera(camera);
}
}  // namespace s21
