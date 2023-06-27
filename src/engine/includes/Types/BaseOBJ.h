#ifndef SRC_INCLUDES_TYPES_BASE_OBJ_H
#define SRC_INCLUDES_TYPES_BASE_OBJ_H

#include <vector>

#include "Face.h"
#include "Normal.h"
#include "TextureCoord.h"
#include "TriangleFace.h"
#include "Vertex.h"
using std::vector;

namespace s21 {

class BaseOBJ {
 public:
  vector<Vertex> vertices;
  vector<Normal> normals;
  vector<TextureCoord> textureCoords;
};

}  // namespace s21

#endif  //   SRC_INCLUDES_TYPES_BASE_OBJ_H