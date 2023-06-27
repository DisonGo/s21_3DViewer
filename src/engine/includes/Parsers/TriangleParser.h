#ifndef SRC_INCLUDES_PARSER_OBJPARSER_TRIANGLE_H
#define SRC_INCLUDES_PARSER_OBJPARSER_TRIANGLE_H

#include "BaseParser.h"
#include "Types/TriangleOBJ.h"

namespace s21 {
class TriangleParser : public s21::BaseParser {
 public:
    BaseOBJ Parse(string filePath) override;
private:
    s21::TagCounters CountTags(const string filePath);
    FaceVertex *ParsePolygon(const string values, size_t &size);
    void ParseFace(const string values, TriangleFace *faces, size_t &index);
};
};  // namespace s21

#endif  //   SRC_INCLUDES_PARSER_OBJPARSER_TRIANGLE_H
