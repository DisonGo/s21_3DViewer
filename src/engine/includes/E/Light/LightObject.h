#ifndef LIGHTOBJECT_H
#define LIGHTOBJECT_H
#include "E/Light/Light.h"
#include "E/Object3D.h"
#include "E/Point.h"
#include "Materials/Material.h"
namespace s21 {
class LightObject : public Object3D, public Light {
 public:
  LightObject(const Light& light, Point& light_point)
      : Object3D(), Light(light), light_point_(light_point) {
    Setup();
  };
  LightObject(Point& light_point) : LightObject(Light(), light_point){};
  virtual EObjectType GetType() const override { return type_; };
  void LoadInGLSLArray(Material& material, const std::string& array_name,
                       size_t index);
  void SetLight(const Light& light) { *static_cast<Light*>(this) = light; }
  Light GetLight() { return *static_cast<Light*>(this); }
  void Draw(GLenum type, Camera* camera) override;

 protected:
  EObjectType type_ = kLightObject;

 private:
  void Setup();
  Point& light_point_;
};

}  // namespace s21
#endif  // LIGTHOBJECT_H
