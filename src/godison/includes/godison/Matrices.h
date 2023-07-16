#ifndef MATRICES_H
#define MATRICES_H
#include <godison/Vectors.h>

#include <algorithm>
// TODO Translate
// TODO Rotate
// TODO Scale
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
    os << v.data_;
    return os;
  }
  void SwapRows(size_t r1, size_t r2) {
    if (r1 == r2) return;
    if (r1 >= rows_ || r2 >= rows_) throw "Out of bounds";
    for (size_t j = 0; j < cols_; j++)
      std::swap((*this)(r1, j), (*this)(r2, j));
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
template <size_t size, typename values_type = float>
class SquareMatrix : public Matrix<size, size, values_type> {
  using MatProto = Matrix<size, size, values_type>;

 public:
  SquareMatrix() : MatProto(){};
  SquareMatrix(const MatProto& other) : MatProto(other){};
  SquareMatrix(MatProto&& other) : MatProto(other){};
  SquareMatrix(std::initializer_list<values_type> vals) : MatProto(vals) {}
  void SetToIdentity() {
    (*this).Data().fill(0);
    for (size_t i = 0; i < size; ++i) (*this)(i, i) = 1;
  }
  double Determinant() {
    Matrix A = *this;
    double det = 1;
    constexpr double EPS = 1e-6;

    for (int i = 0; i < size; ++i) {
      double pivot = A(i, i);
      int pivotRow = i;
      for (size_t row = i + 1; row < size; ++row) {
        if (std::abs(A(row, i)) > std::abs(pivot)) {
          pivot = A(row, i);
          pivotRow = row;
        }
      }
      if (std::abs(pivot) < EPS) {
        return 0.0;
      }
      if (pivotRow != i) {
        A.SwapRows(i, pivotRow);
        det *= -1.0;
      }
      det *= pivot;

      for (size_t row = i + 1; row < size; ++row) {
        for (size_t col = i + 1; col < size; ++col) {
          A(row, col) -= A(row, i) * A(i, col) / pivot;
        }
      }
    }
    if (det < EPS) det = 0;
    return det;
  }
  SquareMatrix Invert() {
    auto n = size;

    // Initialize the inverse matrix with the identity matrix
    SquareMatrix A = *this;
    SquareMatrix A_inv = *this;
    A_inv.SetToIdentity();
    for (size_t j = 0; j < n; ++j) {
      // Find pivot row
      values_type pivot = std::abs(A(j, j));
      size_t pivotRow = j;
      for (size_t row = j + 1; row < size; ++row) {
        const auto val = std::abs(A(row, j));
        if (val > pivot) {
          pivot = val;
          pivotRow = row;
        }
      }
      // Swap rows if necessary
      if (pivotRow != j) {
        A.SwapRows(j, pivotRow);
        A_inv.SwapRows(j, pivotRow);
      }

      // Divide pivot row by pivot element
      pivot = A(j, j);
      for (size_t col = 0; col < size; ++col) {
        A(j, col) /= pivot;
        A_inv(j, col) /= pivot;
      }

      // Eliminate all other elements in column j
      for (size_t i = 0; i < size; ++i) {
        if (i == j) continue;
        const auto factor = A(i, j);
        for (size_t col = 0; col < size; ++col) {
          A(i, col) -= (factor * A(j, col));
          A_inv(i, col) -= (factor * A_inv(j, col));
        }
      }
    }
    return A_inv;
  };
};
}  // namespace matrices
}  // namespace godison

#endif  // MATRICES_H
