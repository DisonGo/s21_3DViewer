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
  vertexBuf.Delete();
}
//! [0]

void GeometryEngine::initCubeGeometry()
{
 importObj("/Users/evverenn/Desktop/Projects/Junk/3D_Viewer/objects/eyeball.obj");
//   GLfloat vertices[] =
//   { //     COORDINATES     /        COLORS      /   TexCoord  //
//     -0.529345, 0.050624, 1.896416,
//     -0.530972, 0.025354, 1.896426,
//     -0.458017, 0.043585, 1.913417,
//     -0.526011, 0.075726, 1.896467,
//     -0.594847, 0.057089, 1.878659,
//     -0.596951, 0.028579, 1.878642,
//     -0.458668, 0.021865, 1.913505,
//     -0.454418, 0.065015, 1.913539,
//     -0.591349, 0.085462, 1.878687,
//     -0.509594, 0.149927, 1.896576,
//     -0.516119, 0.125460, 1.896547,
//     -0.441012, 0.129081, 1.913554,
//     -0.501427, 0.173896, 1.896665,
//     -0.572572, 0.169074, 1.878839,
//     -0.580198, 0.141522, 1.878777,
//     -0.445887, 0.107905, 1.913608,
//     -0.433301, 0.149397, 1.913710,
//     -0.563607, 0.196220, 1.878911,
//     -0.470849, 0.243467, 1.896889,
//     -0.482023, 0.220744, 1.896822,
//     -0.407654, 0.209616, 1.913824,
//     -0.458163, 0.265382, 1.897015,
//     -0.528880, 0.274560, 1.879192,
//     -0.541734, 0.249026, 1.879088,
//     -0.416567, 0.189799, 1.913846,
//     -0.396129, 0.228037, 1.914011
//   };

//  // Indices for vertices order
//  GLuint indices[] =
//  {
//    1, 5, 6, 2,
//    1, 2, 7, 3
//  };
// loadData(vertices, sizeof(vertices) / sizeof(GLfloat), indices, sizeof(indices) / sizeof(GLuint));
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
//  program->Activate();
  indicesN = indCount;
  verticesN = vertCount;
  qDebug() << "Vertices";
//  for (int i = 0; i < vertCount - 2; i += 3)
//    qDebug() << QString("%1 %2 %3").arg(vertices[i]).arg(vertices[i + 1]).arg(vertices[i + 2]);
//  qDebug() << "Indices";
//  for (int i = 0; i < indCount - 2; i += 3)
//    qDebug() << QString("%1 %2 %3").arg(indices[i]).arg(indices[i + 1]).arg(indices[i + 2]);;
  vertexBuf.Bind();
  VBO arrayBuf(vertices, sizeof(GLfloat) * vertCount);
  EBO indexBuf(indices, sizeof(GLuint) * indCount);
//  qDebug() << QString("arrayBuff size:%1").arg(sizeof(GLfloat) * vertCount);
//  qDebug() << QString("indexBuff size:%1").arg(sizeof(GLuint) * indCount);

  vertexBuf.LinkAttrib(arrayBuf, 0, 3, GL_FLOAT, sizeof(GLfloat) * 3, (void*)0);
  vertexBuf.Unbind();
  arrayBuf.Unbind();
  indexBuf.Unbind();
}

void GeometryEngine::drawCubeGeometry()
{
  vertexBuf.Bind();
}
