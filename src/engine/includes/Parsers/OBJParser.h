#ifndef OBJPARSER_H
#define OBJPARSER_H
#include "Parsers/BaseParser.h"
namespace s21 {
class OBJParser : public BaseParser {
 public:
  OBJParserTypes type = kOBJParser;
  virtual OBJParserTypes GetType() const { return type; };
  vector<OBJ> Parse(string filePath);

 private:
  struct object {
    std::string name = "Mesh";
    size_t i_start = 0;
    size_t i_end = 0;
    bool operator==(const object& other) const{
      return name == other.name && i_start == other.i_start && i_end == other.i_end;
    }
  };
  void ParseFace(const string values, Face *faces, size_t &index);
  void CenterVertices(vector<Vertex> &vertices, Vertex center);
  void ElevateVerticesToGround(vector<Vertex> &vertices);
  void CalculateNegativeIndices(vector<Face> &faces, size_t vertices_max_size);
  void FetchVerticesByFaces(const vector<Vertex>& source, vector<Vertex>& output, vector<Face> &faces);
  void FetchNormalsByFaces(const vector<Normal>& source, vector<Normal>& output, vector<Face> &faces);
  vector<OBJ> CalculateObjects(OBJ& all_data, vector<object> objects);
  TagCounters CountTags(const string filePath);
};
}  // namespace s21
#endif  // OBJPARSER_H
