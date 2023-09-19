#ifndef TEXTURE_H
#define TEXTURE_H

#include "GL/GLObject.h"
#include "Logger.h"
#include "Shaders/Program.h"
namespace s21 {
class Texture : public GLObject {
 public:
  Texture(const std::string& image, GLenum tex_type, GLuint slot, GLenum format,
          GLenum pixel_type);
  void LoadInProgram(Program& program, const std::string& uniform_name);
  void Bind() override { glBindTexture(type_, ID_); };
  void Unbind() override { glBindTexture(type_, 0); };
  void Delete() override { glDeleteTextures(1, &ID_); };
  ~Texture() {
    Unbind();
    Delete();
  };

 protected:
  GLenum type_;
  GLuint unit_;

 private:
  bool CheckImageErrors(int width_img, int height_img);
  const int image_max_size_ = 1024;
  Logger logger_{"Texture"};
};

}  // namespace s21
#endif  // TEXTURE_H