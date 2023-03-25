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
  //  GLfloat vertices[] = {
//    // Vertex data for face 0
//    -1.0f, -1.0f,  1.0f,  // v0
//     1.0f, -1.0f,  1.0f, // v1
//    -1.0f,  1.0f,  1.0f,  // v2
//     1.0f,  1.0f,  1.0f, // v3

//    // Vertex data for face 1
//     1.0f, -1.0f,  1.0f, // v4
//     1.0f, -1.0f, -1.0f, // v5
//     1.0f,  1.0f,  1.0f,  // v6
//     1.0f,  1.0f, -1.0f, // v7

//    // Vertex data for face 2
//     1.0f, -1.0f, -1.0f, // v8
//    -1.0f, -1.0f, -1.0f,  // v9
//     1.0f,  1.0f, -1.0f, // v10
//    -1.0f,  1.0f, -1.0f,  // v11

//    // Vertex data for face 3
//    -1.0f, -1.0f, -1.0f, // v12
//    -1.0f, -1.0f,  1.0f,  // v13
//    -1.0f,  1.0f, -1.0f, // v14
//    -1.0f,  1.0f,  1.0f,  // v15

//    // Vertex data for face 4
//    -1.0f, -1.0f, -1.0f, // v16
//     1.0f, -1.0f, -1.0f, // v17
//    -1.0f, -1.0f,  1.0f, // v18
//     1.0f, -1.0f,  1.0f, // v19

//    // Vertex data for face 5
//    -1.0f,  1.0f,  1.0f, // v20
//     1.0f,  1.0f,  1.0f, // v21
//    -1.0f,  1.0f, -1.0f, // v22
//     1.0f,  1.0f, -1.0f  // v23
//  };
//  GLuint indices[] = {
//     0,  1,  2,  3,  3,     // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
//     4,  4,  5,  6,  7,  7, // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
//     8,  8,  9, 10, 11, 11, // Face 2 - triangle strip ( v8,  v9, v10, v11)
//    12, 12, 13, 14, 15, 15, // Face 3 - triangle strip (v12, v13, v14, v15)
//    16, 16, 17, 18, 19, 19, // Face 4 - triangle strip (v16, v17, v18, v19)
//    20, 20, 21, 22, 23      // Face 5 - triangle strip (v20, v21, v22, v23)
//  };
  GLfloat vertices[] =
  { //     COORDINATES
    -0.5f, 0.0f,  0.5f,
    -0.5f, 0.0f, -0.5f,
     0.5f, 0.0f, -0.5f,
     0.5f, 0.0f,  0.5f,
     0.0f, 0.8f,  0.0f,
  };

  // Indices for vertices order
  GLuint indices[] =
  {
    0, 1, 2,
    0, 2, 3,
    0, 1, 4,
    1, 2, 4,
    2, 3, 4,
    3, 0, 4
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
