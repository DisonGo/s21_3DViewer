#include "Mesh.h"
#include "VBO.h"
#include "EBO.h"
std::vector<VertexData> reassembleVertexArray(std::vector<Vertex> old_arr, std::vector<Face> faces) {
  std::vector<VertexData> new_arr;
  size_t size = old_arr.size();
  for (auto &face : faces) {
    for (auto indexTuple : face.indices) {
      GLuint index = indexTuple.vIndex;
      if (index < size)
        new_arr.push_back({old_arr.at(index)});
    }
  }
  return new_arr;
}
Mesh::Mesh()
{
  initializeOpenGLFunctions();
  SetShader(Shader::Default());
  LoadTransform();
}

Mesh::Mesh(OBJ obj)
{
  initializeOpenGLFunctions();
  SetShader(Shader::Default());
  LoadTransform();
  LoadObj(obj);
}

Mesh::Mesh(OBJ obj, Shader *shader)
{
  initializeOpenGLFunctions();
  SetShader(shader);
  LoadTransform();
  LoadObj(obj);
}

Mesh::~Mesh()
{
  qDebug() << "Mesh " << vertexBuf.ID << " destroyed";
  vertexBuf.Delete();
}

void Mesh::Draw(GLenum type, Camera* camera)
{
  if (!shader || !camera) return;
  shader->Activate();
  LoadModelMatrix();
  camera->Matrix(60, 0.001, 1000, *shader, "camMatrix");
  vertexBuf.Bind();
  glDrawArrays(type, 0, verticesN);
  vertexBuf.Unbind();
}

void Mesh::LoadObj(const OBJ& obj)
{
  qDebug() << "Loading obj >> Vertex array ID:" << vertexBuf.ID;
  vertexBuf.Bind();
  std::vector<VertexData> vData = reassembleVertexArray(obj.vertices, obj.faces);
  verticesN = vData.size();
  for (auto &face : obj.faces)
    indicesN += face.indices.size();
  VBO VBO1(vData);
  vertexBuf.LinkAttrib(VBO1, 0, 3, GL_FLOAT, sizeof(VertexData), (void*)0);
  vertexBuf.Unbind();
  VBO1.Unbind();
}

void Mesh::SetTransform(const Transform new_transform)
{
  if (transform == new_transform) return;

  transform = new_transform;

  LoadTransform();
}

void Mesh::SetShader(Shader *shader)
{
  this->shader = shader;
}

Transform* Mesh::GetTransformLink()
{
  return &transform;
}

void Mesh::UpdateTransform()
{
  LoadTransform();
}

void Mesh::LoadModelMatrix()
{
  if (!awaitingLoadInShader) return;
  if (!shader) return;
  int modelLoc = glGetUniformLocation(shader->ID, "model");
  glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (modelTranslate * modelRot * modelScale).data());

  awaitingLoadInShader = false;
}

void Mesh::LoadTransform()
{
  modelTranslate.setToIdentity();
  modelScale.setToIdentity();
  modelRot.setToIdentity();

  modelTranslate.translate(transform.translate);
  modelScale.scale(transform.scale);

  modelRot.rotate(transform.rotation.x(), 1, 0, 0);
  modelRot.rotate(transform.rotation.y(), 0, 1, 0);
  modelRot.rotate(transform.rotation.z(), 0, 0, 1);

  awaitingLoadInShader = true;
}
