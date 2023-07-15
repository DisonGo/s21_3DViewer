#ifndef OBJPARSER_H
#define OBJPARSER_H
#include "Parsers/BaseParser.h"
namespace s21 {
class OBJParser : public BaseParser {
 public:
  OBJParserTypes type = kOBJParser;
  virtual OBJParserTypes GetType() const { return type; };
  OBJ Parse(string filePath);

 private:
  void ParseFace(const string values, Face *faces, size_t &index);
  void CenterVertices(vector<Vertex> &vertices, Vertex center);
  void ElevateVerticesToGround(vector<Vertex> &vertices);
  void CalculateNegativeIndices(vector<Face> &faces, size_t vertices_max_size);
  TagCounters CountTags(const string filePath);
};
}  // namespace s21
#endif  // OBJPARSER_H
