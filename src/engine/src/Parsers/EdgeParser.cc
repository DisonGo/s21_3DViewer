#include "Parsers/EdgeParser.h"

s21::TagCounters s21::EdgeParser::CountTagsEdges(const string filePath) {
  FILE* obj_file = NULL;
  obj_file = fopen(filePath.c_str(), "r");
  if (!obj_file) throw std::invalid_argument("Can't open file");
  size_t linesz = 0;
  char* str = nullptr;
  string line;
  string tag;
  string values;
  s21::TagCounters counter;
  for (; getline(&str, &linesz, obj_file) > 0;) {
    line.assign(str);
    size_t pos = line.find(' ');
    tag.assign(line.substr(0, pos));
    if (tag == "v") counter.vC++;
    if (tag == "vn") counter.vnC++;
    if (tag == "vt") counter.vtC++;
    if (tag == "f") counter.fC++;
  }
  free(str);
  fclose(obj_file);
  return counter;
}
FaceVertex* s21::EdgeParser::ParsePolygonEdges(FaceVertex* vertices, size_t& size) {
  size_t edge_count = size * 2;
  FaceVertex* edges = new FaceVertex[edge_count];
  for (size_t i = 0, j = 0; i < size; ++i) {
    edges[j++] = vertices[i];
    edges[j++] = vertices[i + 1];
  }
  return edges;
}

void s21::EdgeParser::ParseFaceEdges(const string values, Face* faces, size_t& index) {
  FaceVertex* vertices = nullptr;
  FaceVertex* edges = nullptr;
  size_t vCount = 0;
  edges = ParsePolygonEdges(vertices, vCount);
  faces[index].indices.insert(faces[index].indices.end(), edges,
                              edges + vCount * 2);
  ++index;
  delete[] vertices;
  delete[] edges;
}

s21::EdgeOBJ* s21::EdgeParser::Parse(string filePath) {
  FILE* obj_file = NULL;
  obj_file = fopen(filePath.c_str(), "r");
  if (!obj_file) throw std::invalid_argument("Can't open file");
  s21::EdgeOBJ obj;

  // Count total amount of tags in file for memory allocation

  s21::TagCounters tags = CountTagsEdges(filePath);

  // std::vector memory allocation

  obj.vertices.reserve(tags.vC);
  obj.normals.reserve(tags.vnC);
  obj.textureCoords.reserve(tags.vtC);
  obj.faces.reserve(tags.fC);

  // Dynamic arrays memory allocation

  Vertex* vertices = new Vertex[tags.vC];
  Normal* normals = new Normal[tags.vnC];
  TextureCoord* textureCoords = new TextureCoord[tags.vtC];
  Face* faces = new Face[tags.fC];

  s21::TagCounters counter;  // Index counter for dynamic arrays
  size_t linesz = 0;
  char* str = nullptr;
  string line;
  string tag;
  string values;

  for (; getline(&str, &linesz, obj_file) > 0;) {
    line.assign(str);

    // Find sub strings of tag and it's values

    size_t pos = line.find(' ');
    tag.assign(line.substr(0, pos));
    values.assign(line.substr(pos + 1, line.size() - 1));

    // Parse and save values depending on tag

    if (tag == "v") {
      vertices[counter.vC] = ParseVertex(values);
      counter.vC++;
    } else if (tag == "vt") {
      textureCoords[counter.vtC] = ParseTextureCoord(values);
      counter.vtC++;
    } else if (tag == "vn") {
      normals[counter.vnC] = ParseNormal(values);
      counter.vnC++;
    } else if (tag == "f") {
      ParseFaceEdges(values, faces, counter.fC);
    }
  }

  // Insert values from dynamic arrays to OBJ std::vector`s

  obj.vertices.insert(obj.vertices.end(), vertices, vertices + tags.vC);
  obj.normals.insert(obj.normals.end(), normals, normals + tags.vnC);
  obj.textureCoords.insert(obj.textureCoords.end(), textureCoords,
                           textureCoords + tags.vtC);

  obj.faces.insert(obj.faces.end(), faces, faces + tags.fC);

  // Cleaning

  delete[] vertices;
  delete[] normals;
  delete[] textureCoords;
  delete[] faces;

  if (str) free(str);
  fclose(obj_file);
  return new s21::EdgeOBJ(obj);
}
