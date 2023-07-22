#ifndef LIGHTOBJECT_H
#define LIGHTOBJECT_H
#include "E/Object3D.h"
namespace s21 {
class LightObject : public Object3D {
 public:
  LightObject() = default;
  void Draw(GLenum type, Camera* camera) override;
};
}  // namespace s21
#endif  // LIGTHOBJECT_H