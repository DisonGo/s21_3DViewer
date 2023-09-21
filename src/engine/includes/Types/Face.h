#ifndef FACE_H
#define FACE_H
#include <vector>

#include "FaceVertex.h"
namespace s21 {
struct Face {
  std::vector<FaceVertex> indices;
  friend std::ostream& operator<<(std::ostream& os, const Face& f) {
    for (auto& index : f.indices)
      os << index << (&index == &f.indices.back() ? "" : " | ");
    return os;
  }
};
}  // namespace s21

#endif  // FACE_H
