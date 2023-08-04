#include "Shaders/Program.h"

#include <QFile>

#include "QDebug"
namespace s21 {
Program::Program() { initializeOpenGLFunctions(); }

Program::Program(const std::string& vertexFile, const std::string& fragmentFile)
    : Program() {
  SetProgram(vertexFile, fragmentFile);
}
bool Program::LinkSuccessful() {
  int status;
  glGetProgramiv(ID_, GL_LINK_STATUS, &status);
  return status == GL_TRUE;
}

void Program::PrintProgramError() {
  GLint maxLength = 0;
  glGetProgramiv(ID_, GL_INFO_LOG_LENGTH, &maxLength);
  std::vector<GLchar> errorLog(maxLength);
  glGetProgramInfoLog(ID_, maxLength, &maxLength, &errorLog[0]);
  qDebug() << "Program id:" << ID_;
  qDebug() << errorLog.data();
}
void Program::Activate() { glUseProgram(ID_); }
void Program::Delete() { glDeleteProgram(ID_); }

int Program::GetUniform(const std::string& name) {
  return glGetUniformLocation(ID_, name.c_str());
}

Program* Program::Default() {
  return new Program(":/Shaders/vshader.glsl", ":/Shaders/fshader.glsl");
}

Program& Program::operator=(const Program& other) {
  if (this == &other) return *this;
  CopyProgram(other);
  return *this;
}

Program& Program::operator=(Program&& other) {
  if (this == &other) return *this;
  this->ID_ = other.ID_;
  other.ID_ = 0;
  return *this;
}

void Program::Uniform1i(const char* name, int a) {
  glUniform1i(GetUniform(name), a);
}

void Program::Uniform1f(const char* name, float a) {
  glUniform1f(GetUniform(name), a);
}

void Program::Uniform2f(const char* name, float a, float b) {
  glUniform2f(GetUniform(name), a, b);
}

void Program::Uniform3f(const char* name, float a, float b, float c) {
  glUniform3f(GetUniform(name), a, b, c);
}

void Program::UniformMatrix4fv(const char* name, int count, bool normalize,
                               const float* data) {
  glUniformMatrix4fv(GetUniform(name), count, normalize, data);
}

void Program::CopyProgram(const Program& other) {
  GLsizei binarySize;
  glGetProgramiv(other.ID_, GL_PROGRAM_BINARY_LENGTH, &binarySize);
  std::vector<GLubyte> binaryData(binarySize);
  GLsizei length;
  GLenum format;
  glGetProgramBinary(other.ID_, binarySize, &length, &format,
                     binaryData.data());
  glProgramBinary(ID_, format, binaryData.data(), length);
}

void Program::SetProgram(const std::string& vertexFile,
                         const std::string& fragmentFile) {
  ID_ = glCreateProgram();
  VertexShader vertexShader(vertexFile);
  FragmentShader fragmentShader(fragmentFile);
  vertexShader.LinkToProgram(ID_);
  fragmentShader.LinkToProgram(ID_);
  glLinkProgram(ID_);
  if (!LinkSuccessful()) {
    qDebug() << "Program linking failed";
    PrintProgramError();
  }
}
}  // namespace s21
