#include "Shaders/Program.h"

#include <QFile>

#include "QDebug"

Program::Program() {
  initializeOpenGLFunctions();
  ID_ = -1;
}

Program::Program(const std::string& vertexFile,
                 const std::string& fragmentFile) {
  initializeOpenGLFunctions();
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

Program& Program::operator=(Program&& obj) {
  this->ID_ = obj.ID_;
  return *this;
}

void Program::SetProgram(const std::string& vertexFile,
                         const std::string& fragmentFile) {
  ID_ = glCreateProgram();
  s21::VertexShader vertexShader(vertexFile);
  s21::FragmentShader fragmentShader(fragmentFile);
  vertexShader.LinkToProgram(ID_);
  fragmentShader.LinkToProgram(ID_);
  glLinkProgram(ID_);
  if (!LinkSuccessful()) {
    qDebug() << "Program linking failed";
    PrintProgramError();
  }
}
