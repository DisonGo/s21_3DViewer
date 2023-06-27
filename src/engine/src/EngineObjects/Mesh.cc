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
Mesh::Mesh() { initializeOpenGLFunctions(); }

Mesh::Mesh(s21::EdgeOBJ obj) {
  initializeOpenGLFunctions();
  LoadObj(obj);
}

Mesh::Mesh(s21::TriangleOBJ obj)
{
    initializeOpenGLFunctions();
    LoadObj(obj);
}

Mesh::~Mesh() {
  qDebug() << "Mesh " << vertexBuf.ID << " destroyed";
  vertexBuf.Delete();
}

void Mesh::Bind() { vertexBuf.Bind(); }
void Mesh::Unbind() { vertexBuf.Unbind(); }
void Mesh::Draw(GLenum type) {
  Bind();
  glDrawArrays(type, 0, verticesN);
  Unbind();
}

void Mesh::LoadObj(const s21::EdgeOBJ &obj)
{
    qDebug() << "Loading obj >> Vertex array ID:" << vertexBuf.ID;
    vertexBuf.Bind();
    std::vector<VertexData> vData =
        reassembleVertexArray(obj.vertices, obj.faces);
    verticesN = vData.size();
    indicesN = obj.faces.size() * 3;
    qDebug() << QString("Loading %1 vertices.").arg(verticesN);
    VBO VBO1(vData);
    vertexBuf.LinkAttrib(VBO1, 0, 3, GL_FLOAT, sizeof(VertexData), (void*)0);
    vertexBuf.Unbind();
    VBO1.Unbind();
}

void Mesh::LoadObj(const s21::TriangleOBJ &obj)
{
    qDebug() << "Loading obj >> Vertex array ID:" << vertexBuf.ID;
    vertexBuf.Bind();
    std::vector<VertexData> vData =
        reassembleVertexArray(obj.vertices, obj.faces);
    verticesN = vData.size();
    indicesN = obj.faces.size() * 3;
    qDebug() << QString("Loading %1 vertices.").arg(verticesN);
    VBO VBO1(vData);
    vertexBuf.LinkAttrib(VBO1, 0, 3, GL_FLOAT, sizeof(VertexData), (void*)0);
    vertexBuf.Unbind();
    VBO1.Unbind();
}

