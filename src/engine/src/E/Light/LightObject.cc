
#include "E/Light/LightObject.h"

namespace s21 {
void LightObject::Draw(GLenum type, Camera* camera) {
  light_point_.GetTrasform().SetTranslate(position_);
  auto c = color_.ToVector<3, int>();
  light_point_.SetVerticesColor({c[0], c[1], c[2]});
  light_point_.Draw(type, camera);
}

void LightObject::Setup() { light_point_.SetVerticesSize(20); }
void LightObject::LoadInGLSLArray(Program& program,
                                  const std::string& array_name, size_t index) {
  if (array_name.empty()) return;
  auto prefix = array_name + "[" + std::to_string(index) + "].";
  program.Uniform3f(prefix + "position", position_.X(), position_.Y(),
                    position_.Z());
  program.Uniform3f(prefix + "color", color_.X() / 256, color_.Y() / 256,
                    color_.Z() / 256);
  program.Uniform1f(prefix + "strength", strength_);
}
}  // namespace s21
