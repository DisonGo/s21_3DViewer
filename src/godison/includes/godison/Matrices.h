#ifndef MATRICES_H
#define MATRICES_H
#include <godison/Vectors.h>
namespace godison {
namespace matrices {
using vectors::Vector;
template <size_t w, size_t h, typename values_type = float>
class Matrix {
 public:
  using MatData = Vector<values_type, w * h>;
  Matrix(){

  };
  Matrix(std::initializer_list<values_type> vals) : Matrix() {
    size_t min_size = std::min(vals.size(), w * h);
    for (size_t i = 0; i < min_size; ++i) this[i] = vals.begin()[i];
  }
  Matrix(const Matrix& other) { *this = other; }
  Matrix(Matrix&& other) { *this = std::move(other); }
  ~Matrix() = default;
  Matrix& operator=(const Matrix& other) {
    if (this == &other) return *this;
    data_ = other.data_;
    return *this;
  }
  Matrix& operator=(Matrix&& other) {
    if (this == &other) return *this;
    data_ = std::move(other.data_);
    return *this;
  }
  const Matrix& operator+(const Matrix& other) const {
    Matrix tmp(*this);
    return tmp += other;
  };
  const Matrix& operator+(values_type value) const {
    Matrix tmp(*this);
    return tmp += value;
  };
  const Matrix& operator+() const { return *this; }
  const Matrix& operator-(const Matrix& other) const {
    Matrix tmp(*this);
    return tmp -= other;
  };
  const Matrix& operator-(values_type value) const {
    Matrix tmp(*this);
    return tmp -= value;
  };
  const Matrix& operator-() const {
    Matrix tmp(*this);
    for (auto& val : tmp.data_) val *= -1;
    return tmp;
  }
  const Matrix& operator*(const Matrix& other) const {
    Matrix tmp(*this);
    return tmp *= other;
  };
  const Matrix& operator*(values_type value) const {
    Matrix tmp(*this);
    return tmp *= value;
  };
  friend const Matrix& operator*(values_type value, const Matrix& matrix) {
    return matrix * value;
  }
  const Matrix& operator/(values_type value) const {
    Matrix tmp(*this);
    return tmp /= value;
  };
  const Matrix& operator+=(const Matrix& other) {
    data_ += other.data_;
    return *this;
  };
  const Matrix& operator+=(values_type value) {
    data_ += value;
    return *this;
  };
  const Matrix& operator-=(const Matrix& other) {
    data_ -= other.data_;
    return *this;
  };
  const Matrix& operator-=(values_type value) {
    data_ -= value;
    return *this;
  };
  const Matrix& operator*=(const Matrix& other) {
    Matrix result;
    for (size_t row = 0; row < rows_; row++)
      for (size_t col = 0; col < other.cols_; col++)
        for (size_t k = 0; k < cols_; k++)
          result(row,col) += (*this)(row,k) * other(k,col);
    *this = std::move(result);
    return *this;
  };
  const Matrix& operator*=(values_type value) {
    data_ *= value;
    return *this;
  };
  const Matrix& operator/=(values_type value) {
    data_ /= value;
    return *this;
  };
  bool operator==(const Matrix& other) const { return data_ == other.data_; }
  bool operator!=(const Matrix& other) const { return !(*this == other); }
  values_type& operator[](size_t index) {
    if (index >= w * h) throw "Out of bounds";
    return data_[index];
  };
  const values_type& operator[](size_t index) const {
    if (index >= w * h) throw "Out of bounds";
    return data_[index];
  };
  values_type& operator()(size_t row, size_t col) {
    if (row >= rows_ || col >= cols_) throw "Out of bounds";
    return data_[cols_ * row + col];
  };
  const values_type& operator()(size_t row, size_t col) const {
    if (row >= rows_ || col >= cols_) throw "Out of bounds";
    return data_[cols_ * row + col];
  };
  std::array<values_type, w * h>& Data() { return data_.Data(); };
  const std::array<values_type, w * h>& Data() const { return data_.Data(); }
  friend std::ostream& operator<<(std::ostream& os, const Matrix& v) {
    for (const auto val : v.data_) os << val << " ";
    return os;
  }

 protected:
  MatData data_;
  size_t rows_ = h;
  size_t cols_ = w;
};
}  // namespace matrices
}  // namespace godison

godison::matrices::Matrix<2, 2> a;
godison::matrices::Matrix<2, 2> b;
auto c = a * b;
#endif  // MATRICES_H
