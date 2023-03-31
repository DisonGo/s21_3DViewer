#include "VBO.h"
VBO::VBO()
{
  initializeOpenGLFunctions();
  glGenBuffers(1, &ID);
}

VBO::VBO(std::vector<VertexData> vertices)
{
  initializeOpenGLFunctions();
	glGenBuffers(1, &ID);
  BindVertices(vertices);
}

void VBO::BindVertices(std::vector<VertexData> vertices)
{
  if (ID == -1) return;
  Bind();
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexData), vertices.data(), GL_STATIC_DRAW);
}

void VBO::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete()
{
  glDeleteBuffers(1, &ID);
}

VBO::~VBO()
{

}
