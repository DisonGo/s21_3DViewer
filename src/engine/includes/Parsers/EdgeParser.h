#ifndef SRC_INCLUDES_PARSER_OBJPARSER_EDGES_H
#define SRC_INCLUDES_PARSER_OBJPARSER_EDGES_H

#include "Parsers/BaseParser.h"
#include "Types/EdgeOBJ.h"

namespace s21 {
class EdgeParser : public s21::BaseParser {
 public:
  OBJParserTypes type = kEdgeParser;
  virtual OBJParserTypes GetType() const override { return type; };
  EdgeOBJ *Parse(string filePath);

 private:
  std::vector<Face> RearangeIndices(const std::vector<Face>& arr);
  void ParseFaceEdges(const string values, Face *faces, size_t &index);
  FaceVertex *ParsePolygonEdges(FaceVertex *vertices, size_t &size);
  s21::TagCounters CountTagsEdges(const string filePath);
};
};  // namespace s21

#endif  //   SRC_INCLUDES_PARSER_OBJPARSER_EDGES_H
