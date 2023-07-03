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
    if (tag == "v") counter.vC_++;
    if (tag == "vn") counter.vnC_++;
    if (tag == "vt") counter.vtC_++;
    if (tag == "f") counter.fC_++;
  }
  free(str);
  fclose(obj_file);
  return counter;
}

FaceVertex* s21::EdgeParser::ParsePolygonEdges(FaceVertex* vertices,
                                               size_t& size) {
  size_t edge_count = size * 2;
  FaceVertex* edges = new FaceVertex[edge_count];
  for (size_t i = 0, j = 0; i < size - 1; ++i) {
    edges[j++] = vertices[i];
    //    edges[j++] = vertices[i + 1];
  }
  return edges;
}

void s21::EdgeParser::ParseFaceEdges(const string values, Face* faces,
                                     size_t& index) {
  FaceVertex* vertices = nullptr;
  FaceVertex* edges = nullptr;
  size_t vCount = 0;
  vertices = ParsePolygon(values, vCount);
  edges = ParsePolygonEdges(vertices, vCount);
  faces[index].indices_.insert(faces[index].indices_.end(), edges,
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

  obj.vertices_.reserve(tags.vC_);
  obj.normals_.reserve(tags.vnC_);
  obj.texture_coords_.reserve(tags.vtC_);
  obj.faces_.reserve(tags.fC_);

  // Dynamic arrays memory allocation

  Vertex* vertices = new Vertex[tags.vC_];
  Normal* normals = new Normal[tags.vnC_];
  TextureCoord* textureCoords = new TextureCoord[tags.vtC_];
  Face* faces = new Face[tags.fC_];

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
      vertices[counter.vC_] = ParseVertex(values);
      counter.vC_++;
    } else if (tag == "vt") {
      textureCoords[counter.vtC_] = ParseTextureCoord(values);
      counter.vtC_++;
    } else if (tag == "vn") {
      normals[counter.vnC_] = ParseNormal(values);
      counter.vnC_++;
    } else if (tag == "f") {
      ParseFaceEdges(values, faces, counter.fC_);
    }
  }

  // Insert values from dynamic arrays to OBJ std::vector`s

  obj.vertices_.insert(obj.vertices_.end(), vertices, vertices + tags.vC_);
  obj.normals_.insert(obj.normals_.end(), normals, normals + tags.vnC_);
  obj.texture_coords_.insert(obj.texture_coords_.end(), textureCoords,
                             textureCoords + tags.vtC_);

  obj.faces_.insert(obj.faces_.end(), faces, faces + tags.fC_);

  // Cleaning

  delete[] vertices;
  delete[] normals;
  delete[] textureCoords;
  delete[] faces;

  if (str) free(str);
  fclose(obj_file);
  return new s21::EdgeOBJ(obj);
}
