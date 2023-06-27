#ifndef TRIANGLEFACE_H
#define TRIANGLEFACE_H
#include "FaceVertex.h"
typedef struct {
  FaceVertex indices[3];
} TriangleFace;

#endif // TRIANGLEFACE_H