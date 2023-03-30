#include "EBO.h"

EBO::EBO()
{
  initializeOpenGLFunctions();
  glGenBuffers(1, &ID);
}

EBO::EBO(GLuint* indices, GLsizeiptr size)
{
  initializeOpenGLFunctions();
  glGenBuffers(1, &ID);
  BindIndices(indices, size);
}

void EBO::BindIndices(GLuint *indices, GLsizeiptr size)
{
  if (ID == -1) return;
  Bind();
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
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
