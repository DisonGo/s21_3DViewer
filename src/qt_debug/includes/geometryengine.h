// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef GEOMETRYENGINE_H
#define GEOMETRYENGINE_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include "shader.h"
#include "Buffers.h"

class GeometryEngine : protected QOpenGLFunctions
{
public:
  GeometryEngine(Shader *program);
  virtual ~GeometryEngine();

  void drawCubeGeometry();
  int indiciesN = 0;

private:
  Shader* program = nullptr;
  void initCubeGeometry();
  VAO vertexBuf;
  VBO arrayBuf;
  EBO indexBuf;
};

#endif // GEOMETRYENGINE_H
