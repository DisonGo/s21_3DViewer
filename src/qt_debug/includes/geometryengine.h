// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef GEOMETRYENGINE_H
#define GEOMETRYENGINE_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include "shader.h"
#include "Buffers.h"
extern "C" {
#include "obj_parser.h"
}
class GeometryEngine : protected QOpenGLFunctions
{
public:
  GeometryEngine(Shader *program);
  virtual ~GeometryEngine();

  void drawCubeGeometry();
  int indicesN = 0;
  int verticesN = 0;
private:
  Shader* program = nullptr;
  void initCubeGeometry();
  void importObj(QString fileName);
  void loadData(GLfloat *vertices, int vertCount, GLuint* indices, int indCount);
  VAO vertexBuf;
};

#endif // GEOMETRYENGINE_H
