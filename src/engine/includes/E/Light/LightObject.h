#ifndef LIGHTOBJECT_H
#define LIGHTOBJECT_H
#include "E/Light/Light.h"
#include "E/Object3D.h"
#include "E/Point.h"
namespace s21 {
class LightObject : public Object3D, public Light {
 public:
  LightObject() : Object3D(), Light() { Setup(); };
  LightObject(const Light& light) : Object3D(), Light(light) { Setup(); };
  virtual EObjectType GetType() const override { return type_; };
  void LoadInGLSLArray(Program& program, const std::string& array_name,
                       size_t index);
  void SetLight(const Light& light) { *this = light; }
  Light GetLight() { return *static_cast<Light*>(this); }

 protected:
  EObjectType type_ = kLightObject;
  void SyncPrograms();
  void Draw(GLenum type, Camera* camera) override;

 private:
  void Setup();
  Point light_point_{position_};
};

}  // namespace s21
#endif  // LIGTHOBJECT_H
