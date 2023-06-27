#include "Shader.h"

#include <QFile>

#include "QDebug"
QString Shader::getFileContent(const char* fileName) {
  QFile shader_file(fileName);
  if (!shader_file.open(QIODevice::ReadOnly)) {
    qDebug() << "Cannot open shader file " << fileName;
    return "";
  }
  QString shader_content = QString::fromUtf8(shader_file.readAll());
  return shader_content;
}

Shader::Shader(QObject* parent) : QObject(parent) {
  initializeOpenGLFunctions();
  ID = -1;
}

Shader::Shader(const char* vertexFile, const char* fragmentFile,
               QObject* parent)
    : QObject(parent) {
  initializeOpenGLFunctions();
  SetVertexShader(vertexFile);
  SetFragmentShader(fragmentFile);
  setProgram();
}
bool Shader::LinkSuccessful(int obj) {
  int status;
  glGetProgramiv(obj, GL_LINK_STATUS, &status);
  return status == GL_TRUE;
}
bool Shader::CompileSuccessful(int obj) {
  int status;
  glGetShaderiv(obj, GL_COMPILE_STATUS, &status);
  return status == GL_TRUE;
}
void Shader::PrintShaderError(int obj, const char* fileName) {
  GLint maxLength = 0;
  glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &maxLength);
  std::vector<GLchar> errorLog(maxLength);
  glGetShaderInfoLog(obj, maxLength, &maxLength, &errorLog[0]);
  qDebug() << fileName << ":";
  qDebug() << errorLog.data();
}
void Shader::PrintProgramError(int obj) {
  GLint maxLength = 0;
  glGetProgramiv(obj, GL_INFO_LOG_LENGTH, &maxLength);
  std::vector<GLchar> errorLog(maxLength);
  glGetProgramInfoLog(obj, maxLength, &maxLength, &errorLog[0]);
  qDebug() << "Program id:" << obj;
  qDebug() << errorLog.data();
}
void Shader::Check_compilation(int id, ShaderType type) {
  const char* fileName = type == Vertex ? vertexFileName : fragmentFileName;
  if (!CompileSuccessful(id)) PrintShaderError(id, fileName);
}
void Shader::Activate() { glUseProgram(ID); }
void Shader::Delete() { glDeleteProgram(ID); }

Shader* Shader::Default() {
  return new Shader(":/Shaders/vshader.glsl", ":/Shaders/fshader.glsl",
                    nullptr);
}

Shader& Shader::operator=(Shader&& obj) {
  this->ID = obj.ID;
  return *this;
}

void Shader::SetVertexShader(const char* vertexFile) {
  vertexFileName = vertexFile;
  std::string vertexCode = getFileContent(vertexFile).toStdString();
  const char* vertexSource = vertexCode.c_str();
  vertexId = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexId, 1, &vertexSource, NULL);
  glCompileShader(vertexId);
  Check_compilation(vertexId, Vertex);
}

void Shader::SetFragmentShader(const char* fragmentFile) {
  fragmentFileName = fragmentFile;
  std::string fragmentCode = getFileContent(fragmentFile).toStdString();
  const char* fragmentSource = fragmentCode.c_str();
  fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentId, 1, &fragmentSource, NULL);
  glCompileShader(fragmentId);
  Check_compilation(fragmentId, Fragment);
}

void Shader::setProgram() {
  if (vertexId == -1 || fragmentId == -1) return;
  ID = glCreateProgram();
  glAttachShader(ID, vertexId);
  glAttachShader(ID, fragmentId);
  glLinkProgram(ID);
  if (!LinkSuccessful(ID)) {
    qDebug() << "Shader linking failed";
    PrintProgramError(ID);
  }
  glDeleteShader(vertexId);
  glDeleteShader(fragmentId);
}
