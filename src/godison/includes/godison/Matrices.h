#ifndef GMATRICES_H
#define GMATRICES_H
#include <godison/GUtility.h>
#include <godison/Vectors.h>

#include <algorithm>
#include <iomanip>

namespace godison {
namespace matrices {
using vectors::Vector;
template <size_t w, size_t h, typename values_type = float>
class Matrix {
 public:
  using MatData = Vector<values_type, w * h>;
  Matrix() {}
  Matrix(values_type fill_value) { Fill(fill_value); }
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
  values_type* RawData() { return data_.Data().data(); }
  const values_type* RawConstData() const { return data_.Data().data(); }

  friend std::ostream& operator<<(std::ostream& os, const Matrix& v) {
    for (size_t i = 0; i < h; ++i) {
      for (size_t j = 0; j < w; ++j) {
        os << std::setw(9) << v(i, j) << '\t';
      }
      os << "\n";
    }
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
  void Fill(values_type value) { Data().fill(value); }

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
class Matrix2x2 : public SquareMatrix<2> {
 public:
  using SquareMatrix::SquareMatrix;
};
class Matrix3x3 : public SquareMatrix<3> {
 public:
  using SquareMatrix::SquareMatrix;
};
class Matrix4x4 : public SquareMatrix<4> {
  // scale(const QVector3D &vector)
  // rotate(float angle, const QVector3D &vector)
  // ortho(float left, float right, float bottom, float top, float nearPlane,
  // float farPlane) perspective(float verticalAngle, float aspectRatio, float
  // nearPlane, float farPlane)
 public:
  using SquareMatrix::SquareMatrix;
  void LookAt(vectors::Vector3D eye, vectors::Vector3D at,
              vectors::Vector3D up) {
    // TODO Think about -0 values.
    auto z_axis = (vectors::Vector3D)(at - eye).Normalized();
    auto x_axis = (vectors::Vector3D)z_axis.CrossProduct(up).Normalized();
    auto y_axis = x_axis.CrossProduct(z_axis);
    z_axis.Negate();
    *this =
        (Matrix4x4){x_axis.X(),       y_axis.X(),       z_axis.X(),       0,
                    x_axis.Y(),       y_axis.Y(),       z_axis.Y(),       0,
                    x_axis.Z(),       y_axis.Z(),       z_axis.Z(),       0,
                    -x_axis.Dot(eye), -y_axis.Dot(eye), -z_axis.Dot(eye), 1};
  };
  void Translate(vectors::Vector3D translate) {
    data_[0 + 3 * 4] = translate.X();
    data_[1 + 3 * 4] = translate.Y();
    data_[2 + 3 * 4] = translate.Z();
  };
  void Rotate(const float angle, const vectors::Vector3D& axis) {
    auto radian = godison::utility::GToRadians(angle);
    auto cosine = cos(radian);
    auto sine = sin(radian);
    /* one munis cosine */
    auto omcosine = 1 - cosine;

    auto x = axis.X();
    auto y = axis.Y();
    auto z = axis.Z();

    data_[0 + 0 * 4] = (x * x * omcosine + cosine);
    data_[1 + 0 * 4] = (x * y * omcosine + z * sine);
    data_[2 + 0 * 4] = (x * z * omcosine - y * sine);

    data_[0 + 1 * 4] = (y * x * omcosine - z * sine);
    data_[1 + 1 * 4] = (y * y * omcosine + cosine);
    data_[2 + 1 * 4] = (y * z * omcosine + x * sine);

    data_[0 + 2 * 4] = (z * x * omcosine + y * sine);
    data_[1 + 2 * 4] = (z * y * omcosine - x * sine);
    data_[2 + 2 * 4] = (z * z * omcosine + cosine);
  }
  void Scale(const vectors::Vector3D& scale) {
    data_[0 + 0 * 4] = scale.X();
    data_[1 + 1 * 4] = scale.Y();
    data_[2 + 2 * 4] = scale.Z();
  }
  void Perspective(float left, float right, float bottom, float top,
                   float nearPlane, float farPlane) {
    data_.Data().fill(0);
    data_[0 + 0 * 4] = (2 * nearPlane / (right - left));
    data_[1 + 1 * 4] = (2 * nearPlane / (top - bottom));
    data_[2 + 0 * 4] = ((right + left) / (right - left));
    data_[2 + 1 * 4] = ((top + bottom) / (top - bottom));
    data_[2 + 2 * 4] = ((nearPlane + farPlane) / (nearPlane - farPlane));
    data_[2 + 3 * 4] = (-1.0f);
    data_[3 + 2 * 4] = ((2.0f * nearPlane * farPlane) / (nearPlane - farPlane));
  }
  void Perspective(float fov, float aspectRatio, float nearPlane,
                   float farPlane) {
    data_.Data().fill(0);
    float e = 1.0f / tan(godison::utility::GToRadians(0.5f * fov));
    data_[0 + 0 * 4] = (e / aspectRatio);
    data_[1 + 1 * 4] = (e);
    data_[2 + 2 * 4] = ((nearPlane + farPlane) / (nearPlane - farPlane));
    data_[2 + 3 * 4] = (-1.0f);
    data_[3 + 2 * 4] = ((2.0f * nearPlane * farPlane) / (nearPlane - farPlane));
  }
  void Orthographic(float left, float right, float bottom, float top,
                    float nearPlane, float farPlane) {
    SetToIdentity();
    data_[0 + 0 * 4] = (2.0f / (right - left));
    data_[1 + 1 * 4] = (2.0f / (top - bottom));
    data_[2 + 2 * 4] = (2.0f / (nearPlane - farPlane));

    data_[0 + 3 * 4] = ((left + right) / (left - right));
    data_[1 + 3 * 4] = ((bottom + top) / (bottom - top));
    data_[2 + 3 * 4] = ((nearPlane + farPlane) / (nearPlane - farPlane));
  }
};
}  // namespace matrices
}  // namespace godison

#endif  // GMATRICES_H
