#include "Shaders/VertexShader.h"
namespace s21 {
void VertexShader::Compile() {
  auto fileStr = utils::GetFileContent(fileName_);
  const char* vertexSource = fileStr.c_str();
  if (ID_) Delete();
  ID_ = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(ID_, 1, &vertexSource, NULL);
  glCompileShader(ID_);
  CheckCompilation();
}
}  // namespace s21
