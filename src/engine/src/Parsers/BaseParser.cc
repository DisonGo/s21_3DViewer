#include "Parsers/BaseParser.h"

using std::isspace;
using std::string;
using std::vector;
size_t s21::BaseParser::CountFaceVertices(const char* line) {
  size_t count = 0;
  for (; *line; ++line) {
    if (*line && !isspace(*line)) {
      count++;
      while (*line && !isspace(*line)) ++line;
    }
  }
  return count;
}

double s21::BaseParser::parseDigits(char** p) {
  double value = 0;
  while (**p >= '0' && **p <= '9') {
    value = (value * 10.0) + (**p - '0');
    ++(*p);
  }
  return value;
}

double s21::BaseParser::parseDigits(char** p, int& count) {
  double value = 0;
  while (**p >= '0' && **p <= '9') {
    value = (value * 10.0) + (**p - '0');
    ++count;
    ++(*p);
  }
  return value;
}

double s21::BaseParser::stod(const char* s) {
  double r = 0.0;
  char* p = (char*)s;
  while (*p && std::isspace(*p)) ++p;
  while (*p && *p != '-' && !std::isdigit(*p)) ++p;

  bool neg = *p == '-';
  if (neg) ++p;
  r = parseDigits(&p);
  if (*p == '.') {
    double f = 0.0;
    int n = 0;
    ++p;
    f = parseDigits(&p, n);
    r += f / std::pow(10.0, n);
  }
  if (neg) r = -r;
  return r;
}

Vertex s21::BaseParser::ParseVertex(const string& line) {
  Vertex vert;
  const char* str = line.c_str();
  while (*str && isspace(*str)) ++str;
  vert.x = stod(str);
  while (*str && !isspace(*str)) ++str;
  while (*str && isspace(*str)) ++str;
  vert.y = stod(str);
  while (*str && !isspace(*str)) ++str;
  vert.z = stod(str);
  return vert;
}

TextureCoord s21::BaseParser::ParseTextureCoord(const string& line) {
  TextureCoord textureCoord;
  const char* str = line.c_str();
  while (*str && isspace(*str)) ++str;
  textureCoord.u = stod(str);
  while (*str && !isspace(*str)) ++str;
  textureCoord.v = stod(str);
  return textureCoord;
}

Normal s21::BaseParser::ParseNormal(const string& line) {
  Normal normal;
  const char* str = line.c_str();
  while (*str && isspace(*str)) ++str;
  normal.x = stod(str);
  while (*str && !isspace(*str)) ++str;
  while (*str && isspace(*str)) ++str;
  normal.y = stod(str);
  while (*str && !isspace(*str)) ++str;
  normal.z = stod(str);
  return normal;
}

FaceVertex* s21::BaseParser::ParsePolygon(const string values, size_t& size) {
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
      unsigned index = stod(str) - 1;
      while (*str && isspace(*str)) ++str;
      while (*str && std::isdigit(*str)) ++str;
      if (j == 0) vertex.vIndex = index;
      if (j == 1) vertex.tIndex = index;
      if (j == 2) vertex.nIndex = index;
      bool isslash = *str == '/';
      if (isslash) ++str;
      if (!isslash) {
        if (j == 0) vertex.tIndex = -1;
        if (j != 2) vertex.nIndex = -1;
        j = 2;
      }
    }
    while (*str && !isspace(*str)) ++str;
  }
  return vertices;
}