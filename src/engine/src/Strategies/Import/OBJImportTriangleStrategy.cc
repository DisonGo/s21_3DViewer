#include "Strategies/Import/OBJImportTriangleStrategy.h"

#include "Logger.h"
namespace s21 {
VAO OBJImportTriangleStrategy::Import(const OBJ& obj) const {
  VAO vao;
  vao.Bind();
  VBO vbo(GetVertexDataArray(obj));
  EBO ebo(GetTriangleIndexArray(obj));
  vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(VertexData), NULL);
  vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, sizeof(VertexData),
                 (void*)(3 * sizeof(float)));
  vao.SetIndicesN(ebo.GetSize());
  vao.SetVerticesN(vbo.GetSize());
  vao.Unbind();
  vbo.Unbind();
  ebo.Unbind();
  return vao;
}
std::vector<VertexData> OBJImportTriangleStrategy::GetVertexDataArray(
    const OBJ& obj) const {
  std::vector<VertexData> new_arr;
  //  for (auto& vertex : obj.vertices) new_arr.push_back({vertex});
  auto vert_size = obj.vertices.size();
  if (vert_size != obj.normals.size()) {
    static Logger logger("OBJImportTriangleStrategy");
    auto log = std::string("Vertices size: ") + std::to_string(vert_size);
    auto log2 =
        std::string("Normals size: ") + std::to_string(obj.normals.size());
    logger.Log(log.c_str(), Logger::LogLevel::kError);
    logger.Log(log2.c_str(), Logger::LogLevel::kError);
    throw "vertices.size != normals.size";
  }
  for (size_t i = 0; i < vert_size; ++i)
    new_arr.push_back({obj.vertices[i], obj.normals[i]});
  return new_arr;
}
std::vector<Face> OBJImportTriangleStrategy::GetTriangleIndexArray(
    const OBJ& obj) {
  std::vector<Face> triangle_indices;
  for (auto& face : obj.faces) {
    auto size = face.indices.size();
    const auto& first = face.indices.front();
    for (size_t i = 1; i < size - 1; ++i)
      triangle_indices.push_back(
          {{first, face.indices.at(i), face.indices.at(i + 1)}});
  }
  return triangle_indices;
};
}  // namespace s21
