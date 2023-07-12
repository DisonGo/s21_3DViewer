#ifndef GEOMETRYSHADER_H
#define GEOMETRYSHADER_H

#include "Shaders/Shader.h"
namespace s21 {
class GeometryShader : public Shader {
 public:
  void Compile();
  using Shader::Shader;
  GeometryShader(const std::string& filePath) : Shader() {
    SetFileName(filePath);
    Compile();
  };
};
}  // namespace s21

#endif  // GEOMETRYSHADER_H
