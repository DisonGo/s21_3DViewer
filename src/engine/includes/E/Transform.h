#ifndef TRANSFORM_H
#define TRANSFORM_H
#include <godison/Matrices.h>

#include "E/EObject.h"
#include "Shaders/Program.h"
namespace s21 {
class Transform : public EObject, protected QOpenGLFunctions {
  friend class TransformSpacer;
  using Vector3D = godison::vectors::Vector3D;

 public:
  Transform() {
    initializeOpenGLFunctions();
    UpdateModel();
  };

  void UpdateModel();
  void LoadModelMatrix(Program *program);

  virtual EObjectType GetType() const override { return type_; };
  bool operator==(const Transform &a) const;

  const Vector3D &GetScale() const;
  const Vector3D &GetRotation() const;
  const Vector3D &GetTranslate() const;

  void SetScale(const Vector3D &newScale);
  void SetRotation(const Vector3D &newRotation);
  void SetTranslate(const Vector3D &newTranslate);

 protected:
  EObjectType type_ = EObjectType::kTransform;

 private:
  void UpdateScale();
  void UpdateRotation();
  void UpdateTranslate();
  Vector3D scale_ = Vector3D(1, 1, 1);
  Vector3D rotation_ = Vector3D(0, 0, 0);
  Vector3D translate_ = Vector3D(0, 0, 0);

  godison::matrices::Matrix4x4 model_scale_;
  godison::matrices::Matrix4x4 model_rot_;
  godison::matrices::Matrix4x4 model_translate_;
  bool awaitingLoadInProgram_ = false;
};
}  // namespace s21

#endif  // TRANSFORM_H
