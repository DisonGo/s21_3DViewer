#ifndef MESH_H
#define MESH_H
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include "VAO.h"
#include "Types/OBJ.h"
#include "Types/Transform.h"
#include "shader.h"
class Mesh : protected QOpenGLFunctions
{
public:
  Mesh();
  Mesh(OBJ obj);
  ~Mesh();
  void Draw(GLenum type);
  void LoadObj(const OBJ& obj);
  void SetTransform(const Transform new_transform);
  void SetShader(Shader* shader);
  Transform* GetTransformLink();
  void UpdateTransform();
private:
  void LoadModelMatrix();
  void LoadTransform();
private:
  Transform transform;
  Shader* shader = nullptr;
  QMatrix4x4 modelRot;
  QMatrix4x4 modelTranslate;
  QMatrix4x4 modelScale;
  int verticesN = 0;
  int indicesN = 0;
  bool awaitingLoadInShader = false;
  VAO vertexBuf;
};

#endif // MESH_H
