#ifndef OPENGL_HELPER_H_
#define OPENGL_HELPER_H_
#define GL_SILENCE_DEPRECATION
#include <QOpenGLFunctions>
#include <QOpenGLExtraFunctions>
#include "parser_types.h"
struct VertexColor {
  GLfloat r;
  GLfloat g;
  GLfloat b;
};
struct VertexData {
  Vertex vertex;
  VertexColor color;
};
#endif // !OPENGL_HELPER_H_
