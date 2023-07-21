#ifndef PROGRAM_H
#define PROGRAM_H

#ifndef GL_SILENCE_DEPRECATION
#define GL_SILENCE_DEPRECATION
#endif

#include <QOpenGLExtraFunctions>


namespace s21 {
class Program : protected QOpenGLExtraFunctions {
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
  void UniformMatrix4fv(const char* name, int count, bool normalize,
                        const float* data);
  void UniformBlockBinding(const char* uniform_name, GLuint id);
  GLuint GetUniformBlockIndex(const char* uniform_name);

 private:
  GLuint ID_ = 0;
  void SetProgram(const std::string& vertexFile,
                  const std::string& fragmentFile);
  bool LinkSuccessful();
  void PrintProgramError();
};
}  // namespace s21

#endif  // PROGRAM_H
