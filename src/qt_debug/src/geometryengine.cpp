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
GeometryEngine::GeometryEngine()
  : indexBuf(QOpenGLBuffer::IndexBuffer)
{
  initializeOpenGLFunctions();

  // Generate 2 VBOs
  arrayBuf.create();
  indexBuf.create();

  // Initializes cube geometry and transfers it to VBOs
  initCubeGeometry();
}

GeometryEngine::~GeometryEngine()
{
  arrayBuf.destroy();
  indexBuf.destroy();
}
//! [0]

void GeometryEngine::initCubeGeometry()
{
  VertexData vertices[] = {
    // Vertex data for face 0
    {QVector3D(-1.0f, -1.0f,  1.0f), QVector3D(0.0f,0.0f,1.0f)},  // v0
    {QVector3D( 1.0f, -1.0f,  1.0f), QVector3D(0.0f,0.0f,1.0f)}, // v1
    {QVector3D(-1.0f,  1.0f,  1.0f), QVector3D(0.0f,0.0f,1.0f)},  // v2
    {QVector3D( 1.0f,  1.0f,  1.0f), QVector3D(0.0f,0.0f,1.0f)}, // v3

    // Vertex data for face 1
    {QVector3D( 1.0f, -1.0f,  1.0f), QVector3D(0.0f,0.0f,1.0f)}, // v4
    {QVector3D( 1.0f, -1.0f, -1.0f), QVector3D(0.0f,0.0f,1.0f)}, // v5
    {QVector3D( 1.0f,  1.0f,  1.0f), QVector3D(0.0f,0.0f,1.0f)},  // v6
    {QVector3D( 1.0f,  1.0f, -1.0f), QVector3D(0.0f,0.0f,1.0f)}, // v7

    // Vertex data for face 2
    {QVector3D( 1.0f, -1.0f, -1.0f), QVector3D(0.0f,0.0f,1.0f)}, // v8
    {QVector3D(-1.0f, -1.0f, -1.0f), QVector3D(0.0f,0.0f,1.0f)},  // v9
    {QVector3D( 1.0f,  1.0f, -1.0f), QVector3D(0.0f,0.0f,1.0f)}, // v10
    {QVector3D(-1.0f,  1.0f, -1.0f), QVector3D(0.0f,0.0f,1.0f)},  // v11

    // Vertex data for face 3
    {QVector3D(-1.0f, -1.0f, -1.0f), QVector3D(0.0f,0.0f,1.0f)}, // v12
    {QVector3D(-1.0f, -1.0f,  1.0f), QVector3D(0.0f,0.0f,1.0f)},  // v13
    {QVector3D(-1.0f,  1.0f, -1.0f), QVector3D(0.0f,0.0f,1.0f)}, // v14
    {QVector3D(-1.0f,  1.0f,  1.0f), QVector3D(0.0f,0.0f,1.0f)},  // v15

    // Vertex data for face 4
    {QVector3D(-1.0f, -1.0f, -1.0f), QVector3D(0.0f,0.0f,1.0f)}, // v16
    {QVector3D( 1.0f, -1.0f, -1.0f), QVector3D(0.0f,0.0f,1.0f)}, // v17
    {QVector3D(-1.0f, -1.0f,  1.0f), QVector3D(0.0f,0.0f,1.0f)}, // v18
    {QVector3D( 1.0f, -1.0f,  1.0f), QVector3D(0.0f,0.0f,1.0f)}, // v19

    // Vertex data for face 5
    {QVector3D(-1.0f,  1.0f,  1.0f), QVector3D(0.0f,0.0f,1.0f)}, // v20
    {QVector3D( 1.0f,  1.0f,  1.0f), QVector3D(0.0f,0.0f,1.0f)}, // v21
    {QVector3D(-1.0f,  1.0f, -1.0f), QVector3D(0.0f,0.0f,1.0f)}, // v22
    {QVector3D( 1.0f,  1.0f, -1.0f), QVector3D(0.0f,0.0f,1.0f)}  // v23
  };

  // Indices for drawing cube faces using triangle strips.
  // Triangle strips can be connected by duplicating indices
  // between the strips. If connecting strips have opposite
  // vertex order then last index of the first strip and first
  // index of the second strip needs to be duplicated. If
  // connecting strips have same vertex order then only last
  // index of the first strip needs to be duplicated.
  GLushort indices[] = {
     0,  1,  2,  3,  3,     // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
     4,  4,  5,  6,  7,  7, // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
     8,  8,  9, 10, 11, 11, // Face 2 - triangle strip ( v8,  v9, v10, v11)
    12, 12, 13, 14, 15, 15, // Face 3 - triangle strip (v12, v13, v14, v15)
    16, 16, 17, 18, 19, 19, // Face 4 - triangle strip (v16, v17, v18, v19)
    20, 20, 21, 22, 23      // Face 5 - triangle strip (v20, v21, v22, v23)
  };
  // Transfer vertex data to VBO 0
  arrayBuf.bind();
  arrayBuf.allocate(vertices, sizeof(vertices));

  // Transfer index data to VBO 1
  indexBuf.bind();
  indexBuf.allocate(indices, sizeof(indices));
}

void GeometryEngine::drawCubeGeometry(Shader *program)
{
  arrayBuf.bind();
  indexBuf.bind();

  int vertexLocation = glGetAttribLocation(program->ID, "a_position");
  qDebug() << "Vertex" << vertexLocation;
  glEnableVertexAttribArray(vertexLocation);
  glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), 0);

  int colorLocation = glGetAttribLocation(program->ID, "color");
  qDebug() << "Color" <<  colorLocation;
  glEnableVertexAttribArray(colorLocation);
  glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)sizeof(QVector3D));
  glDrawElements(GL_TRIANGLE_STRIP, 5, GL_UNSIGNED_SHORT, nullptr);
}
