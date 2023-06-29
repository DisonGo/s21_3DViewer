#include "E/Mesh.h"

#include "GL/VBO.h"
std::vector<VertexData> reassembleVertexArray(std::vector<Vertex> old_arr,
                                              std::vector<TriangleFace> faces) {
  std::vector<VertexData> new_arr;
  size_t size = old_arr.size();
  for (auto& face : faces) {
    for (size_t i = 0; i < 3; i++) {
      GLuint index = face.indices[i].vIndex;
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
    for (auto& indices : face.indices) {
      GLuint index = indices.vIndex;
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
        {{triangle.indices[0], triangle.indices[1], triangle.indices[2]}});
  }
  return new_faces;
}
Mesh::Mesh() {
  initializeOpenGLFunctions();
  drawConfig_ = &DrawConfig::Instance();
}

Mesh::Mesh(s21::EdgeOBJ obj) {
  initializeOpenGLFunctions();
  drawConfig_ = &DrawConfig::Instance();
  LoadObj(obj);
}

Mesh::Mesh(s21::TriangleOBJ obj) {
  initializeOpenGLFunctions();
  drawConfig_ = &DrawConfig::Instance();
  LoadObj(obj);
}

Mesh::~Mesh() {
  qDebug() << "Mesh " << vertexOnlyVAO_.ID << " destroyed";
  vertexOnlyVAO_.Delete();
}

void Mesh::Bind() { vertexOnlyVAO_.Bind(); }
void Mesh::Unbind() { vertexOnlyVAO_.Unbind(); }
void Mesh::Draw(GLenum type) {
  if (drawConfig_->IndexDraw)
  {
    mixVAO_.Bind();
    glDrawElements(type, indicesN, GL_UNSIGNED_INT, (void*)0);
    mixVAO_.Unbind();
  }
  if (drawConfig_->VertexOnlyDraw) {
    vertexOnlyVAO_.Bind();
    glDrawArrays(type, 0, verticesN);
    vertexOnlyVAO_.Unbind();
  }
}

void Mesh::LoadObj(const s21::EdgeOBJ& obj) {
  // Index draw
  qDebug() << "Loading obj >> Vertex array ID:" << mixVAO_.ID;
  mixVAO_.Bind();
  std::vector<VertexData> vData = reassembleVertexArray(obj.vertices);
  for (auto& face : obj.faces) indicesN += face.indices.size();
  qDebug() << QString("Loading %1 indices.").arg(indicesN);
  VBO VBO1(vData);
  mixVAO_.LinkAttrib(VBO1, 0, 3, GL_FLOAT, sizeof(VertexData), (void*)0);
  EBO EBO1(obj.faces);
  mixVAO_.Unbind();
  VBO1.Unbind();
  EBO1.Unbind();
  //Vertex Only Draw
  qDebug() << "Loading obj >> Vertex array ID:" << vertexOnlyVAO_.ID;
  vertexOnlyVAO_.Bind();
  vData = reassembleVertexArray(obj.vertices, obj.faces);
  verticesN = vData.size();

  qDebug() << QString("Loading %1 vertices.").arg(verticesN);

  VBO VBO2(vData);
  vertexOnlyVAO_.LinkAttrib(VBO2, 0, 3, GL_FLOAT, sizeof(VertexData), (void*)0);
  vertexOnlyVAO_.Unbind();
  VBO2.Unbind();
}

void Mesh::LoadObj(const s21::TriangleOBJ& obj) {
  // Index draw
  qDebug() << "Loading obj >> Vertex array ID:" << mixVAO_.ID;
  mixVAO_.Bind();
  std::vector<VertexData> vData = reassembleVertexArray(obj.vertices);
  auto faces = TriangleToPolygon(obj.faces);
  for (auto& face : faces) indicesN += face.indices.size();
  qDebug() << QString("Loading %1 indices.").arg(indicesN);
  VBO VBO1(vData);

  mixVAO_.LinkAttrib(VBO1, 0, 3, GL_FLOAT, sizeof(VertexData), (void*)0);
  EBO EBO1(faces);

  mixVAO_.Unbind();
  VBO1.Unbind();
  EBO1.Unbind();
  //Vertex Only Draw
  qDebug() << "Loading obj >> Vertex array ID:" << vertexOnlyVAO_.ID;
  vertexOnlyVAO_.Bind();
  vData = reassembleVertexArray(obj.vertices, obj.faces);
  verticesN = vData.size();

  qDebug() << QString("Loading %1 vertices.").arg(verticesN);

  VBO VBO2(vData);
  vertexOnlyVAO_.LinkAttrib(VBO2, 0, 3, GL_FLOAT, sizeof(VertexData), (void*)0);
  vertexOnlyVAO_.Unbind();
  VBO2.Unbind();
}
