#ifndef MATERIAL_H
#define MATERIAL_H
#include "E/Camera.h"
#include "E/Transform.h"
#include "GL/Texture.h"
#include "Shaders/Program.h"
#include "godison/Vectors.h"
#include "map"
#include "memory.h"

namespace s21 {
enum PointDisplayType { kNoPoint = 0, kCircle, kSquare };
enum LineDisplayType { kSolid = 0, kDashed };
enum ObjectDisplayType { kWireframe = 0, kFlatShading, kSmoothShading };
class Material {
 public:
  Material() : program_(Program::Default()) {}
  Material(std::shared_ptr<Program> program) : program_(program) {}
  Material(const Material& other) { Copy(other); }
  Material(Material&& other) {
    Copy(other);
    other.program_.reset();
  }
  Material operator=(const Material& other) {
    if (this == &other) return *this;
    Copy(other);
    return *this;
  }
  Material operator=(Material&& other) {
    if (this == &other) return *this;
    Copy(other);
    other.program_.reset();
    return *this;
  }
  godison::vectors::Vector3D base_color{40, 40, 40};
  godison::vectors::Vector3D edges_color{255, 255, 255};
  godison::vectors::Vector3D vertices_color{255, 125, 125};
  double edges_thickness{1};
  double vertices_size{1};
  bool texture_on = true;
  bool lighting_on = true;
  PointDisplayType point_display_method = kNoPoint;
  LineDisplayType line_display_type = kSolid;
  ObjectDisplayType object_display_type = kSmoothShading;

  std::shared_ptr<Texture> texture;

  std::shared_ptr<Program> GetProgram() { return program_; };

  void LoadMaterial();
  void LoadCamera(Camera& camera);
  void LoadModelMatrix(Transform& transform);
  void LoadPrototypeSettings(GLenum type);
  void LoadTexture(const std::string& uniform);
  void LoadTexture(Texture& new_texture, const std::string& uniform);
  void ResetBools();
  void Activate();
  void Deactivate();

  void SetBoolUniform(bool value, const std::string& uniform);
  void SetIntUniform(int value, const std::string& uniform);
  void SetFloatUniform(float value, const std::string& uniform);

 protected:
  void Copy(const Material& other) {
    program_ = other.program_;
    base_color = other.base_color;
    edges_color = other.edges_color;
    vertices_color = other.vertices_color;
    edges_thickness = other.edges_thickness;
    vertices_size = other.vertices_size;
    texture_on = other.texture_on;
    lighting_on = other.lighting_on;
    point_display_method = other.point_display_method;
    line_display_type = other.line_display_type;
    object_display_type = other.object_display_type;
  }
  using prototype_type = GLenum;
  std::map<prototype_type, std::map<std::string, bool>> bool_uniforms_{
      {GL_POINTS, {{"u_circlePoint", true}}},
      {GL_LINES, {{"u_dashed", true}}},
      {GL_TRIANGLES,
       {{
           {"u_texture_on", true},
           {"u_do_lighting", true},
           {"u_flat_shade", true},
       }}}};
  std::shared_ptr<Program> program_;
};
}  // namespace s21
#endif  // MATERIAL_H
