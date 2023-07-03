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
enum OBJType { kBaseOBJ, kEdgeOBJ, kTriangleOBJ };
class BaseOBJ {
 public:
  vector<Vertex> vertices_;
  vector<Normal> normals_;
  vector<TextureCoord> texture_coords_;
  OBJType type_ = OBJType::kBaseOBJ;
  virtual OBJType GetType() const { return type_; };
  virtual ~BaseOBJ() = default;
};

}  // namespace s21
#endif  // BASEOBJ_H