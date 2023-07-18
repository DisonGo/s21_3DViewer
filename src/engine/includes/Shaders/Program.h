#ifndef PROGRAM_H
#define PROGRAM_H

#ifndef GL_SILENCE_DEPRECATION
#define GL_SILENCE_DEPRECATION
#endif

#include <QOpenGLFunctions>

#include "Shaders/FragmentShader.h"
#include "Shaders/VertexShader.h"
namespace s21 {
class Program : protected QOpenGLFunctions {
 public:
  
  Program();
  Program(const std::string& vertexFile, const std::string& fragmentFile);
  void Activate();
  void Delete();
  int GetUniform(const std::string& name);
  static Program* Default();
  Program& operator=(Program&&);
  // GL Functions
  void Uniform1i(const char* name, int a);
  void Uniform1f(const char* name, float a);
  void Uniform2f(const char* name, float a, float b);
  void Uniform3f(const char* name, float a, float b, float c);
  void UniformMatrix4fv(const char* name, int count, bool normalize, const float* data);


 private:
  GLuint ID_ = 0;
  void SetProgram(const std::string& vertexFile,
                  const std::string& fragmentFile);
  bool LinkSuccessful();
  void PrintProgramError();
};
}  // namespace s21

#endif  // PROGRAM_H
