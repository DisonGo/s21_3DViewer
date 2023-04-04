#ifndef SHADER_CLASS_H_
#define SHADER_CLASS_H_
#define GL_SILENCE_DEPRECATION

#include <QOpenGLFunctions>
#include <QObject>
#include <string>
class Shader : public QObject, protected QOpenGLFunctions
{
  Q_OBJECT
public:
  enum ShaderType {
    Vertex = 0,
    Fragment
  };
  GLuint ID;
  explicit Shader(QObject* parent = nullptr);
  Shader(const char* vertexFile = "", const char* fragmentFile = "", QObject* parent = nullptr);
  void Activate();
  void Delete();
  Shader &operator=(Shader&&);
private:
  GLint vertexId = -1;
  GLint fragmentId = -1;

  void SetVertexShader(const char* vertexFile);
  void SetFragmentShader(const char* fragmentFile);
  void setProgram();
  QString getFileContent(const char *fileName);
  const char* vertexFileName;
  const char* fragmentFileName;
  void PrintShaderError(int obj, const char *fileName);
  void Check_compilation(int id, ShaderType type);
  bool CompileSuccessful(int obj);
  bool LinkSuccessful(int obj);
  void PrintProgramError(int obj);
};

#endif
