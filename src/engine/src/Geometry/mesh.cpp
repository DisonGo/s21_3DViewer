#include "mesh.h"
#include "VBO.h"
#include "EBO.h"
std::vector<VertexData> reassembleVertexArray(std::vector<Vertex> old_arr, std::vector<Face> faces) {
  std::vector<VertexData> new_arr;
  size_t size = old_arr.size();
  for (auto face : faces) {
    for (auto indexTuple : face.indices) {
      GLuint index = indexTuple.vIndex;
      if (index < size)
        new_arr.push_back({old_arr.at(index)});
    }
  }
  return new_arr;
}
Mesh::Mesh()
{
  initializeOpenGLFunctions();
}

Mesh::Mesh(OBJ obj)
{
  initializeOpenGLFunctions();
  LoadObj(obj);
}

Mesh::~Mesh()
{
  qDebug() << "Mesh " << vertexBuf.ID << " destroyed";
  vertexBuf.Delete();
}

void Mesh::Draw(GLenum type)
{
  vertexBuf.Bind();
//  glDrawElements(type, indicesN, type, 0);
  glDrawArrays(type, 0, verticesN);
  vertexBuf.Unbind();
}

void Mesh::LoadObj(const OBJ& obj)
{
  qDebug() << "Loading obj >> Vertex array ID:" << vertexBuf.ID;
  vertexBuf.Bind();
  std::vector<VertexData> vData = reassembleVertexArray(obj.vertices, obj.faces);
  verticesN = vData.size();
  for (auto &face : obj.faces)
    indicesN += face.indices.size();
  VBO VBO1(vData);
  vertexBuf.LinkAttrib(VBO1, 0, 3, GL_FLOAT, sizeof(VertexData), (void*)0);
  vertexBuf.Unbind();
  VBO1.Unbind();
}
