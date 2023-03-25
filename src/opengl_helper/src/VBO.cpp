#include "VBO.h"
VBO::VBO()
{
  initializeOpenGLFunctions();
  glGenBuffers(1, &ID);
}

VBO::VBO(GLfloat* vertices, GLsizeiptr size)
{
  initializeOpenGLFunctions();
	glGenBuffers(1, &ID);
  BindVertices(vertices, size);
}

void VBO::BindVertices(GLfloat *vertices, GLsizeiptr size)
{
  if (ID == -1) return;
  Bind();
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
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
