#ifndef FACE_H
#define FACE_H
#include <vector>

#include "FaceVertex.h"
typedef struct {
  std::vector<FaceVertex> indices;
} Face;

#endif // FACE_H