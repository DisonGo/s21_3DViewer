// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "geometryengine.h"

#include <QVector2D>
#include <QVector3D>
#include <QRandomGenerator>
VertexColor getRandRGB() {
  VertexColor color;
  color.r = QRandomGenerator::global()->generateDouble();
  color.g = QRandomGenerator::global()->generateDouble();
  color.b = QRandomGenerator::global()->generateDouble();
  return color;
}
template <typename T>
std::vector<T> parseToStdVector(T* arr_x, size_t size) {
  std::vector<T> arr;
  for (size_t i = 0; i < size; i++)
    arr.push_back(arr_x[i]);
  return arr;
}
std::vector<VertexData> reassembleVertexArray(std::vector<Vertex> old_arr, std::vector<Face> faces) {
  std::vector<VertexData> new_arr;
  size_t size = old_arr.size();
  for (auto face : faces)
    for (auto i : face.index)
      if (i < size)
        new_arr.push_back({old_arr.at(i - 1), getRandRGB()});
      else
        qDebug() << "Out of range:" << i;
  return new_arr;
}
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
//  importObj("C:/Users/Dison/Downloads/DNA_Infinity.obj");
    importObj("C:/gits/3D_Viewer/objects/IronMan.obj");
//  importObj("C:/gits/3D_Viewer/objects/castle_blender.obj");
//  std::vector<GLfloat> vertices;
//  std::vector<GLuint> indices;
//  float z = 0;
//  int field_size = 10;
//  int half = field_size / 2;
//  int counter = 0;
//  for (int y = -half; y < half; y++) {
//    for (int x = -half; x < half; x++){
//      vertices.push_back(x);
//      vertices.push_back(y);
//      vertices.push_back(z);
//      indices.push_back(counter);
//      counter++;
//    }
//  }

// loadData(vertices.data(), vertices.size(), indices.data(), indices.size());
}

void GeometryEngine::importObj(QString fileName)
{
  int result = parse_obj_file(&scene, fileName.toStdString().c_str());
  if (result) {
    qDebug() << "Parser error:" << result;
    return;
  };
  loadScene(&scene);
//  loadData(verts.vertex, verts.point_count, inds.indexes, inds.index_count);
}

void GeometryEngine::loadData(GLfloat *vertices, int vertCount, GLuint* indices, int indCount)
{
//  program->Activate();
//  indicesN = indCount;
//  verticesN = vertCount;
//  indic = indices;
//  qDebug() << "Vertices";
////  for (int i = 0; i < vertCount - 2; i += 3)
////    qDebug() << QString("%1 %2 %3").arg(vertices[i]).arg(vertices[i + 1]).arg(vertices[i + 2]);
////  qDebug() << "Indices";
////  for (int i = 0; i < indCount - 2; i += 3)
////    qDebug() << QString("%1 %2 %3").arg(indices[i]).arg(indices[i + 1]).arg(indices[i + 2]);;
//  vertexBuf.Bind();
//  VBO arrayBuf(vertices);
//  EBO indexBuf(indices, sizeof(GLuint) * indCount);
////  qDebug() << QString("arrayBuff size:%1").arg(sizeof(GLfloat) * vertCount);
////  qDebug() << QString("indexBuff size:%1").arg(sizeof(GLuint) * indCount);

//  vertexBuf.LinkAttrib(arrayBuf, 0, 3, GL_FLOAT, sizeof(GLfloat) * 3, (void*)0);
//  vertexBuf.Unbind();
//  arrayBuf.Unbind();
//  indexBuf.Unbind();
}

void GeometryEngine::loadScene(Scene *new_scene)
{
  if (!new_scene) return;
  scene = *new_scene;
  verticesN = scene.vertices_count;

  std::vector<Face> faces;
  for (size_t i = 0; i < scene.objects_count; i++) {
    Object* obj = &scene.objects[i];
    auto new_face_vector = parseToStdVector(obj->faces,obj->num_faces);
    faces.insert(faces.end(), new_face_vector.begin(), new_face_vector.end());
    indicesN += obj->num_faces;
  }

  vertexBuf.Bind();
  std::vector<Vertex> vertices = parseToStdVector(scene.vertices, scene.vertices_count);
  std::vector<VertexData> vData= reassembleVertexArray(vertices, faces);
  verticesN = vData.size();
  VBO VBO1(vData);
//  EBO Index_buffer(faces);
  vertexBuf.LinkAttrib(VBO1, 0, 3, GL_FLOAT, sizeof(VertexData), (void*)0);
  vertexBuf.LinkAttrib(VBO1, 1, 3, GL_FLOAT, sizeof(VertexData), (void*)sizeof(Vertex));
  vertexBuf.Unbind();
  VBO1.Unbind();
//  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void GeometryEngine::drawGeometry(GLenum type)
{
  vertexBuf.Bind();
  if (type == GL_POINTS) {
//    glDrawElements(type, indicesN, GL_UNSIGNED_INT, 0);
    glDrawArrays(type, 0, verticesN);
    vertexBuf.Unbind();
    return;
  }
  glDrawArrays(type, 0, verticesN);
//  glDrawElements(type, indicesN, GL_UNSIGNED_INT, 0);
//  vertexBuf.Unbind();
}
