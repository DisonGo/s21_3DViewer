#include "Strategies/Import/OBJImportNormalsStrategy.h"

#include "godison/Vectors.h"
using godison::vectors::Vector3D;
namespace s21 {
VAO OBJImportNormalsStrategy::Import(const OBJ& obj) const {
  VAO vao;
  vao.Bind();
  VBO vbo(GetVertexDataArray(obj));
  EBO ebo(GetNormalsIndexArray(obj));
  vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(VertexData), NULL);
  vao.SetIndicesN(ebo.GetSize());
  vao.SetVerticesN(vbo.GetSize());
  vao.Unbind();
  vbo.Unbind();
  ebo.Unbind();
  return vao;
}
std::vector<VertexData> OBJImportNormalsStrategy::GetVertexDataArray(
    const OBJ& obj) const {
  std::vector<VertexData> new_arr;
  auto vert_size = obj.vertices.size();
  if (vert_size != obj.normals.size()) {
    static Logger logger("OBJImportNormalsStrategy");
    auto log = std::string("Vertices size: ") + std::to_string(vert_size);
    auto log2 =
        std::string("Normals size: ") + std::to_string(obj.normals.size());
    logger.Log(log.c_str(), Logger::LogLevel::kError);
    logger.Log(log2.c_str(), Logger::LogLevel::kError);
    throw "vertices.size != normals.size";
  }
  for (size_t i = 0; i < vert_size; ++i) {
    Vector3D vertex{obj.vertices[i].x, obj.vertices[i].y, obj.vertices[i].z};
    Vector3D normal{obj.normals[i].x, obj.normals[i].y, obj.normals[i].z};

    auto second_vert = vertex + normal.Normalized() * 0.01;
    new_arr.push_back({{vertex.X(), vertex.Y(), vertex.Z()}, {0, 0, 0}});
    new_arr.push_back(
        {{second_vert[0], second_vert[1], second_vert[2]}, {0, 0, 0}});
  }
  return new_arr;
}
std::vector<Face> OBJImportNormalsStrategy::GetNormalsIndexArray(
    const OBJ& obj) {
  std::vector<Face> indices;
  int i = 0;
  for (const auto& vert : obj.vertices) {
    indices.push_back({{{i, 0, 0}, {i + 1, 0, 0}, {i + 1, 0, 0}, {i, 0, 0}}});
    i += 2;
  }
  return indices;
};
}  // namespace s21
