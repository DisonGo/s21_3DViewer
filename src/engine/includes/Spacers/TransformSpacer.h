#ifndef TRANSFORMSPACER_H
#define TRANSFORMSPACER_H
#include <QVector3D>

#include "E/Transform.h"

class TransformSpacer {
public:
  TransformSpacer(Transform &transform) : transform_(transform){};
  const QVector3D &GetScale() const;
  const QVector3D &GetRotation() const;
  const QVector3D &GetTranslate() const;

  void SetScale(const QVector3D &newScale);
  void SetRotation(const QVector3D &newRotation);
  void SetTranslate(const QVector3D &newTranslate);

 private:
  Transform &transform_;
};
#endif  // TRANSFORMSPACER_H
