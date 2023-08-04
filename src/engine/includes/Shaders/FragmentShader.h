#ifndef FRAGMENTSHADER_H
#define FRAGMENTSHADER_H
#include "Shaders/Shader.h"

namespace s21 {
class FragmentShader : public Shader {
 public:
  void Compile();
  using Shader::Shader;
  FragmentShader(const std::string& filePath) : Shader() {
    SetFileName(filePath);
    Compile();
  };
};
}  // namespace s21
#endif  // FRAGMENTSHADER_H
