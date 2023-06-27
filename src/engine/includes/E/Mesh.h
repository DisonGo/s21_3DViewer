#ifndef MESH_H
#define MESH_H
#include <QMatrix4x4>
#include <QOpenGLFunctions>

#include "E/Camera.h"
#include "E/EObject.h"
#include "E/Transform.h"
#include "GL/VAO.h"
#include "Shader.h"
#include "Types/EdgeOBJ.h"
#include "Types/TriangleOBJ.h"
class Mesh : public EObject, protected QOpenGLFunctions {
 public:
  Mesh();
  Mesh(s21::EdgeOBJ obj);
  Mesh(s21::TriangleOBJ obj);
  ~Mesh();
  EObjectType type = EObjectType::kMesh;
  void Bind();
  void Unbind();
  void Draw(GLenum type);
  void LoadObj(const s21::EdgeOBJ& obj);
  void LoadObj(const s21::TriangleOBJ& obj);
  virtual EObjectType GetType() const override { return type; };

 private:
  int verticesN = 0;
  int indicesN = 0;

  VAO vertexBuf;
};

#endif  // MESH_H
