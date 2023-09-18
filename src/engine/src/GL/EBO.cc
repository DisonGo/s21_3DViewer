#include "GL/EBO.h"

#include <QDebug>
namespace s21 {
EBO::EBO(std::vector<Face> indices) { BindIndices(indices); }

GLsizei EBO::GetSize() { return size_; }

void EBO::BindIndices(std::vector<Face> indices) {
  if (ID_ == 0) {
    logger_.Log("ID is 0", Logger::LogLevel::kError);
    return;
  }
  Bind();
  std::vector<FaceVertex> new_indices;
  for (auto& face : indices)
    new_indices.insert(new_indices.end(), face.indices.begin(),
                       face.indices.end());
  std::vector<GLuint> ind;
  for (auto& faceVert : new_indices) ind.push_back(faceVert.v_index);
  size_ = ind.size();
  allocated_ = size_ * sizeof(GLuint);
  auto log = std::string("Allocating ") + std::to_string(size_) +
             " elements with total size of " + std::to_string(allocated_) +
             " bytes";
  logger_.Log(log);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, allocated_, ind.data(), GL_STATIC_DRAW);
}
}  // namespace s21
