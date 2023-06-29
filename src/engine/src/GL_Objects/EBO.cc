#include "GL/EBO.h"

EBO::EBO(std::vector<Face> indices) { BindIndices(indices); }

GLsizei EBO::GetSize() { return size_; }

void EBO::BindIndices(std::vector<Face> indices) {
  if (ID == (GLuint)-1) return;
  Bind();
  std::vector<FaceVertex> new_indices;
  for (auto& face : indices)
    new_indices.insert(new_indices.end(),face.indices.begin(), face.indices.end());
  size_ = new_indices.size();
  allocated_ = size_ * sizeof(FaceVertex);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, allocated_, new_indices.data(),
               GL_STATIC_DRAW);
}
