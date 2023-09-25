#ifndef TEXTURE_H
#define TEXTURE_H

#include "GL/GLObject.h"
#include "Logger.h"
#include "Shaders/Program.h"
namespace s21 {
class Texture : public GLObject {
 public:
  Texture() = delete;
  Texture(const Texture& other) { Copy(other); }
  Texture(const std::string& image, GLenum tex_type, GLuint slot, GLenum format,
          GLenum pixel_type);
  Texture& operator=(const Texture& other) { Copy(other); }
  Texture& operator=(Texture&& other) {
    if (this == &other) return *this;
    Delete();
    ID_ = 0;
    std::swap(other.ID_, ID_);
    return *this;
  }
  void LoadInProgram(Program& program, const std::string& uniform_name);
  void Bind() override { glBindTexture(type_, ID_); }
  void Unbind() override { glBindTexture(type_, 0); }
  void Delete() override { glDeleteTextures(1, &ID_); }
  ~Texture() {
    Unbind();
    Delete();
  }

 protected:
  GLenum type_;
  GLuint unit_;

 private:
  int img_w_, img_h_, img_col_ch_;
  void Copy(const Texture& other);
  bool CheckImageErrors(int width_img, int height_img);
  const int image_max_size_ = 1024;
  Logger logger_{"Texture"};
};

}  // namespace s21
#endif  // TEXTURE_H