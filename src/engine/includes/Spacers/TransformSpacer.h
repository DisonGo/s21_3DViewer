#ifndef TRANSFORMSPACER_H
#define TRANSFORMSPACER_H
#include <QObject>
#include <QVector3D>

#include "E/Transform.h"

class TransformSpacer : public QObject {
  Q_OBJECT
 public:
  TransformSpacer(Transform &transform, QObject *parent = nullptr)
      : QObject(parent), transform_(transform){};
  const QVector3D &GetScale() const;
  const QVector3D &GetRotation() const;
  const QVector3D &GetTranslate() const;
 public slots:
  void SetScale(const QVector3D &newScale);
  void SetRotation(const QVector3D &newRotation);
  void SetTranslate(const QVector3D &newTranslate);
 signals:
  void ConfigUpdated();

 private:
  Transform &transform_;
};
#endif  // TRANSFORMSPACER_H
