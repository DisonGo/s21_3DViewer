#ifndef TRANSFORM_H
#define TRANSFORM_H
#include <godison/Vectors.h>
using godison::vectors::Vector3D;
#include <QMatrix4x4>

#include "E/EObject.h"
#include "Shaders/Program.h"
namespace s21 {
class Transform : public EObject, protected QOpenGLFunctions {
  friend class TransformSpacer;

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

  QMatrix4x4 modelScale_;
  QMatrix4x4 modelRot_;
  QMatrix4x4 modelTranslate_;
  bool awaitingLoadInProgram_ = false;
};
}  // namespace s21

#endif  // TRANSFORM_H
