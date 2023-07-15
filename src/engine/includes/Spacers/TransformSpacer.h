#ifndef TRANSFORMSPACER_H
#define TRANSFORMSPACER_H
#include <godison/Vectors.h>
using godison::vectors::Vector3D;
#include <QObject>

#include "E/Transform.h"
namespace s21 {
class TransformSpacer : public QObject {
  Q_OBJECT
 public:
  TransformSpacer(Transform &transform, QObject *parent = nullptr)
      : QObject(parent), transform_(transform){};
  const Vector3D &GetScale() const;
  const Vector3D &GetRotation() const;
  const Vector3D &GetTranslate() const;
 public slots:
  void SetScale(const Vector3D &newScale);
  void SetRotation(const Vector3D &newRotation);
  void SetTranslate(const Vector3D &newTranslate);
 signals:
  void ConfigUpdated();

 private:
  Transform &transform_;
};
}  // namespace s21
#endif  // TRANSFORMSPACER_H
