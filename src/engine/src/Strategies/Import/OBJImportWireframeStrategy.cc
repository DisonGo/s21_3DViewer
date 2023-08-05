#include "Strategies/Import/OBJImportWireframeStrategy.h"

namespace s21 {
VAO OBJImportWireframeStrategy::Import(const OBJ& obj) const {
  VAO vao;
  vao.Bind();
  VBO vbo(GetVertexDataArray(obj));
  EBO ebo(GetWireFrameIndexArray(obj));
  vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(VertexData), NULL);
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
  auto vert_size = obj.vertices.size();
  if (vert_size != obj.normals.size()) throw "vertices.size != normals.size";
  for (size_t i = 0; i < vert_size; ++i)
    new_arr.push_back({obj.vertices[i], obj.normals[i]});
  // for (auto& vertex : obj.vertices) new_arr.push_back({vertex});
  return new_arr;
}
std::vector<Face> OBJImportWireframeStrategy::GetWireFrameIndexArray(
    const OBJ& obj) {
  std::vector<Face> indices;
  for (auto& face : obj.faces) {
    Face wire_face;
    wire_face.indices.push_back(face.indices.front());
    auto size = face.indices.size();
    for (size_t i = 1; i < size; ++i) {
      wire_face.indices.push_back(face.indices.at(i));
      wire_face.indices.push_back(face.indices.at(i));
    }
    wire_face.indices.push_back(face.indices.front());
    indices.push_back(wire_face);
  }
  return indices;
};
}  // namespace s21
