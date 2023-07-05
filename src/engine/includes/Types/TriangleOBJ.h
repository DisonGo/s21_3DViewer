#ifndef TRIANGLEOBJ_H
#define TRIANGLEOBJ_H

#include "Types/OBJ.h"

namespace s21 {

class TriangleOBJ : public s21::BaseOBJ {
 public:
  vector<TriangleFace> faces;
  OBJType type = OBJType::kTriangleOBJ;
  virtual OBJType GetType() const override { return type; };
};

}  // namespace s21

#endif  // TRIANGLEOBJ_H
