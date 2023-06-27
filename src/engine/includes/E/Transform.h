#ifndef TRANSFORM_H
#define TRANSFORM_H
#include <QVector3D>

#include "E/EObject.h"
class Transform : public EObject {
public:
  QVector3D translate = QVector3D(0, 0, 0);
  QVector3D rotation = QVector3D(0, 0, 0);
  QVector3D scale = QVector3D(1, 1, 1);
  EObjectType type = EObjectType::kTransform;
  bool operator==(const Transform& a) const;
};



#endif  // TRANSFORM_H
