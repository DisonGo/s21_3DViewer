#include "Strategies/Import/OBJImportWireframeStrategy.h"

namespace s21 {
VAO OBJImportWireframeStrategy::Import(const OBJ& obj) const {
  VAO vao;
  vao.Bind();
  VBO vbo(GetVertexDataArray(obj));
  EBO ebo(GetWireFrameIndexArray(obj));
  vao.LinkAttrib(vbo, 2, 3, GL_FLOAT, sizeof(VertexData), NULL);
  vao.SetIndicesN(ebo.GetSize());
  vao.SetVerticesN(vbo.GetSize());
  vao.Unbind();
  vbo.Unbind();
  ebo.Unbind();
  return vao;
}
std::vector<VertexData> OBJImportWireframeStrategy::GetVertexDataArray(
    const OBJ& obj) const {
  std::vector<VertexData> new_arr;
  for (auto& vertex : obj.vertices) new_arr.push_back({vertex});
  return new_arr;
}
std::vector<Face> OBJImportWireframeStrategy::GetWireFrameIndexArray(
    const OBJ& obj) {
  std::vector<Face> triangle_indices;
  for (auto& face : obj.faces) {
    Face triangleFace;
    triangleFace.indices.push_back(face.indices.front());
    auto size = face.indices.size();
    for (size_t i = 1; i < size; ++i) {
      triangleFace.indices.push_back(face.indices.at(i));
      triangleFace.indices.push_back(face.indices.at(i));
    }
    triangleFace.indices.push_back(face.indices.front());
    triangle_indices.push_back(triangleFace);
  }
  return triangle_indices;
};
}  // namespace s21
