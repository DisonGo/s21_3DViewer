#include "GL/Texture.h"

extern "C" {
// #include "stb_image.h"
#include "SOIL/SOIL.h"
}
namespace s21 {
Texture::Texture(const std::string& image, GLenum tex_type, GLuint slot)
    : type_(tex_type), unit_(slot) {
  unsigned char* bytes = SOIL_load_image(image.c_str(), &img_w_, &img_h_,
                                         &img_col_ch_, SOIL_LOAD_AUTO);

  // if (CheckImageErrors(width_img, height_img)) return;
  ID_ = SOIL_create_OGL_texture(
      bytes, img_w_, img_h_, img_col_ch_, ID_,
      SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y);
  // glGenTextures(1, &ID_);
  // Bind();

  // // Configures the type of algorithm that is used to make the image smaller
  // or
  // // bigger
  glTexParameteri(tex_type, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
  glTexParameteri(tex_type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  // // Configures the way the texture repeats (if it does at all)
  // glTexParameteri(tex_type, GL_TEXTURE_WRAP_S, GL_REPEAT);
  // glTexParameteri(tex_type, GL_TEXTURE_WRAP_T, GL_REPEAT);

  // // Assigns the image to the OpenGL Texture object
  // glTexImage2D(tex_type, 0, GL_RGBA, width_img, height_img, 0, format,
  //              pixel_type, bytes);
  // glGenerateMipmap(tex_type);
  // Unbind();
  SOIL_free_image_data(bytes);
}

void Texture::LoadInProgram(Program& program, const std::string& uniform_name) {
  program.Activate();
  program.Uniform1i(uniform_name, unit_);
}
bool Texture::CheckImageErrors(int width_img, int height_img) {
  bool size_is_negative = width_img <= 0 || height_img <= 0;
  bool size_is_too_large =
      (width_img > image_max_size_ || height_img > image_max_size_);
  bool size_error = size_is_negative || size_is_too_large;

  bool orientation_error = width_img != height_img;

  if (size_error)
    logger_.Log("Bad texture size: " + std::to_string(width_img) + "x" +
                    std::to_string(height_img),
                Logger::LogLevel::kError);
  if (orientation_error)
    logger_.Log("Texture image isn't square", Logger::LogLevel::kError);
  return size_error || orientation_error;
}
void Texture::Copy(const Texture& other) {
  Bind();
  glBindBuffer(other.ID_, GL_READ_BUFFER);
  glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, other.img_w_, other.img_h_,
                   0);
  glBindBuffer(0, GL_READ_BUFFER);
  Unbind();
}
}  // namespace s21