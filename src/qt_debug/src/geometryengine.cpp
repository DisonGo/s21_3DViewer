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
  qDebug() <<QString("Old_arr size:%1").arg(size);
  for (auto face : faces)
    for (auto i : face.index)
      if ((i - 1) < size)
        new_arr.push_back({old_arr.at(i - 1), getRandRGB()});
      else
        qDebug() << "Out of range:" << i;
  return new_arr;
}

GeometryEngine::GeometryEngine(Shader *program)
{
  initializeOpenGLFunctions();
  this->program = program;
  initCubeGeometry();
}

GeometryEngine::~GeometryEngine()
{
  vertexBuf.Delete();
}

void GeometryEngine::initCubeGeometry()
{
  importObj("C:/Users/Dison/Downloads/DNA_Infinity.obj");
}

void GeometryEngine::importObj(QString fileName)
{
  int result = parse_obj_file(&scene, fileName.toStdString().c_str());
  if (result) {
    qDebug() << "Parser error:" << result;
    return;
  };
  loadScene(&scene);
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
  vertexBuf.LinkAttrib(VBO1, 0, 3, GL_FLOAT, sizeof(VertexData), (void*)0);
  vertexBuf.LinkAttrib(VBO1, 1, 3, GL_FLOAT, sizeof(VertexData), (void*)sizeof(Vertex));
  vertexBuf.Unbind();
  VBO1.Unbind();
}

void GeometryEngine::drawGeometry(GLenum type)
{
  vertexBuf.Bind();
  glDrawArrays(type, 0, verticesN);
  vertexBuf.Unbind();
}
