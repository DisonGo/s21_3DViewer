#ifndef OBJECT3D_H
#define OBJECT3D_H

#include <godison/Point.h>

#include <memory>

#include "E/Camera.h"
#include "E/EObject.h"
#include "E/Mesh.h"
#include "E/Transform.h"
#include "Logger.h"
#include "Materials/Material.h"
#include "Shaders/Program.h"

namespace s21 {
class Object3D : public EObject {
 public:
  Object3D() = default;
  Object3D(const Object3D& other) { *this = other; }
  Object3D(Object3D&& other) { *this = other; }
  ~Object3D() = default;
  Object3D& operator=(const Object3D& other);
  Object3D& operator=(Object3D&& other);
  virtual EObjectType GetType() const override { return type_; }
  virtual void Draw(GLenum type, Camera* camera);
  void UploadMesh(const OBJ& obj, OBJImportStrategy* importer);
  void SetTransform(const Transform& transform);
  void SetMaterial(const Material& material) { material_ = material; }
  Mesh& GetMesh(size_t index) { return *meshes_.at(index); }
  const std::vector<std::shared_ptr<Mesh>>& GetMeshes() { return meshes_; }
  Transform& GetTrasform() { return transform_; }
  std::string GetFileName() { return file_name_; }
  Material& GetMaterial() { return material_; }
  unsigned long CountVertices(OBJImportStrategyType buffer_type);
  unsigned long CountIndices(OBJImportStrategyType buffer_type);

  void SetObjectDisplayType(ObjectDisplayType new_type);
  void SetFileName(std::string file_name);
protected:
  std::string file_name_ = "";
  EObjectType type_ = kObject3D;
  std::vector<std::shared_ptr<Mesh>> meshes_;
  Logger logger_{"Object3D"};
  Transform transform_;
  Material material_;
};

}  // namespace s21

#endif  // OBJECT3D_H
