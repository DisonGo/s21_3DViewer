#ifndef SRC_INCLUDES_PARSER_OBJPARSER_TRIANGLE_H
#define SRC_INCLUDES_PARSER_OBJPARSER_TRIANGLE_H

#include "BaseParser.h"
#include "Types/TriangleOBJ.h"

namespace s21 {
class TriangleParser : public s21::BaseParser {
 public:
  OBJParserTypes type = kTriangleParser;
  virtual OBJParserTypes GetType() const override { return type; };
  TriangleOBJ *Parse(string filePath);

 private:
  s21::TagCounters CountTags(const string filePath);
  void ParseFace(const string values, TriangleFace *faces, size_t &index);
};
};  // namespace s21

#endif  //   SRC_INCLUDES_PARSER_OBJPARSER_TRIANGLE_H
