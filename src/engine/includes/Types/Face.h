#ifndef FACE_H
#define FACE_H
#include <vector>

#include "FaceVertex.h"
struct Face {
  std::vector<FaceVertex> indices_;
};

#endif  // FACE_H
