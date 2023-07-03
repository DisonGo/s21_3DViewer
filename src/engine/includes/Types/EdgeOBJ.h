#ifndef EDGEOBJ_H
#define EDGEOBJ_H

#include "BaseOBJ.h"

namespace s21 {

class EdgeOBJ : public s21::BaseOBJ {
 public:
  vector<Face> faces_;
  OBJType type = OBJType::kEdgeOBJ;
  virtual OBJType GetType() const override { return type; };
};

}  // namespace s21

#endif  // EDGEOBJ_H