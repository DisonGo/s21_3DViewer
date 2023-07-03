#ifndef MESH_H
#define MESH_H
#include <QMatrix4x4>
#include <QOpenGLFunctions>

#include "DrawConfig.h"
#include "E/Camera.h"
#include "E/EObject.h"
#include "E/Transform.h"
#include "GL/EBO.h"
#include "GL/VAO.h"
#include "Shaders/Program.h"
#include "Types/EdgeOBJ.h"
#include "Types/TriangleOBJ.h"
class Mesh : public EObject, protected QOpenGLFunctions {
 public:
  Mesh();
  Mesh(s21::EdgeOBJ obj);
  Mesh(s21::TriangleOBJ obj);
  ~Mesh();
  void Bind();
  void Unbind();
  void Draw(GLenum type);
  void LoadObj(const s21::EdgeOBJ& obj);
  void LoadObj(const s21::TriangleOBJ& obj);
  virtual EObjectType GetType() const override { return type_; };

 protected:
  EObjectType type_ = EObjectType::kMesh;

 private:
  int verticesN_ = 0;
  int indicesN_ = 0;
  DrawConfig* draw_config_;
  VAO vertex_only_VAO_;
  VAO mix_VAO_;
};

#endif  // MESH_H
