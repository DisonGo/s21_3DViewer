#include "GL/Texture.h"

extern "C" {
#include "stb_image.h"
}
namespace s21 {
Texture::Texture(const std::string& image, GLenum tex_type, GLuint slot,
                 GLenum format, GLenum pixel_type)
    : type_(tex_type), unit_(slot) {
  int width_img, height_img, num_of_color_chanels;
  stbi_set_flip_vertically_on_load(true);
  unsigned char* bytes = stbi_load(image.c_str(), &width_img, &height_img,
                                   &num_of_color_chanels, 0);
  if (CheckImageErrors(width_img, height_img)) return;
  glGenTextures(1, &ID_);
  Bind();

  // Configures the type of algorithm that is used to make the image smaller or
  // bigger
  glTexParameteri(tex_type, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
  glTexParameteri(tex_type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  // Configures the way the texture repeats (if it does at all)
  glTexParameteri(tex_type, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(tex_type, GL_TEXTURE_WRAP_T, GL_REPEAT);

  // Assigns the image to the OpenGL Texture object
  glTexImage2D(tex_type, 0, GL_RGBA, width_img, height_img, 0, format,
               pixel_type, bytes);
  glGenerateMipmap(tex_type);
  stbi_image_free(bytes);
  Unbind();
}

void Texture::LoadInProgram(Program& program, const std::string& uniform_name) {
  program.Activate();
  program.Uniform1i(uniform_name, unit_);
}
bool Texture::CheckImageErrors(int width_img, int height_img) {
  bool size_is_negative = width_img <= 0 || height_img <= 0;
  bool size_is_too_large =
      (width_img >= image_max_size_ || height_img >= image_max_size_);
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
}  // namespace s21