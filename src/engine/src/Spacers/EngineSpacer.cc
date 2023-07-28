#include "Spacers/EngineSpacer.h"

namespace s21 {
void EngineSpacer::InitializeEngine() { engine_.Initialize(); }

void EngineSpacer::RequestRenderCycle() { engine_.Cycle(); }

void EngineSpacer::ImportOBJFile(std::string file_path) {
  engine_.ImportOBJFile(file_path);
}

EObjectItemModel &EngineSpacer::GetEObjectItemModel() {
  return engine_.GetEObjectItemModel();
}

Camera *EngineSpacer::GetCurrentCamera() { return engine_.GetCurrentCamera(); }

void EngineSpacer::SetCurrentCamera(Camera *camera) {
  engine_.SetCurrentCamera(camera);
}

void EngineSpacer::GetObjectStats() {}
}  // namespace s21
