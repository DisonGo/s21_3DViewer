#include "VAO.h"
VAO::VAO()
{
  initializeOpenGLFunctions();
	glGenVertexArrays(1, &ID);
}
void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint nComponents, GLenum type, GLsizeiptr stride, void* offset)
{
  if (ID == -1) return;
  VBO.Bind();
  glVertexAttribPointer(layout, nComponents, type, GL_FALSE, stride, offset);
  glEnableVertexAttribArray(layout);
  VBO.Unbind();
}
void VAO::Bind()
{
	glBindVertexArray(ID);
}

void VAO::Unbind()
{
	glBindVertexArray(0);
}

void VAO::Delete()
{
  glDeleteVertexArrays(1, &ID);
}

VAO::~VAO()
{
  if (ID > -1) Delete();
  ID = -1;
}
