#ifndef VBO_H
#define VBO_H
#include "GL/GLBuffer.h"
#include "Types/VertexData.h"
class VBO : public GLBuffer {
 public:
  VBO(std::vector<VertexData> vertices);
  void BindVertices(std::vector<VertexData> vertices);
};
#endif  // !VBO_H_
