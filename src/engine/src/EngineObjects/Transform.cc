#include "E/Transform.h"
bool Transform::operator==(const Transform& a) const {
  return (translate == a.translate && rotation == a.rotation &&
          scale == a.scale);
}