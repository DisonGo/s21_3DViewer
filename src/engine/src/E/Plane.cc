#include "E/Plane.h"

#include "iostream"
namespace s21 {
void Plane::GeneratePlane() {
  OBJ obj;
  obj.vertices = GenerateVertices();
  obj.faces = GenerateIndices();
  auto importer = new OBJImportStandartStrategy;
  UploadMesh(obj, importer);
  auto& mesh = GetMesh(0);
  mesh.SetBufferToggle(kStandartImport, true);
  mesh.SetBufferToggle(kWireframeImport, false);
  mesh.SetBufferToggle(kTriangleImport, false);
  delete importer;
}
std::vector<Face> Plane::GenerateIndices() {
  std::vector<Face> indices;
  int yLength = hor_divisions_;
  int xLength = vert_divisions_;
  int numStripsRequired = yLength - 1;
  int numDegensRequired = 2 * (numStripsRequired - 1);
  int verticesPerStrip = 2 * xLength;
  unsigned* heightMapIndexData =
      new unsigned[(verticesPerStrip * numStripsRequired) + numDegensRequired];
  int offset = 0;

  for (int y = 0; y < yLength - 1; y++) {
    if (y > 0) {
      heightMapIndexData[offset++] = (unsigned)(y * yLength);
    }

    for (int x = 0; x < xLength; x++) {
      // One part of the strip
      heightMapIndexData[offset++] = (unsigned)((y * yLength) + x);
      heightMapIndexData[offset++] = (unsigned)(((y + 1) * yLength) + x);
    }

    if (y < yLength - 2) {
      // Degenerate end: repeat last vertex
      heightMapIndexData[offset++] =
          (unsigned)(((y + 1) * yLength) + (xLength - 1));
    }
  }
  Face f;
  for (int i = 0; i < offset; ++i)
    f.indices.push_back({(int)heightMapIndexData[i], -1, -1});
  delete[] heightMapIndexData;
  indices.push_back(f);
  return indices;
}
std::vector<Vertex> Plane::GenerateVertices() {
  double minW = -(w_ / 2);
  double minH = -(h_ / 2);
  //  double maxW = w_ / 2;
  //  double maxH = h_ / 2;
  double stepW = w_ / std::max(vert_divisions_, 1);
  double stepH = h_ / std::max(hor_divisions_, 1);
  std::vector<Vertex> vertices;

  double y = minH;
  int i = 0;
  for (; i < hor_divisions_; i++, y += stepH) {
    double x = minW;
    int j = 0;
    for (; j < vert_divisions_; j++, x += stepW)
      vertices.emplace_back(x, y, 0.);
  }
  return vertices;
}
}  // namespace s21
