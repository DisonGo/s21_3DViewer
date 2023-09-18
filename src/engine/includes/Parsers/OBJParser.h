#ifndef OBJPARSER_H
#define OBJPARSER_H
#include <Logger.h>

#include "Parsers/BaseParser.h"
namespace s21 {
class OBJParser : public BaseParser {
 public:
  OBJParserTypes type = kOBJParser;
  virtual OBJParserTypes GetType() const { return type; };
  vector<OBJ> Parse(string filePath);

 private:
  struct Object {
    std::string name = "Mesh";
    size_t i_start = 0;
    size_t i_end = 0;
    bool operator==(const Object &other) const {
      return name == other.name && i_start == other.i_start &&
             i_end == other.i_end;
    }
    bool IsEmpty() const { return i_end == i_start; }
  };
  void ParseFace(const string values, Face *faces, size_t &index,
                 size_t vertex_index);
  void CenterVertices(vector<Vertex> &vertices, Vertex center);
  void ElevateVerticesToGround(vector<Vertex> &vertices);
  void FetchVertexDataByFaces(const OBJ &source, OBJ &output,
                              std::vector<Face> &faces);
  void NormalizeVertices(vector<Vertex> &vertices, float normalizeSize);
  vector<OBJ> CalculateObjects(OBJ &all_data, vector<Object> objects);
  void GenerateNormals(OBJ &obj);
  TagCounters CountTags(const string filePath);
  Logger logger_{"OBJParser"};
};
}  // namespace s21
#endif  // OBJPARSER_H
