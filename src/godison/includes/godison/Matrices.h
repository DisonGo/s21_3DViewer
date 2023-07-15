#ifndef MATRICES_H
#define MATRICES_H
#include <godison/Vectors.h>

#include <algorithm>
// TODO Determinant (test)
// TODO Complements
// TODO Inverse
// TODO Transpose
// TODO Translate
// TODO Rotate
// TODO Scale
// TODO SetToIdentity
// TODO Square matrix prototype
// TODO Preset square matrices
// TODO LookAt
// TODO Ortho
// TODO Perpective
// TODO LookAt
namespace godison {
namespace matrices {
using vectors::Vector;
template <size_t w, size_t h, typename values_type = float>
class Matrix {
 public:
  using MatData = Vector<values_type, w * h>;
  Matrix(){};
  Matrix(std::initializer_list<values_type> vals) : data_(vals) {}
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
  Matrix operator+(const Matrix& other) const {
    Matrix tmp(*this);
    return tmp += other;
  };
  Matrix operator+(values_type value) const {
    Matrix tmp(*this);
    return tmp += value;
  };
  Matrix operator+() const { return *this; }
  Matrix operator-(const Matrix& other) const {
    Matrix tmp(*this);
    return tmp -= other;
  };
  Matrix operator-(values_type value) const {
    Matrix tmp(*this);
    return tmp -= value;
  };
  Matrix operator-() const {
    Matrix tmp(*this);
    for (auto& val : tmp.data_) val *= -1;
    return tmp;
  }
  Matrix operator*(const Matrix& other) const {
    Matrix tmp(*this);
    return tmp *= other;
  };
  Matrix operator*(values_type value) const {
    Matrix tmp(*this);
    return tmp *= value;
  };
  friend const Matrix& operator*(values_type value, const Matrix& matrix) {
    return matrix * value;
  }
  Matrix operator/(values_type value) const {
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
          result(row, col) += (*this)(row, k) * other(k, col);
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
  void SwapRows(size_t r1, size_t r2) {
    if (r1 >= rows_ || r2 >= rows_) throw "Out of bounds";
    auto row1_beg = data_.Data().begin() + r1 * cols_;
    auto row2_beg = data_.Data().begin() + r2 * cols_;
    std::swap_ranges(data_.Data().begin(), row1_beg, row2_beg);
  }
  // void SwapCols(size_t c1, size_t c2) {
  //   if (c1 >= cols_ || c2 >= cols_) throw "Out of bounds";
  //   auto col1_beg = data_.Data().begin() + c1 * rows_;
  //   auto col2_beg = data_.Data().begin() + c2 * rows_;
  //   std::swap_ranges(data_.Data().begin(), col1_beg, col2_beg);
  // }
  Matrix<h, w> Transpose() {
    Matrix<h, w> result;
    for (size_t col = 0; col < cols_; col++)
      for (size_t row = 0; row < rows_; row++)
        result(col, row) = (*this)(row, col);
    return result;
  }

 protected:
  MatData data_;
  size_t rows_ = h;
  size_t cols_ = w;
};
template <size_t size , typename values_type = float>
class SquareMatrix : public Matrix<size, size, values_type> {
  using MatProto = Matrix<size, size, values_type>;
 public:
  double Determinant() {
    const double eps = 1e-6;
    Matrix A = *this;
    double det = 1;

    for (size_t i = 0; i < size; ++i) {
      size_t k = i;
      for (size_t j = i + 1; j < size; ++j) {
        if (std::abs(A(j, i)) > std::abs(A(k, i))) {
          k = j;
        }
      }

      if (std::abs(A(k, i)) < eps) {
        return 0;
      }

      if (i != k) {
        det *= -1;
        A.SwapCols(i, k);
      }

      det *= A(i, i);

      for (size_t j = i + 1; j < size; ++j) {
        values_type coeff = A(j, i) / A(i, i);
        for (size_t l = i; l < size; ++l) {
          A(j, l) -= A(i, l) * coeff;
        }
      }
    }

    return det;
  }
};
}  // namespace matrices
}  // namespace godison

#endif  // MATRICES_H
