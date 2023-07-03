#include "E/Mesh.h"

#include "GL/VBO.h"
std::vector<VertexData> reassembleVertexArray(std::vector<Vertex> old_arr,
                                              std::vector<TriangleFace> faces) {
  std::vector<VertexData> new_arr;
  size_t size = old_arr.size();
  for (auto& face : faces) {
    for (size_t i = 0; i < 3; i++) {
      GLuint index = face.indices_[i].v_index_;
      if (index < size) new_arr.push_back({old_arr.at(index)});
    }
  }
  return new_arr;
}
std::vector<VertexData> reassembleVertexArray(std::vector<Vertex> old_arr,
                                              std::vector<Face> faces) {
  std::vector<VertexData> new_arr;
  size_t size = old_arr.size();
  for (auto& face : faces) {
    for (auto& indices : face.indices_) {
      GLuint index = indices.v_index_;
      if (index < size) new_arr.push_back({old_arr.at(index)});
    }
  }
  return new_arr;
}
std::vector<VertexData> reassembleVertexArray(std::vector<Vertex> old_arr) {
  std::vector<VertexData> new_arr;
  for (auto& vertex : old_arr) new_arr.push_back({vertex});
  return new_arr;
}
std::vector<Face> TriangleToPolygon(std::vector<TriangleFace> faces) {
  std::vector<Face> new_faces;
  for (auto& triangle : faces) {
    new_faces.push_back(
        {{triangle.indices_[0], triangle.indices_[1], triangle.indices_[2]}});
  }
  return new_faces;
}
Mesh::Mesh() {
  initializeOpenGLFunctions();
  draw_config_ = &DrawConfig::Instance();
}

Mesh::Mesh(s21::EdgeOBJ obj) {
  initializeOpenGLFunctions();
  draw_config_ = &DrawConfig::Instance();
  LoadObj(obj);
}

Mesh::Mesh(s21::TriangleOBJ obj) {
  initializeOpenGLFunctions();
  draw_config_ = &DrawConfig::Instance();
  LoadObj(obj);
}

Mesh::~Mesh() {
  qDebug() << "Mesh " << vertex_only_VAO_.ID_ << " destroyed";
  vertex_only_VAO_.Delete();
}

void Mesh::Bind() { vertex_only_VAO_.Bind(); }
void Mesh::Unbind() { vertex_only_VAO_.Unbind(); }
void Mesh::Draw(GLenum type) {
  if (draw_config_->index_draw_) {
    mix_VAO_.Bind();
    glDrawElements(type, indicesN_, GL_UNSIGNED_INT, 0);
    mix_VAO_.Unbind();
  }
  if (draw_config_->vertex_only_draw_) {
    vertex_only_VAO_.Bind();
    glDrawArrays(type, 0, verticesN_);
    vertex_only_VAO_.Unbind();
  }
}

void Mesh::LoadObj(const s21::EdgeOBJ& obj) {
  // Index draw
  qDebug() << "Loading obj >> Vertex array ID:" << mix_VAO_.ID_;
  mix_VAO_.Bind();
  std::vector<VertexData> vData = reassembleVertexArray(obj.vertices_);
  for (auto& face : obj.faces_) indicesN_ += face.indices_.size();
  qDebug() << QString("Loading %1 indices.").arg(indicesN_);
  VBO VBO1(vData);
  EBO EBO1(obj.faces_);
  mix_VAO_.LinkAttrib(VBO1, 0, 3, GL_FLOAT, sizeof(VertexData), (void*)0);
  mix_VAO_.Unbind();
  VBO1.Unbind();
  EBO1.Unbind();
  // Vertex Only Draw
  qDebug() << "Loading obj >> Vertex array ID:" << vertex_only_VAO_.ID_;
  vertex_only_VAO_.Bind();
  vData = reassembleVertexArray(obj.vertices_, obj.faces_);
  verticesN_ = vData.size();

  qDebug() << QString("Loading %1 vertices.").arg(verticesN_);

  VBO VBO2(vData);
  vertex_only_VAO_.LinkAttrib(VBO2, 0, 3, GL_FLOAT, sizeof(VertexData),
                              (void*)0);
  vertex_only_VAO_.Unbind();
  VBO2.Unbind();
}

void Mesh::LoadObj(const s21::TriangleOBJ& obj) {
  // Index draw
  qDebug() << "Loading obj >> Vertex array ID:" << mix_VAO_.ID_;
  mix_VAO_.Bind();
  std::vector<VertexData> vData = reassembleVertexArray(obj.vertices_);
  auto faces = TriangleToPolygon(obj.faces_);
  for (auto& face : faces) indicesN_ += face.indices_.size();
  qDebug() << QString("Loading %1 indices.").arg(indicesN_);
  VBO VBO1(vData);
  EBO EBO1(faces);
  mix_VAO_.LinkAttrib(VBO1, 0, 3, GL_FLOAT, sizeof(VertexData), (void*)0);
  mix_VAO_.Unbind();
  VBO1.Unbind();
  EBO1.Unbind();
  // Vertex Only Draw
  qDebug() << "Loading obj >> Vertex array ID:" << vertex_only_VAO_.ID_;
  vertex_only_VAO_.Bind();
  vData = reassembleVertexArray(obj.vertices_, obj.faces_);
  verticesN_ = vData.size();

  qDebug() << QString("Loading %1 vertices.").arg(verticesN_);

  VBO VBO2(vData);
  vertex_only_VAO_.LinkAttrib(VBO2, 0, 3, GL_FLOAT, sizeof(VertexData),
                              (void*)0);
  vertex_only_VAO_.Unbind();
  VBO2.Unbind();
}
