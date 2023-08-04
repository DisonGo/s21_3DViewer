#include "Parsers/BaseParser.h"

#include "stdio.h"
using std::isspace;
using std::string;
using std::vector;
namespace s21 {
size_t BaseParser::CountFaceVertices(const char* line) {
  size_t count = 0;
  size_t size = strlen(line);
  for (size_t i = 0; *line && i < size; ++line, ++i) {
    if (*line && !isspace(*line)) {
      count++;
      while (*line && !isspace(*line)) {
        ++line;
        ++i;
      }
    }
  }
  return count;
}

double BaseParser::ParseDigits(char** p) {
  double value = 0;
  while (**p >= '0' && **p <= '9') {
    value = (value * 10.0) + (**p - '0');
    ++(*p);
  }
  return value;
}

double BaseParser::ParseDigits(char** p, int& count) {
  double value = 0;
  while (**p >= '0' && **p <= '9') {
    value = (value * 10.0) + (**p - '0');
    ++count;
    ++(*p);
  }
  return value;
}

double BaseParser::Stod(const char* s) {
  double r = 0.0;
  char* p = (char*)s;
  while (*p && std::isspace(*p)) ++p;
  while (*p && *p != '-' && !std::isdigit(*p)) ++p;

  bool neg = *p == '-';
  if (neg) ++p;
  r = ParseDigits(&p);
  if (*p == '.') {
    double f = 0.0;
    int n = 0;
    ++p;
    f = ParseDigits(&p, n);
    r += f / std::pow(10.0, n);
  }
  if (neg) r = -r;
  return r;
}

Vertex BaseParser::ParseVertex(const string& line) {
  Vertex vert;
  const char* str = line.c_str();
  while (*str && isspace(*str)) ++str;
  sscanf(str, "%f %f %f", &vert.x, &vert.y, &vert.z);
  return vert;
}

TextureCoord BaseParser::ParseTextureCoord(const string& line) {
  TextureCoord textureCoord;
  const char* str = line.c_str();
  while (*str && isspace(*str)) ++str;
  sscanf(str, "%f %f", &textureCoord.u, &textureCoord.v);
  return textureCoord;
}

Normal BaseParser::ParseNormal(const string& line) {
  Normal normal;
  const char* str = line.c_str();
  while (*str && isspace(*str)) ++str;
  sscanf(str, "%f %f %f", &normal.x, &normal.y, &normal.z);
  return normal;
}

FaceVertex* BaseParser::ParsePolygon(const string values, size_t& size,
                                     size_t vertex_index) {
  const char* str = values.c_str();
  size = CountFaceVertices(str);
  FaceVertex* vertices = new FaceVertex[size];

  // Face vertex is object with 3 values 'vertex index' 'texture coordinate
  // index' 'normal index' Face vertex patterns:
  /*
    1/1/1   2/2/2   2/2/2   (All 3 indices)
    1//1    2//2    3//3    (Vertex and normal indices)
    1/1     2/2     3/3     (Vertex and texture indices)
    1       2       3       (Only vertex indices)
  */
  // If any of indices is not present it is set to -1;

  for (size_t i = 0; i < size && *str; i++) {
    FaceVertex& vertex = vertices[i];
    for (int j = 0; j < 3 && *str; j++) {
      int index = Stod(str) - 1;
      if (index < 0) index += vertex_index + 1;
      while (*str && isspace(*str)) ++str;
      while (*str && std::isdigit(*str)) ++str;
      if (j == 0) vertex.v_index = index;
      if (j == 1) vertex.t_index = index;
      if (j == 2) vertex.n_index = index;
      bool isslash = *str == '/';
      if (isslash) ++str;
      if (!isslash) {
        if (j == 0) vertex.t_index = -1;
        if (j != 2) vertex.n_index = -1;
        j = 2;
      }
    }
    while (*str && !isspace(*str)) ++str;
  }
  return vertices;
}
}  // namespace s21
