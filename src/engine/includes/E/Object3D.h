#ifndef OBJECT3D_H
#define OBJECT3D_H
#include "E/Camera.h"
#include "E/EObject.h"
#include "E/Mesh.h"
#include "E/Transform.h"
#include "Types/EdgeOBJ.h"
#include "Types/TriangleOBJ.h"
#include "Shader.h"
class Object3D : public EObject {
 public:
  Object3D(){};
  Object3D(const Mesh& mesh) : mesh_(mesh){};
  Object3D(const Mesh& mesh, Shader& shader) : mesh_(mesh) {
    SetShader(shader);
  };
  Object3D(const Mesh& mesh, Shader& shader, const Transform& transform)
      : mesh_(mesh), transform_(transform) {
    SetShader(shader);
  };
  EObjectType type = kObject3D;
  virtual EObjectType GetType() const override { return type; };
  void Draw(GLenum type, Camera* camera);

  void UploadMesh(const s21::EdgeOBJ& obj);
  void UploadMesh(const s21::TriangleOBJ& obj);

  void SetMesh(const Mesh& mesh);
  void SetShader(Shader& shader);
  void SetTransform(const Transform& transform);

 private:
  Mesh mesh_;
  Shader* shader_{};
  Transform transform_;
};

#endif  // OBJECT3D_H
