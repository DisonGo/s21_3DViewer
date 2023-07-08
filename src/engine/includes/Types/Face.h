#ifndef FACE_H
#define FACE_H
#include <vector>

#include "FaceVertex.h"
namespace s21 {
struct Face {
  std::vector<FaceVertex> indices;
};
}  // namespace s21

#endif  // FACE_H
