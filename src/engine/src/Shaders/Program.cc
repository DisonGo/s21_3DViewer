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
  auto ptr = new Program(":/Shaders/vshader.glsl", ":/Shaders/fshader.glsl");
  ptr->UniformBlockBinding("", 3);
  return ptr;
}

Program& Program::operator=(Program&& obj) {
  this->ID_ = obj.ID_;
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

void Program::UniformBlockBinding(const char *uniform_name, GLuint id)
{
   glUniformBlockBinding(ID_, GetUniformBlockIndex(uniform_name), id);
}

GLuint Program::GetUniformBlockIndex(const char *uniform_name)
{
  return glGetUniformBlockIndex(ID_, uniform_name);
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
