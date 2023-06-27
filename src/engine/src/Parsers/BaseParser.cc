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
