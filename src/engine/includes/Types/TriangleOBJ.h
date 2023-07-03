#ifndef TRIANGLEOBJ_H
#define TRIANGLEOBJ_H

#include "BaseOBJ.h"

namespace s21 {

class TriangleOBJ : public s21::BaseOBJ {
 public:
  vector<TriangleFace> faces_;
  OBJType type_ = OBJType::kTriangleOBJ;
  virtual OBJType GetType() const override { return type_; };
};

}  // namespace s21

#endif  // TRIANGLEOBJ_H