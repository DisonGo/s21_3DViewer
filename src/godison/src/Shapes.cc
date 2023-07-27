#include <godison/Shapes.h>
namespace godison {
namespace shapes {
vector<float> Polygon::GenerateVertices() {
  vector<float> vertices;
  vertices.reserve(n_ * 3);
  auto offset = offset_.ToVector<3>();
  for (size_t i = 0; i < n_; ++i) {
    double x = cx_ + r_ * std::sin(i * 2.0 * M_PI / n_);
    double y = cy_ + r_ * std::cos(i * 2.0 * M_PI / n_);
    vectors::Vector3D vertex(x, y);
    vertex += offset;
    vertices.push_back(vertex.X());
    vertices.push_back(vertex.Y());
    vertices.push_back(vertex.Z());
  }
  return vertices;
};
vector<unsigned> Polygon::GenerateIndices() {
  vector<unsigned> indices;
  indices.reserve(n_);
  for (size_t i = 0; i < n_; ++i) indices.push_back(i);
  return indices;
};
}  // namespace shapes
}  // namespace godison
