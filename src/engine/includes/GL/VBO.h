#ifndef VBO_H
#define VBO_H
#include "GL/GLBuffer.h"
#include "Types/VertexData.h"
class VBO : public GLBuffer {
 public:
  VBO(std::vector<VertexData> vertices);
  // VBO(std::vector<Vertex> vertices);
  // VBO(std::vector<Normal> vertices);
  // VBO(std::vector<Normal> vertices);
  void BindVertices(std::vector<VertexData> vertices);
  GLenum GetType() override { return type; };
  GLenum type = GL_ARRAY_BUFFER;
};
#endif  // VBO_H
