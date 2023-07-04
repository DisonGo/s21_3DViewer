#include "E/Mesh.h"

#include <iostream>

#include "GL/VBO.h"

std::vector<VertexData> reassembleVertexArray(std::vector<Vertex> old_arr) {
  std::vector<VertexData> new_arr;
  for (auto& vertex : old_arr) new_arr.push_back({vertex});
  return new_arr;
}
std::vector<Face> TriangleToPolygon(std::vector<TriangleFace> faces) {
  std::vector<Face> new_faces;
  for (auto& triangle : faces) {
    new_faces.push_back(
        {{triangle.indices[0], triangle.indices[1], triangle.indices[2]}});
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

Mesh::~Mesh() { qDebug() << "Mesh " << vertex_only_VAO_.ID_ << " destroyed"; }

void Mesh::Bind() { vertex_only_VAO_.Bind(); }

void Mesh::Unbind() { vertex_only_VAO_.Unbind(); }

void Mesh::Draw(GLenum type) {
  mix_VAO_.Bind();
  glDrawElements(type, indicesN_, GL_UNSIGNED_INT, 0);
  mix_VAO_.Unbind();
}

void Mesh::LoadObj(const s21::EdgeOBJ& obj) {
  // Index draw
  qDebug() << "Loading obj >> Vertex array ID:" << mix_VAO_.ID_;
  mix_VAO_.Bind();
  std::vector<VertexData> vData = reassembleVertexArray(obj.vertices);
  VBO VBO1(vData);
  EBO EBO1(obj.faces);
  indicesN_ = EBO1.GetSize();
  qDebug() << QString("Loading %1 indices.").arg(indicesN_);
  mix_VAO_.LinkAttrib(VBO1, 0, 3, GL_FLOAT, sizeof(VertexData), (void*)0);
  mix_VAO_.Unbind();
  VBO1.Unbind();
  EBO1.Unbind();
}

void Mesh::LoadObj(const s21::TriangleOBJ& obj) {
  // Index draw
  qDebug() << "Loading obj >> Vertex array ID:" << mix_VAO_.ID_;
  mix_VAO_.Bind();
  std::vector<VertexData> vData = reassembleVertexArray(obj.vertices);
  auto faces = TriangleToPolygon(obj.faces);
  qDebug() << QString("Loading %1 indices.").arg(indicesN_);
  VBO VBO1(vData);
  EBO EBO1(faces);
  indicesN_ = EBO1.GetSize();
  mix_VAO_.LinkAttrib(VBO1, 0, 3, GL_FLOAT, sizeof(VertexData), (void*)0);
  mix_VAO_.Unbind();
  VBO1.Unbind();
  EBO1.Unbind();
}
