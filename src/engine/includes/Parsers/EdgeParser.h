#ifndef SRC_INCLUDES_PARSER_OBJPARSER_EDGES_H
#define SRC_INCLUDES_PARSER_OBJPARSER_EDGES_H

#include "Parsers/BaseParser.h"
#include "Types/EdgeOBJ.h"

namespace s21 {
class EdgeParser : s21::BaseParser {
 public:
    BaseOBJ Parse(string filePath) override;
private:
    void ParseFaceEdges(const string values, Face *faces, size_t &index);
    FaceVertex *ParsePolygonEdges(FaceVertex *vertices, size_t &size);
    s21::TagCounters CountTagsEdges(const string filePath);
};
};  // namespace s21

#endif  //   SRC_INCLUDES_PARSER_OBJPARSER_EDGES_H
