#ifndef SHAPES_H
#define SHAPES_H
#include <godison/Types.h>
#include <godison/Vectors.h>

#include <type_traits>
#include <vector>

using std::vector;
namespace godison {
namespace shapes {
class Shape {
 public:
  virtual vector<float> GenerateVertices() = 0;
  virtual vector<unsigned> GenerateIndices() = 0;
  template <typename T>
  friend void GenerateDataInto(T& container);
  template <typename T>
  friend T GenerateData();

 protected:
  Shape(vectors::Vector4D offset = {0, 0, 0, 0}) : offset_(offset){};
  ~Shape() = default;

  vectors::Vector4D offset_;
};
class Polygon : public Shape {
 public:
  Polygon(size_t n, double cx, double cy, double r,
          vectors::Vector4D offset = {0, 0, 0, 0})
      : Shape(offset), n_(n), cx_(cx), cy_(cy), r_(r){};
  vector<float> GenerateVertices() override;
  vector<unsigned> GenerateIndices() override;

 protected:
  size_t n_;
  double cx_, cy_, r_;
};
class Rectangle : public Shape {
 public:
  //  Rectangle(double x = 0, double y = 0, double w = 0, double h = 0,
  //            vectors::Vector4D offset = {0, 0, 0, 0}){};
};

class Point : public Shape {
 public:
  Point();
  virtual vector<float> GenerateVertices() override { return vector<float>(); };
  virtual vector<unsigned> GenerateIndices() override {
    return vector<unsigned>();
  };
};
}  // namespace shapes
}  // namespace godison
#endif  // SHAPES_H
