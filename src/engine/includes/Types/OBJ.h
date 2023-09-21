#ifndef BASEOBJ_H
#define BASEOBJ_H

#include <vector>

#include "Face.h"
#include "Normal.h"
#include "TextureCoord.h"
#include "TriangleFace.h"
#include "Vertex.h"
using std::vector;

namespace s21 {
struct OBJ {
 public:
  std::string name = "";
  vector<Vertex> vertices;
  vector<Normal> normals;
  vector<Face> faces;
  vector<TextureCoord> texture_coords;
  inline bool HasUvs() const { return !texture_coords.empty(); }
  inline bool Balanced() const {
    bool balanced_v_n = vertices.size() == normals.size();
    bool balanced_v_t = vertices.size() == texture_coords.size();
    return HasUvs() ? balanced_v_n && balanced_v_t : balanced_v_n;
  }
  void Print() {
    for (auto& vertex : vertices) std::cout << vertex << "\n";
    for (auto& t_coords : texture_coords) std::cout << t_coords << "\n";
    for (auto& normal : normals) std::cout << normal << "\n";
    for (auto& face : faces) std::cout << face << "\n";
  }
};
}  // namespace s21
#endif  // BASEOBJ_H
