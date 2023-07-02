#ifndef VERTEXSHADER_H
#define VERTEXSHADER_H
#include "Shaders/Shader.h"

namespace s21 {
class VertexShader : public Shader {
public:
  void Compile();
  using Shader::Shader;
  VertexShader(const std::string& filePath) : Shader(){
    SetFileName(filePath);
    Compile();
  };
};
}  // namespace s21
#endif  // VERTEXSHADER_H
