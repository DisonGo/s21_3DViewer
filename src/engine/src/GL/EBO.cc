#include "GL/EBO.h"

#include <QDebug>
namespace s21 {
EBO::EBO(std::vector<Face> indices) { BindIndices(indices); }

GLsizei EBO::GetSize() { return size_; }

void EBO::BindIndices(std::vector<Face> indices) {
  if (ID_ == 0) return;
  Bind();
  std::vector<FaceVertex> new_indices;
  for (auto& face : indices)
    new_indices.insert(new_indices.end(), face.indices.begin(),
                       face.indices.end());
  std::vector<GLuint> ind;
  for (auto& faceVert : new_indices) ind.push_back(faceVert.v_index);
  size_ = ind.size();
  allocated_ = size_ * sizeof(GLuint);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, allocated_, ind.data(), GL_STATIC_DRAW);
}
}  // namespace s21
