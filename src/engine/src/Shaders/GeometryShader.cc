#include "Shaders/GeometryShader.h"
namespace s21 {
void GeometryShader::Compile() {
  auto fileStr = utils::GetFileContent(fileName_);
  const char* geometrySource = fileStr.c_str();
  if (ID_) Delete();
  ID_ = glCreateShader(GL_GEOMETRY_SHADER);
  glShaderSource(ID_, 1, &geometrySource, NULL);
  glCompileShader(ID_);
  CheckCompilation();
}
}  // namespace s21
