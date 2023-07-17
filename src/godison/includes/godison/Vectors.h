#ifndef VECTORS_H
#define VECTORS_H
#include <godison/Types.h>

#include <array>
#include <cmath>
#include <initializer_list>
namespace godison {
namespace vectors {
// TODO Add Type cast Normalized functions for VectorXD
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
  Vector operator+(const Vector& other) const {
    Vector tmp(*this);
    return tmp += other;
  };
  Vector operator+(type value) const {
    Vector tmp(*this);
    return tmp += value;
  };
  Vector operator+() const { return *this; }
  Vector operator-(const Vector& other) const {
    Vector tmp(*this);
    return tmp -= other;
  };
  Vector operator-(type value) const {
    Vector tmp(*this);
    return tmp -= value;
  };
  Vector operator-() const {
    Vector tmp(*this);
    for (auto& val : tmp.data_) val *= -1;
    return tmp;
  }
  Vector operator*(const Vector& other) const {
    Vector tmp(*this);
    return tmp *= other;
  };
  Vector operator*(type value) const {
    Vector tmp(*this);
    return tmp *= value;
  };
  friend Vector operator*(type value, const Vector& vector) {
    return vector * value;
  }
  Vector operator/(type value) const {
    Vector tmp(*this);
    return tmp /= value;
  };
  const Vector& operator+=(const Vector& other) {
    for (size_t i = 0; i < size; ++i) data_[i] += other.data_[i];
    return *this;
  };
  const Vector& operator+=(type value) {
    for (size_t i = 0; i < size; ++i) data_[i] += value;
    return *this;
  };
  const Vector& operator-=(const Vector& other) {
    for (size_t i = 0; i < size; ++i) data_[i] -= other.data_[i];
    return *this;
  };
  const Vector& operator-=(type value) {
    for (size_t i = 0; i < size; ++i) data_[i] -= value;
    return *this;
  };
  const Vector& operator*=(const Vector& other) {
    for (size_t i = 0; i < size; ++i) data_[i] *= other.data_[i];
    return *this;
  };
  const Vector& operator*=(type value) {
    for (size_t i = 0; i < size; ++i) data_[i] *= value;
    return *this;
  };
  const Vector& operator/=(type value) {
    for (size_t i = 0; i < size; ++i) data_[i] /= value;
    return *this;
  };
  bool operator==(const Vector& other) const {
    constexpr double EPS = 1e-6;
    for (size_t i = 0; i < size; ++i)
      if (std::abs(data_[i] - other.data_[i]) > EPS) return false;
    return true;
  }
  bool operator!=(const Vector& other) const { return !(*this == other); }
  type& operator[](size_t index) {
    // assert(index < size);
    if (index >= size) throw "Out of bounds";
    return data_[index];
  };
  const type& operator[](size_t index) const {
    // assert(index < size);
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
  Vector<T, S> ToVector(T fill_value = 0) const {
    Vector<T, S> v;
    size_t min_size = std::min(S, size);
    v.Data().fill(fill_value);
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
  Vector Normalized() const {
    Vector tmp(*this);
    tmp.Normalize();
    return tmp;
  }
  type Dot(const Vector& v1) const { return Dot(*this, v1); }
  static type Dot(const Vector& v1, const Vector& v2) {
    vector_type result{};
    for (size_t i = 0; i < size; ++i) result += v1[i] * v2[i];
    return result;
  }
  void Negate() {
    for (auto& val : data_)
      if (val < 0) val *= -1;
  }

 protected:
  using vector_type = type;
  const size_t size_ = size;
  std::array<type, size> data_;
};
class Vector2D : public Vector<float, 2> {
 public:
  Vector2D(vector_type x = 0, vector_type y = 0) : Vector() {
    SetX(x);
    SetY(y);
  };
  Vector2D(const Vector& other) { *this = other; };
  Vector2D& operator=(const Vector& other) {
    if (this == &other) return *this;
    data_ = other.Data();
    return *this;
  }
  vector_type CrossProduct(const Vector2D& v1) const {
    return CrossProduct(*this, v1);
  };
  static vector_type CrossProduct(const Vector2D& v1, const Vector2D& v2) {
    return v1[0] * v2[1] - v1[1] * v2[0];
  };
  inline vector_type X() const { return data_[0]; }
  inline vector_type Y() const { return data_[1]; }
  inline void SetX(vector_type value) { data_[0] = value; }
  inline void SetY(vector_type value) { data_[1] = value; }
};
class Vector3D : public Vector<float, 3> {
 public:
  Vector3D(vector_type x = 0, vector_type y = 0, vector_type z = 0) : Vector() {
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
  Vector3D CrossProduct(const Vector3D& v1) const {
    return CrossProduct(*this, v1);
  };
  static Vector3D CrossProduct(const Vector3D& v1, const Vector3D& v2) {
    Vector3D result;
    result[0] = v1[1] * v2[2] - v1[2] * v2[1];
    result[1] = v1[2] * v2[0] - v1[0] * v2[2];
    result[2] = v1[0] * v2[1] - v1[1] * v2[0];
    return result;
  };
  // Unit normal vector
  Vector3D Normal(const Vector3D& v1) const { return Normal(*this, v1); };
  static Vector3D Normal(const Vector3D& v1, const Vector3D& v2) {
    return CrossProduct(v1, v2).Normalized();
  };

  inline vector_type X() const { return data_[0]; }
  inline vector_type Y() const { return data_[1]; }
  inline vector_type Z() const { return data_[2]; }
  inline void SetX(vector_type value) { data_[0] = value; }
  inline void SetY(vector_type value) { data_[1] = value; }
  inline void SetZ(vector_type value) { data_[2] = value; }
};
class Vector4D : public Vector<float, 4> {
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
