#ifndef OBJECT3D_H
#define OBJECT3D_H
#include "E/Camera.h"
#include "E/EObject.h"
#include "E/Mesh.h"
#include "E/Transform.h"
#include "Shaders/Program.h"
namespace s21 {
enum class DisplayMethod { kNone = 0, kCircle, kSquare };
enum UIType { kSolid = 0, kDashed };
class Object3D : public EObject {
 public:
  Object3D() = default;
  Object3D(const Mesh& mesh) : mesh_(mesh){};
  Object3D(const Mesh& mesh, Program& program) : mesh_(mesh) {
    SetProgram(program);
  };
  Object3D(const Mesh& mesh, Program& program, const Transform& transform)
      : mesh_(mesh), transform_(transform) {
    SetProgram(program);
  };
  virtual EObjectType GetType() const override { return type_; };
  void Draw(GLenum type, Camera* camera);

  void UploadMesh(const OBJ& obj, OBJImportStrategy* importer);

  void SetMesh(const Mesh& mesh);
  void SetProgram(Program& program);
  void SetTransform(const Transform& transform);
  void SetEdgesColor(QColor new_color);
  void SetEdgesThickness(double new_thickness);
  void SetVerticesColor(QColor new_color);
  void SetVerticesSize(size_t new_size);
  void SetDisplayMethod(int new_method);
  void SetUIType(int new_type);
  Mesh& GetMesh() { return mesh_; };
  Transform& GetTrasform() { return transform_; };
  DisplayMethod GetDisplayMethod() { return display_method_; };
  UIType GetUIType() { return ui_type_; };
  QColor GetEdgesColor() { return edges_color_; };
  double GetEdgesThickness() { return edges_thickness_; };
  QColor GetVerticesColor() { return vertices_color_; };
  size_t GetVerticesSize() { return vertices_size_; };

 protected:
  EObjectType type_ = kObject3D;

 private:
  Mesh mesh_;
  Program* program_{};
  Transform transform_;
  QColor edges_color_;
  double edges_thickness_;
  QColor vertices_color_;
  size_t vertices_size_;
  DisplayMethod display_method_ = DisplayMethod::kNone;
  UIType ui_type_ = kSolid;
};

}  // namespace s21

#endif  // OBJECT3D_H
