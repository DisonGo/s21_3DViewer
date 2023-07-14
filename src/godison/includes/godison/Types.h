#ifndef TYPES_H
#define TYPES_H
#include <iostream>
#include <vector>
using std::vector;
namespace godison {
namespace types {
struct Vertex {
  float x, y, z;
  Vertex(){};
  Vertex(float X, float Y, float Z) : x(X), y(Y), z(Z){};
  friend std::ostream& operator<<(std::ostream& os, const Vertex& v) {
    os << v.x << " " << v.y << " " << v.z;
    return os;
  }
  Vertex& operator+=(const Vertex& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
  };
  Vertex& operator-=(const Vertex& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
  };
};
struct VertexColor {
  float r, g, b;
};
struct VertexData {
  Vertex vertex;
};
struct Normal {
  float x, y, z;
};
struct TextureCoord {
  float u, v;
};
struct FaceVertex {
  int v_index, t_index, n_index;
};
struct TriangleFace {
  FaceVertex indices[3];
};
struct Face {
  std::vector<FaceVertex> indices;
};
struct OBJ {
  vector<Vertex> vertices;
  vector<Normal> normals;
  vector<Face> faces;
  vector<TextureCoord> texture_coords;
};
}  // namespace types
}  // namespace godison
#endif  // TYPES_H
