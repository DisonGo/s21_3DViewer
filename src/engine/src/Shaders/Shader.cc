#include "Shaders/Shader.h"

namespace s21 {
std::string utils::GetFileContent(const std::string& filePath) {
  QFile shader_file(filePath.c_str());
  if (!shader_file.open(QIODevice::ReadOnly)) {
    qDebug() << "Cannot open shader file " << filePath.c_str();
    return "";
  }
  std::string shader_content =
      QString::fromUtf8(shader_file.readAll()).toStdString();
  return shader_content;
}

void Shader::LinkToProgram(GLuint programID) { glAttachShader(programID, ID_); }
bool Shader::CompileSuccessful() {
  int status = 0;
  glGetShaderiv(ID_, GL_COMPILE_STATUS, &status);
  return status == GL_TRUE;
}

void Shader::SetFileName(const std::string& fileName) { fileName_ = fileName; }
void Shader::CheckCompilation() {
  if (!CompileSuccessful()) PrintShaderError();
}
void Shader::PrintShaderError() {
  GLint maxLength = 0;
  glGetShaderiv(ID_, GL_INFO_LOG_LENGTH, &maxLength);
  std::vector<GLchar> errorLog(maxLength);
  glGetShaderInfoLog(ID_, maxLength, &maxLength, &errorLog[0]);
  qDebug() << fileName_.c_str() << ":";
  qDebug() << errorLog.data();
}
}  // namespace s21
