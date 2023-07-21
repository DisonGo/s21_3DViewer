#include "Strategies/Import/OBJImportStandartStrategy.h"

namespace s21 {
VAO OBJImportStandartStrategy::Import(const OBJ& obj) const {
  VAO vao;
  vao.Bind();
  VBO vbo(GetVertexDataArray(obj));
  EBO ebo(obj.faces);
  vao.LinkAttrib(vbo, 2, 3, GL_FLOAT, sizeof(VertexData), NULL);
  vao.SetIndicesN(ebo.GetSize());
  vao.SetVerticesN(vbo.GetSize());
  vao.Unbind();
  vbo.Unbind();
  ebo.Unbind();
  return vao;
}

std::vector<VertexData> OBJImportStandartStrategy::GetVertexDataArray(
    const OBJ& obj) const {
  std::vector<VertexData> new_arr;
  for (auto& vertex : obj.vertices) new_arr.push_back({vertex});
  return new_arr;
}
}  // namespace s21
