#ifndef SRC_INCLUDES_TYPES_FACES_OBJ_H
#define SRC_INCLUDES_TYPES_FACES_OBJ_H

#include "BaseOBJ.h"

namespace s21 {

class TriangleOBJ : public s21::BaseOBJ {
 public:
  vector<TriangleFace> faces;
  OBJType type = OBJType::kTriangleOBJ;
  virtual OBJType GetType() const override { return type; };
};

}  // namespace s21

#endif  //   SRC_INCLUDES_TYPES_FACES_OBJ_H
