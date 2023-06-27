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

typedef struct {
  size_t vC = 0, vnC = 0, vtC = 0, fC = 0;
} TagCounters;

class BaseParser {
 public:
  double stod(const char* s);
  Vertex ParseVertex(const string& line);
  TextureCoord ParseTextureCoord(const string& line);
  Normal ParseNormal(const string& line);
  virtual BaseOBJ Parse(string filePath) = 0;
  size_t CountFaceVertices(const char *line);
  double parseDigits(char **p);
  double parseDigits(char **p, int &count);
};
}  // namespace s21

#endif  //   SRC_INCLUDES_PARSER_OBJPARSER_BASE_H
