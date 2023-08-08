#ifndef LIGHTOBJECT_H
#define LIGHTOBJECT_H
#include "E/Light/Light.h"
#include "E/Object3D.h"
namespace s21 {
class LightObject : public Object3D, Light {
 public:
  using Object3D::Object3D;
  virtual EObjectType GetType() const override { return type_; };
  void LoadInGLSLArray(const Program& program, const std::string& array_name, size_t index);

 protected:
  EObjectType type_ = kLightObject;

  // void Draw(GLenum type, Camera* camera) override;
};




}  // namespace s21
#endif  // LIGTHOBJECT_H