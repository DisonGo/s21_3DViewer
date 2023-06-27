#ifndef TRANSFORM_H
#define TRANSFORM_H
#include <QMatrix4x4>
#include <QVector3D>

#include "E/EObject.h"
#include "Shader.h"
class Transform : public EObject {
 public:
  Transform(){UpdateModel();};

  QVector3D translate = QVector3D(0, 0, 0);
  QVector3D rotation = QVector3D(0, 0, 0);
  QVector3D scale = QVector3D(1, 1, 1);

  QMatrix4x4 modelTranslate;
  QMatrix4x4 modelRot;
  QMatrix4x4 modelScale;

  void UpdateModel();
  void LoadModelMatrix(Shader* shader);

  EObjectType type = EObjectType::kTransform;
  virtual EObjectType GetType() const override { return type; };
  bool operator==(const Transform& a) const;

 private:
  bool awaitingLoadInShader_ = false;
};


#endif  // TRANSFORM_H
