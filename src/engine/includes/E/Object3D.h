#ifndef OBJECT3D_H
#define OBJECT3D_H

#define GL_SILENCE_DEPRECATION
#include <godison/Point.h>

#include <QColor>
#include <memory>

#include "E/Camera.h"
#include "E/EObject.h"
#include "E/Mesh.h"
#include "E/Transform.h"
#include "Shaders/Program.h"
namespace s21 {
enum class PointDisplayType { kNone = 0, kCircle, kSquare };
enum LineDisplayType { kSolid = 0, kDashed };
class Object3D : public EObject {
 public:
  Object3D() = default;
  Object3D(const Object3D& other) {
    *this = other;
  }
  Object3D(Object3D&& other) {
    *this = other;
  }
  ~Object3D() {
    if (delete_program_ && program_) delete program_;
  }
  Object3D& operator=(const Object3D& other);
  Object3D& operator=(Object3D&& other);
  virtual EObjectType GetType() const override { return type_; };
  virtual void Draw(GLenum type, Camera* camera);
  void UploadMesh(const OBJ& obj, OBJImportStrategy* importer);
  void SetMesh(const Mesh& mesh);
  void SetProgram(Program& program);
  void SetTransform(const Transform& transform);
  void SetEdgesColor(QColor new_color);
  void SetEdgesThickness(double new_thickness);
  void SetVerticesColor(QColor new_color);
  void SetVerticesSize(double new_size);
  void SetDisplayMethod(PointDisplayType new_method);
  void SetLineDisplayType(LineDisplayType new_type);
  void SetFileName(std::string file_name);
  Mesh& GetMesh(size_t index) { return *meshes_.at(index); };
  const std::vector<std::shared_ptr<Mesh>>& GetMeshes() { return meshes_; };
  Transform& GetTrasform() { return transform_; };
  PointDisplayType GetPointDisplayMethod() { return point_display_method_; };
  LineDisplayType GetLineDisplayType() { return line_display_type_; };
  QColor GetEdgesColor() { return edges_color_; };
  double GetEdgesThickness() { return edges_thickness_; };
  QColor GetVerticesColor() { return vertices_color_; };
  double GetVerticesSize() { return vertices_size_; };
  std::string GetFileName() { return file_name_; };
  unsigned long CountVertices(OBJImportStrategyType buffer_type);
  unsigned long CountIndices(OBJImportStrategyType buffer_type);

 protected:
  bool delete_program_ = false;
  std::string file_name_ = "";
  EObjectType type_ = kObject3D;
  std::vector<std::shared_ptr<Mesh>> meshes_;
  Program* program_{};
  Transform transform_;
  QColor edges_color_{255, 255, 255};
  double edges_thickness_{1};
  QColor vertices_color_{255, 125, 125};
  double vertices_size_{1};
  PointDisplayType point_display_method_ = PointDisplayType::kNone;
  LineDisplayType line_display_type_ = kSolid;
};

}  // namespace s21

#endif  // OBJECT3D_H
