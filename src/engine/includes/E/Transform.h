#ifndef TRANSFORM_H
#define TRANSFORM_H
#include <QMatrix4x4>
#include <QVector3D>

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

  const QVector3D &GetScale() const;
  const QVector3D &GetRotation() const;
  const QVector3D &GetTranslate() const;

  void SetScale(const QVector3D &newScale);
  void SetRotation(const QVector3D &newRotation);
  void SetTranslate(const QVector3D &newTranslate);

 protected:
  EObjectType type_ = EObjectType::kTransform;

 private:
  void UpdateScale();
  void UpdateRotation();
  void UpdateTranslate();
  QVector3D scale_ = QVector3D(1, 1, 1);
  QVector3D rotation_ = QVector3D(0, 0, 0);
  QVector3D translate_ = QVector3D(0, 0, 0);

  QMatrix4x4 modelScale_;
  QMatrix4x4 modelRot_;
  QMatrix4x4 modelTranslate_;
  bool awaitingLoadInProgram_ = false;
};
}  // namespace s21

#endif  // TRANSFORM_H
