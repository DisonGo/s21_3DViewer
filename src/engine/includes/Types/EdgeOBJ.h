#ifndef EDGEOBJ_H
#define EDGEOBJ_H

#include "Types/OBJ.h"

namespace s21 {

class EdgeOBJ : public s21::BaseOBJ {
 public:
  vector<Face> faces;
  OBJType type = OBJType::kEdgeOBJ;
  virtual OBJType GetType() const override { return type; };
};

}  // namespace s21

#endif  // EDGEOBJ_H
