#ifndef GPOINT_H
#define GPOINT_H
#include <godison/Vectors.h>
namespace godison {
class GPoint : public vectors::Vector<float, 2> {
public:
  GPoint(vector_type x = 0, vector_type y = 0) : Vector() {
    SetX(x);
    SetY(y);
  };
  GPoint(const Vector& other) { *this = other; };
  GPoint& operator=(const Vector& other) {
    if (this == &other) return *this;
    data_ = other.Data();
    return *this;
  }
  inline vector_type X() { return data_[0]; }
  inline vector_type Y() { return data_[1]; }
  inline void SetX(vector_type value) { data_[0] = value; }
  inline void SetY(vector_type value) { data_[1] = value; }
};
}  // namespace godison
#endif  // GPOINT_H
