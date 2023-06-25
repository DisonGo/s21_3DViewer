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

Engine::Engine(Camera* camera)
{
  initializeOpenGLFunctions();
  this->camera = camera;
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
  Mesh* mesh = new Mesh(obj);
  meshes.push_back(mesh);
}

std::vector<Transform*> Engine::GetMeshTransforms()
{
  size_t size = meshes.size();
  std::vector<Transform*> result;
  for (size_t i = 0; i < size; i++)
    result.push_back(meshes[i]->GetTransformLink());
  return result;
}

std::vector<Mesh *> Engine::GetMeshes()
{
  return meshes;
}

void Engine::drawGeometry(GLenum type)
{
  for (auto mesh : meshes)
    mesh->Draw(type, camera);
}
