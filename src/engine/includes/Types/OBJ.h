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
}  // namespace s21
#endif  // BASEOBJ_H