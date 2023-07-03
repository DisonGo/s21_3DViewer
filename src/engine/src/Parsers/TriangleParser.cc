#include "Parsers/TriangleParser.h"

s21::TagCounters s21::TriangleParser::CountTags(const string filePath) {
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
    if (tag == "f") {
      values = line.substr(pos + 1, line.size() - 1);
      size_t faceVerticesCount = CountFaceVertices(values.c_str());
      counter.fC_ += faceVerticesCount - 2;
    }
  }
  free(str);
  fclose(obj_file);
  return counter;
}

void s21::TriangleParser::ParseFace(const string values, TriangleFace* faces,
                                    size_t& index) {
  FaceVertex* vertices = nullptr;
  size_t vCount = 0;
  vertices = ParsePolygon(values, vCount);

  // Polygon contains n of Face vertices
  // Here polygon transforms in (n - 2) triangle faces;
  // Example:
  /*
    Polygon: (1 1 1) (2 2 2) (3 3 3) (4 4 4) (5 5 5)
    Polygon => Triangles:
    T1 (1 1 1) (2 2 2) (3 3 3)
    T2 (1 1 1) (3 3 3) (4 4 4)
    T3 (1 1 1) (4 4 4) (5 5 5)
  */

  for (size_t i = 1; i < vCount - 1; ++i) {
    faces[index] = {vertices[0], vertices[i], vertices[i + 1]};
    ++index;
  }
  delete[] vertices;
}

s21::TriangleOBJ* s21::TriangleParser::Parse(string filePath) {
  FILE* obj_file = NULL;
  obj_file = fopen(filePath.c_str(), "r");
  if (!obj_file) throw std::invalid_argument("Can't open file");
  s21::TriangleOBJ obj;

  // Count total amount of tags in file for memory allocation

  s21::TagCounters tags = CountTags(filePath);  // Подсчет 'v', 'vt', 'f'

  // std::vector memory allocation

  obj.vertices_.reserve(tags.vC_);
  obj.normals_.reserve(tags.vnC_);
  obj.texture_coords_.reserve(tags.vtC_);
  obj.faces_.reserve(tags.fC_);

  // Dynamic arrays memory allocation

  Vertex* vertices = new Vertex[tags.vC_];
  Normal* normals = new Normal[tags.vnC_];
  TextureCoord* textureCoords = new TextureCoord[tags.vtC_];
  TriangleFace* faces = new TriangleFace[tags.fC_];

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
      vertices[counter.vC_] = ParseVertex(values);  // filling_array_vertexes
      counter.vC_++;
    } else if (tag == "vt") {
      textureCoords[counter.vtC_] = ParseTextureCoord(values);
      counter.vtC_++;
    } else if (tag == "vn") {
      normals[counter.vnC_] = ParseNormal(values);
      counter.vnC_++;
    } else if (tag == "f") {
      ParseFace(values, faces, counter.fC_);
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
  return new s21::TriangleOBJ(obj);
}
