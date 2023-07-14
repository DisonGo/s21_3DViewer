#ifndef VECTORS_H
#define VECTORS_H
#include <godison/Types.h>

#include <array>
#include <cmath>
#include <initializer_list>
namespace godison {
namespace vectors {
template <typename type, size_t size>
class Vector {
 public:
  Vector() : data_{} {
    static_assert(std::is_default_constructible<type>::value,
                  "vector_type must be default constructible");
  };
  Vector(std::initializer_list<type> vals) : Vector() {
    size_t min_size = std::min(vals.size(), size);
    for (size_t i = 0; i < min_size; ++i) data_[i] = vals.begin()[i];
  }
  Vector(const Vector& other) { *this = other; }
  Vector(Vector&& other) { *this = std::move(other); }
  ~Vector() = default;
  Vector& operator=(const Vector& other) {
    if (this == &other) return *this;
    data_ = other.data_;
    return *this;
  }
  Vector& operator=(Vector&& other) {
    if (this == &other) return *this;
    data_ = std::move(other.data_);
    return *this;
  }
  const Vector& operator+(const Vector& other) {
    Vector tmp(*this);
    return tmp += other;
  };
  const Vector& operator+(double value) {
    Vector tmp(*this);
    return tmp += value;
  };
  const Vector& operator-(const Vector& other) {
    Vector tmp(*this);
    return tmp += other;
  };
  const Vector& operator-(double value) {
    Vector tmp(*this);
    return tmp += value;
  };
  const Vector& operator*(const Vector& other) {
    Vector tmp(*this);
    return tmp += other;
  };
  const Vector& operator*(double value) {
    Vector tmp(*this);
    return tmp += value;
  };
  const Vector& operator/(double value) {
    Vector tmp(*this);
    return tmp += value;
  };
  const Vector& operator+=(const Vector& other) {
    for (size_t i = 0; i < size; ++i) data_[i] += other.data_[i];
    return *this;
  };
  const Vector& operator+=(double value) {
    for (size_t i = 0; i < size; ++i) data_[i] += value;
    return *this;
  };
  const Vector& operator-=(const Vector& other) {
    for (size_t i = 0; i < size; ++i) data_[i] -= other.data_[i];
    return *this;
  };
  const Vector& operator-=(double value) {
    for (size_t i = 0; i < size; ++i) data_[i] -= value;
    return *this;
  };
  const Vector& operator*=(const Vector& other) {
    for (size_t i = 0; i < size; ++i) data_[i] *= other.data_[i];
    return *this;
  };
  const Vector& operator*=(double value) {
    for (size_t i = 0; i < size; ++i) data_[i] *= value;
    return *this;
  };
  const Vector& operator/=(double value) {
    for (size_t i = 0; i < size; ++i) data_[i] /= value;
    return *this;
  };
  bool operator==(const Vector& other) const {
    constexpr double EPS = 1e-6;
    for (size_t i = 0; i < size; ++i)
      if (std::abs(data_[i] - other.data_[i]) > EPS) return false;
    return true;
  }
  type& operator[](size_t index) {
    if (index >= size) throw "Out of bounds";
    return data_[index];
  };
  const type& operator[](size_t index) const {
    if (index >= size) throw "Out of bounds";
    return data_[index];
  };
  std::array<type, size>& Data() { return data_; };
  const std::array<type, size>& Data() const { return data_; }
  friend std::ostream& operator<<(std::ostream& os, const Vector& v) {
    for (const auto val : v.data_) os << val << " ";
    return os;
  }
  template <size_t S, typename T = type>
  Vector<T, S> ToVector() {
    Vector<T, S> v;
    size_t min_size = std::min(S, size);
    for (size_t i = 0; i < min_size; ++i) v[i] = data_[i];
    return v;
  }
  double Length() const {
    vector_type sum{};
    for (const auto& val : data_) sum += val * val;
    return std::sqrt(sum);
  }
  void Normalize() {
    try {
      *this /= Length();
    } catch (...) {
      *this = Vector();
    }
  }
  Vector Normalized() {
    Vector tmp(*this);
    tmp.Normalize();
    return tmp;
  }

 protected:
  using vector_type = type;
  const size_t size_ = size;
  std::array<type, size> data_;
};
class Vector2D : public Vector<double, 2> {
 public:
  Vector2D(double x = 0, double y = 0) : Vector() {
    SetX(x);
    SetY(y);
  };
  Vector2D(const Vector& other) { *this = other; };
  Vector2D& operator=(const Vector& other) {
    if (this == &other) return *this;
    data_ = other.Data();
    return *this;
  }
  inline double X() { return data_[0]; }
  inline double Y() { return data_[1]; }
  inline void SetX(double value) { data_[0] = value; }
  inline void SetY(double value) { data_[1] = value; }
};
class Vector3D : public Vector<double, 3> {
 public:
  Vector3D(double x = 0, double y = 0, double z = 0) : Vector() {
    SetX(x);
    SetY(y);
    SetZ(z);
  };
  Vector3D(const Vector& other) {
    if (this == &other) return;
    *this = other;
  }
  Vector3D& operator=(const Vector& other) {
    if (this == &other) return *this;
    data_ = other.Data();
    return *this;
  }

  inline double X() { return data_[0]; }
  inline double Y() { return data_[1]; }
  inline double Z() { return data_[2]; }
  inline void SetX(double value) { data_[0] = value; }
  inline void SetY(double value) { data_[1] = value; }
  inline void SetZ(double value) { data_[2] = value; }
};
class Vector4D : public Vector<double, 4> {
 public:
  Vector4D(double x = 0, double y = 0, double z = 0, double w = 0) : Vector() {
    SetX(x);
    SetY(y);
    SetZ(z);
    SetW(w);
  }

  Vector4D(const Vector& other) {
    if (this == &other) return;
    *this = other;
  }
  Vector4D& operator=(const Vector& other) {
    if (this == &other) return *this;
    data_ = other.Data();
    return *this;
  }

  inline double X() const { return data_[0]; }
  inline double Y() const { return data_[1]; }
  inline double Z() const { return data_[2]; }
  inline double W() const { return data_[3]; }

  inline void SetX(double value) { data_[0] = value; }
  inline void SetY(double value) { data_[1] = value; }
  inline void SetZ(double value) { data_[2] = value; }
  inline void SetW(double value) { data_[3] = value; }
};
}  // namespace vectors
}  // namespace godison
#endif  // VECTORS_H
