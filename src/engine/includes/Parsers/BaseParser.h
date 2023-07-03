#ifndef SRC_INCLUDES_PARSER_OBJPARSER_BASE_H
#define SRC_INCLUDES_PARSER_OBJPARSER_BASE_H

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <thread>

#include "Types/BaseOBJ.h"
#include "Types/Face.h"
#include "Types/Normal.h"
#include "Types/TextureCoord.h"
using std::string;
namespace s21 {

struct TagCounters {
  size_t vC = 0, vnC = 0, vtC = 0, fC = 0;
};
enum OBJParserTypes { kBaseParser, kEdgeParser, kTriangleParser };
class BaseParser {
 public:
  OBJParserTypes type = kBaseParser;
  virtual OBJParserTypes GetType() const { return type; };

  size_t CountFaceVertices(const char* line);

  TextureCoord ParseTextureCoord(const string& line);
  Vertex ParseVertex(const string& line);
  Normal ParseNormal(const string& line);
  FaceVertex* ParsePolygon(const string values, size_t& size);

  double Stod(const char* s);
  double ParseDigits(char** p);
  double ParseDigits(char** p, int& count);
  virtual ~BaseParser() = default;
};
}  // namespace s21

#endif  //   SRC_INCLUDES_PARSER_OBJPARSER_BASE_H
