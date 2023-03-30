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
  importObj("C:/gits/3D_Viewer/objects/castle_blender.obj");
//  GLfloat vertices[] = {
//    0, 0, 0,
//    2, 0, 0,
//    1, 2, 0,
//    3, 2, 0
//  };
//  GLuint indices[] = {
//    0, 1, 2,
//    2, 1, 3
//  };
//  GLfloat vertices[] = {
//      -1.0f, -1.0f, -1.0f, // 0
//      -1.0f, -1.0f,  1.0f, // 1
//      -1.0f,  1.0f, -1.0f, // 2
//    -1.0f,  1.0f,  1.0f, // 3
//     1.0f, -1.0f, -1.0f, // 4
//     1.0f, -1.0f,  1.0f, // 5
//     1.0f,  1.0f, -1.0f, // 6
//     1.0f,  1.0f,  1.0f  // 7
//    };
//  GLuint indices[] =
//  {
//    // right
//    0,1,3,
//    3,0,2,

//    // left
//    4,5,6,
//    6,7,4

//    //top
//    8,9,10,
//    10,11,8,

//    //bottom
//    12,13,14,
//    14,15,12,

//    //right
//    16,17,18,
//    18,19,16,

//    //left
//    20,21,22,
//    22,23,20
//  };
//  loadData(vertices, sizeof(vertices) / sizeof(GLfloat), indices, sizeof(indices) / sizeof(GLuint));
}

void GeometryEngine::importObj(QString fileName)
{
  Vertexes verts;
  Indexes inds;
  FILE* obj = NULL;
  obj = fopen(fileName.toStdString().c_str(), "r");
  if (!obj) {
    qDebug() << "file dont open";
    return;
  }
  int result = parse_obj_file(&verts, &inds, obj);
  if (result) {
    qDebug() << "Parser error:" << result;
    return;
  };
  loadData(verts.vertex, verts.point_count, inds.indexes, inds.index_count);
}

void GeometryEngine::loadData(GLfloat *vertices, int vertCount, GLuint* indices, int indCount)
{
  indicesN = indCount;
  verticesN = vertCount;
//  qDebug() << "Vertices";
//  for (int i = 0; i < vertCount; i++)
//    qDebug() << vertices[i];
//  qDebug() << "Indices";
//  for (int i = 0; i < indCount; i++)
//    qDebug() << indices[i];
  vertexBuf.Bind();
  // Transfer vertex data to VBO
  arrayBuf.BindVertices(vertices, sizeof(GLfloat) * vertCount);
  // Transfer index data to EBO
  indexBuf.BindIndices(indices, sizeof(GLuint) * indCount);

  program->Activate();
  int vertexLocation = glGetAttribLocation(program->ID, "aPos");
  vertexBuf.LinkAttrib(arrayBuf, vertexLocation, 3, GL_FLOAT, 0, (void*)0);
  vertexBuf.Unbind();
  arrayBuf.Unbind();
  indexBuf.Unbind();
}

void GeometryEngine::drawCubeGeometry()
{
  vertexBuf.Bind();
}
