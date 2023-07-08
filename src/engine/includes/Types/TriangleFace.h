#ifndef TRIANGLEFACE_H
#define TRIANGLEFACE_H
#include "FaceVertex.h"
namespace s21 {
struct TriangleFace {
  FaceVertex indices[3];
};
}  // namespace s21

#endif  // TRIANGLEFACE_H
