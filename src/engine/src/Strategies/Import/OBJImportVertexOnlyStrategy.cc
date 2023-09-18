#include "Strategies/Import/OBJImportVertexOnlyStrategy.h"

namespace s21 {
VAO OBJImportVertexOnlyStrategy::Import(const OBJ& obj) const {
  VAO vao;
  vao.SetDrawArrays(true);
  vao.Bind();
  auto vertices = GetVertexDataArray(obj);
  VBO vbo(vertices);
  vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(VertexData), NULL);
  vao.SetVerticesN(vbo.GetSize());
  vao.Unbind();
  vbo.Unbind();
  return vao;
}
std::vector<VertexData> OBJImportVertexOnlyStrategy::GetVertexDataArray(
    const OBJ& obj) const {
  std::vector<VertexData> new_arr;
  size_t size = obj.vertices.size();
  // if (obj.vertices.size() != obj.normals.size())
  //   throw "vertices.size != normals.size";
  for (auto& face : obj.faces) {
    for (auto& indices : face.indices) {
      GLuint v_i = indices.v_index;
      if (v_i < size) new_arr.push_back({obj.vertices.at(v_i), {0, 0, 0}, {0,0}});
    }
  }
  return new_arr;
}
}  // namespace s21
