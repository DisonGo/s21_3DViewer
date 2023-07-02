#include "Shaders/Program.h"

#include <QFile>

#include "QDebug"

Program::Program() {
  initializeOpenGLFunctions();
  ID = -1;
}

Program::Program(const std::string& vertexFile, const std::string& fragmentFile) {
  initializeOpenGLFunctions();
  SetProgram(vertexFile, fragmentFile);
}
bool Program::LinkSuccessful() {
  int status;
  glGetProgramiv(ID, GL_LINK_STATUS, &status);
  return status == GL_TRUE;
}

void Program::PrintProgramError() {
  GLint maxLength = 0;
  glGetProgramiv(ID, GL_INFO_LOG_LENGTH, &maxLength);
  std::vector<GLchar> errorLog(maxLength);
  glGetProgramInfoLog(ID, maxLength, &maxLength, &errorLog[0]);
  qDebug() << "Program id:" << ID;
  qDebug() << errorLog.data();
}
void Program::Activate() { glUseProgram(ID); }
void Program::Delete() { glDeleteProgram(ID); }

int Program::GetUniform(const std::string &name)
{
  return glGetUniformLocation(ID, name.c_str());
}

Program* Program::Default() {
  return new Program(":/Shaders/vshader.glsl", ":/Shaders/fshader.glsl");
}

Program& Program::operator=(Program&& obj) {
  this->ID = obj.ID;
  return *this;
}

void Program::SetProgram(const std::string& vertexFile, const std::string& fragmentFile) {
  ID = glCreateProgram();
  s21::VertexShader vertexShader(vertexFile);
  s21::FragmentShader fragmentShader(fragmentFile);
  vertexShader.LinkToProgram(ID);
  fragmentShader.LinkToProgram(ID);
  glLinkProgram(ID);
  if (!LinkSuccessful()) {
    qDebug() << "Program linking failed";
    PrintProgramError();
  }
}
