#include "EBO.h"

EBO::EBO()
{
  initializeOpenGLFunctions();
  glGenBuffers(1, &ID);
}

EBO::EBO(std::vector<Face> indices)
{
  initializeOpenGLFunctions();
  glGenBuffers(1, &ID);
  BindIndices(indices);
}

GLsizei EBO::Size()
{
  return size;
}

void EBO::BindIndices(std::vector<Face> indices)
{
  if (ID == -1) return;
  size = indices.size();
  allocated = size * sizeof(Face);
  Bind();
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, allocated, indices.data(), GL_STATIC_DRAW);
}

void EBO::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::Delete()
{
  glDeleteBuffers(1, &ID);
}

EBO::~EBO()
{
  if (ID != -1) Delete();
  ID = -1;
}
