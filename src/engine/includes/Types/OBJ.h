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
  vector<Vertex> vertices;
  vector<Normal> normals;
  vector<Face> faces;
  vector<TextureCoord> texture_coords;
};
enum OBJType { kBaseOBJ, kEdgeOBJ, kTriangleOBJ };
class BaseOBJ {
 public:
  vector<Vertex> vertices;
  vector<Normal> normals;
  vector<TextureCoord> texture_coords;
  OBJType type = OBJType::kBaseOBJ;
  virtual OBJType GetType() const { return type; };
  virtual ~BaseOBJ() = default;
};
}  // namespace s21
#endif  // BASEOBJ_H