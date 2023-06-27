#ifndef SHADER_H
#define SHADER_H
#define GL_SILENCE_DEPRECATION

#include <QOpenGLFunctions>
#include <string>
class Shader : protected QOpenGLFunctions {
 public:
  enum ShaderType { Vertex = 0, Fragment };
  GLuint ID;
  Shader();
  Shader(const char* vertexFile = "", const char* fragmentFile = "");
  void Activate();
  void Delete();
  static Shader* Default();
  Shader& operator=(Shader&&);

private:
  GLint vertexId = -1;
  GLint fragmentId = -1;

  void SetVertexShader(const char* vertexFile);
  void SetFragmentShader(const char* fragmentFile);
  void setProgram();
  QString getFileContent(const char* fileName);
  const char* vertexFileName;
  const char* fragmentFileName;
  void PrintShaderError(int obj, const char* fileName);
  void Check_compilation(int id, ShaderType type);
  bool CompileSuccessful(int obj);
  bool LinkSuccessful(int obj);
  void PrintProgramError(int obj);
};

#endif  // SHADER_H
