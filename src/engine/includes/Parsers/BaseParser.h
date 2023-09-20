#ifndef BASEPARSER_H
#define BASEPARSER_H

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <thread>

#include "Types/Face.h"
#include "Types/Normal.h"
#include "Types/OBJ.h"
#include "Types/TextureCoord.h"
using std::string;
namespace s21 {

struct TagCounters {
  size_t vC = 0, vnC = 0, vtC = 0, fC = 0;
};
enum OBJParserTypes { kBaseParser, kOBJParser };
class BaseParser {
 public:
  OBJParserTypes type = kBaseParser;
  virtual OBJParserTypes GetType() const { return type; };

  size_t CountFaceVertices(const char* line);

  TextureCoord ParseTextureCoord(const string& line);
  Vertex ParseVertex(const string& line);
  Normal ParseNormal(const string& line);
  FaceVertex* ParsePolygon(const string values, size_t& size,
                           TagCounters& counter);

  double Stod(const char* s);
  double ParseDigits(char** p);
  double ParseDigits(char** p, int& count);
  virtual ~BaseParser() = default;
};
}  // namespace s21
#endif  // BASEPARSER_H