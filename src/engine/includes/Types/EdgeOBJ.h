#ifndef SRC_INCLUDES_TYPES_EDGE_OBJ_H
#define SRC_INCLUDES_TYPES_EDGE_OBJ_H

#include "BaseOBJ.h"

namespace s21 {

class EdgeOBJ : public s21::BaseOBJ {
 public:
  vector<Face> faces;
};

}  // namespace s21

#endif  //   SRC_INCLUDES_TYPES_EDGE_OBJ_H
