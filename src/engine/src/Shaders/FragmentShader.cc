#include "Shaders/FragmentShader.h"
namespace s21 {
void FragmentShader::Compile() {
  auto fileStr = utils::GetFileContent(fileName_);
  const char* fragmentSource = fileStr.c_str();
  if (ID_)  Delete();
  ID_ = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(ID_, 1, &fragmentSource, NULL);
  glCompileShader(ID_);
  CheckCompilation();
}
}  // namespace s21
