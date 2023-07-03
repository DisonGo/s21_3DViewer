#ifndef PROGRAM_H
#define PROGRAM_H

#ifndef GL_SILENCE_DEPRECATION
#define GL_SILENCE_DEPRECATION
#endif

#include <QOpenGLFunctions>

#include "Shaders/FragmentShader.h"
#include "Shaders/VertexShader.h"
class Program : protected QOpenGLFunctions {
 public:
  Program();
  Program(const std::string& vertexFile = "",
          const std::string& fragmentFile = "");
  void Activate();
  void Delete();
  int GetUniform(const std::string& name);
  static Program* Default();
  Program& operator=(Program&&);

 private:
  GLuint ID_ = 0;
  void SetProgram(const std::string& vertexFile = "",
                  const std::string& fragmentFile = "");
  bool LinkSuccessful();
  void PrintProgramError();
};

#endif  // PROGRAM_H
