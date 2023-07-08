#ifndef PLANE_H
#define PLANE_H

#include "E/Object3D.h"
namespace s21 {
class Plane : public Object3D {
 public:
  Plane(double w = 1, double h = 1, int vert_divisions = 1,
        int hor_divisions = 1)
      : w_(w),
        h_(h),
        vert_divisions_(vert_divisions),
        hor_divisions_(hor_divisions) {
    GeneratePlane();
  };

 private:
  void GeneratePlane();
  std::vector<Face> GenerateIndices();
  std::vector<Vertex> GenerateVertices();
  std::vector<Vertex> vertices_;
  std::vector<Face> indices_;
  std::vector<Normal> normals_;
  std::vector<TextureCoord> uvs_;
  double w_ = 1, h_ = 1;
  int vert_divisions_ = 0;
  int hor_divisions_ = 0;
};
}  // namespace s21
#endif  // PLANE_H
