#ifndef MESH_H
#define MESH_H
#include <QOpenGLFunctions>
#include "VAO.h"
#include "Types/OBJ.h"
#include "shader.h"
class Mesh : protected QOpenGLFunctions
{
public:
  Mesh();
  Mesh(OBJ obj);
  ~Mesh();
  void Draw(GLenum type);
  void LoadObj(const OBJ& obj);
private:
  int verticesN = 0;
  int indicesN = 0;
  VAO vertexBuf;
};

#endif // MESH_H
