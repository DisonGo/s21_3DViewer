// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "geometryengine.h"

#include <QVector2D>
#include <QVector3D>

struct VertexData
{
  QVector3D position;
  QVector3D color;
};

//! ,QVector3D(1.0f, 0.0f, 0.0f)[0]
GeometryEngine::GeometryEngine(Shader *program)
{
  initializeOpenGLFunctions();
  this->program = program;
  // Initializes cube geometry and transfers it to VBOs
  initCubeGeometry();
}

GeometryEngine::~GeometryEngine()
{
  arrayBuf.Delete();
  indexBuf.Delete();
  vertexBuf.Delete();
}
//! [0]

void GeometryEngine::initCubeGeometry()
{
  GLfloat vertices[] = {
    0,0,1,
    0.894,0,0.447,
    0.276,0.851,0.447,
    -0.724,0.526,0.447,
    -0.724,-0.526,0.447,
    0.276,-0.851,0.447,
    0.724,0.526,-0.447,
    -0.276,0.851,-0.447,
    -0.894,0,-0.447,
    -0.276,-0.851,-0.447,
    0.724,-0.526,-0.447,
    0,0,-1
  };
  GLuint indices[] = {
    1,2,0,
    2,3,0,
    3,4,0,
    4,5,0,
    5,1,0,
    7,6,11,
    8,7,11,
    9,8,11,
    10,9,11,
    6,10,11,
    1,6,2,
    2,7,3,
    3,8,4,
    4,9,5,
    5,10,1,
    7,2,6,
    8,3,7,
    9,4,8,
    10,5,9,
    6,1,10
  };
  indiciesN = sizeof(indices) / sizeof(GLuint);
  vertexBuf.Bind();
  // Transfer vertex data to VBO
  arrayBuf.BindVertices(vertices, sizeof(vertices));
  // Transfer index data to EBO
  indexBuf.BindIndices(indices, sizeof(indices));

  program->Activate();
  int vertexLocation = glGetAttribLocation(program->ID, "aPos");
  vertexBuf.LinkAttrib(arrayBuf, vertexLocation, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
  vertexBuf.Unbind();
  arrayBuf.Unbind();
  indexBuf.Unbind();
}

void GeometryEngine::drawCubeGeometry()
{
  vertexBuf.Bind();
}
