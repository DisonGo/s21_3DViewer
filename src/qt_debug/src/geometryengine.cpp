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
    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f
  }; // size: 8 * 3 = 24

//  // Scale the vertices to have sides of length 2
//  for (int i = 0; i < 24; i++) {
//      vertices[i] *= 2.0f;
//  }

  // Define the indices of the vertices that make up each face of the cube
  GLuint indices[] = {
      0, 1, 3, 2, // left
      4, 5, 7, 6, // right
      0, 1, 5, 4, // back
      2, 3, 7, 6, // front
      0, 2, 6, 4, // bottom
      1, 3, 7, 5  // top
  }; // size: 6 * 4 = 24
//  GLfloat vertices[] =
//  { //     COORDINATES
//    -0.5f, 0.0f,  0.5f,
//    -0.5f, 0.0f, -0.5f,
//     0.5f, 0.0f, -0.5f,
//     0.5f, 0.0f,  0.5f,
//     0.0f, 0.8f,  0.0f,
//  };

//  // Indices for vertices order
//  GLuint indices[] =
//  {
//    0, 1, 2,
//    0, 2, 3,
//    0, 1, 4,
//    1, 2, 4,
//    2, 3, 4,
//    3, 0, 4
//  };
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
  GLuint indices[] = {
      0, 1, 3, 2, // left
      4, 5, 7, 6, // right
      0, 1, 5, 4, // back
      2, 3, 7, 6, // front
      0, 2, 6, 4, // bottom
      1, 3, 7, 5  // top
  };
  vertexBuf.Bind();
  for (int i = 0; i < 6; i++) {
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, indices + i * 4);
  }
}
