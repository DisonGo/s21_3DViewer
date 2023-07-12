#ifndef SHADER_H
#define SHADER_H

#ifndef GL_SILENCE_DEPRECATION
#define GL_SILENCE_DEPRECATION
#endif

#include <QFile>
#include <QOpenGLFunctions>

#include "QDebug"

namespace s21 {
namespace utils {
std::string GetFileContent(const std::string& filePath);
}
class Shader : protected QOpenGLFunctions {
 public:
  void LinkToProgram(GLuint programID);
  void Delete() {
    glDeleteShader(ID_);
    ID_ = 0;
  };

 protected:
  Shader() { initializeOpenGLFunctions(); };
  ~Shader() { Delete(); };
  bool CompileSuccessful();
  void SetFileName(const std::string& fileName);
  void CheckCompilation();
  void PrintShaderError();
  GLuint ID_ = 0;
  std::string fileName_{};
};

}  // namespace s21
#endif  // SHADER_H
