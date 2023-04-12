#include "engine.h"

#include <QVector2D>
#include <QVector3D>
#include <QRandomGenerator>

//VertexColor getRandRGB() {
//  VertexColor color;
//  color.r = QRandomGenerator::global()->generateDouble();
//  color.g = QRandomGenerator::global()->generateDouble();
//  color.b = QRandomGenerator::global()->generateDouble();
//  return color;
//}

Engine::Engine(Shader *program)
{
  initializeOpenGLFunctions();
  this->program = program;
}

Engine::~Engine()
{
  for (auto mesh : meshes)
    delete mesh;
}

void Engine::importObj(QString fileName)
{
  OBJ obj = ObjParser::Parse(fileName.toStdString());
  indicesN += obj.vertices.size();
  meshes.push_back(new Mesh(obj));
}

void Engine::drawGeometry(GLenum type)
{
  program->Activate();
  for (auto mesh : meshes)
    mesh->Draw(type);
}
