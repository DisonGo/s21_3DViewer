#pragma once
#include <vector>

#include "FaceVertex.h"
typedef struct _Face {
  std::vector<FaceVertex> indices;
} Face;
