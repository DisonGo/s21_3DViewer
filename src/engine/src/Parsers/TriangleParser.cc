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
    if (tag == "v") counter.vC++;
    if (tag == "vn") counter.vnC++;
    if (tag == "vt") counter.vtC++;
    if (tag == "f") {
      values = line.substr(pos + 1, line.size() - 1);
      size_t faceVerticesCount = CountFaceVertices(values.c_str());
      counter.fC += faceVerticesCount - 2;
    }
  }
  free(str);
  fclose(obj_file);
  return counter;
}

FaceVertex* s21::TriangleParser::ParsePolygon(const string values, size_t& size) {
  const char* str = values.c_str();
  size = CountFaceVertices(str);
  FaceVertex* vertices = new FaceVertex[size];

  // Face vertex is object with 3 values 'vertex index' 'texture coordinate
  // index' 'normal index' Face vertex patterns:
  /*
    1/1/1   2/2/2   2/2/2   (All 3 indices)
    1//1    2//2    3//3    (Vertex and normal indices)
    1/1     2/2     3/3     (Vertex and texture indices)
    1       2       3       (Only vertex indices)
  */
  // If any of indices is not present it is set to -1;

  for (size_t i = 0; i < size && *str; i++) {
    FaceVertex& vertex = vertices[i];
    for (int j = 0; j < 3 && *str; j++) {
      unsigned index = stod(str) - 1;
      while (*str && isspace(*str)) ++str;
      while (*str && std::isdigit(*str)) ++str;
      if (j == 0) vertex.vIndex = index;
      if (j == 1) vertex.tIndex = index;
      if (j == 2) vertex.nIndex = index;
      bool isslash = *str == '/';
      if (isslash) ++str;
      if (!isslash) {
        if (j == 0) vertex.tIndex = -1;
        if (j != 2) vertex.nIndex = -1;
        j = 2;
      }
    }
    while (*str && !isspace(*str)) ++str;
  }
  return vertices;
}

void s21::TriangleParser::ParseFace(const string values, TriangleFace* faces, size_t& index) {
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

s21::BaseOBJ s21::TriangleParser::Parse(string filePath) {
  FILE* obj_file = NULL;
  obj_file = fopen(filePath.c_str(), "r");
  if (!obj_file) throw std::invalid_argument("Can't open file");
  s21::TriangleOBJ obj;

  // Count total amount of tags in file for memory allocation

  s21::TagCounters tags = CountTags(filePath);  // Подсчет 'v', 'vt', 'f'

  // std::vector memory allocation

  obj.vertices.reserve(tags.vC);
  obj.normals.reserve(tags.vnC);
  obj.textureCoords.reserve(tags.vtC);
  obj.faces.reserve(tags.fC);

  // Dynamic arrays memory allocation

  Vertex* vertices = new Vertex[tags.vC];
  Normal* normals = new Normal[tags.vnC];
  TextureCoord* textureCoords = new TextureCoord[tags.vtC];
  TriangleFace* faces = new TriangleFace[tags.fC];

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
      vertices[counter.vC] = ParseVertex(values);  // filling_array_vertexes
      counter.vC++;
    } else if (tag == "vt") {
      textureCoords[counter.vtC] = ParseTextureCoord(values);
      counter.vtC++;
    } else if (tag == "vn") {
      normals[counter.vnC] = ParseNormal(values);
      counter.vnC++;
    } else if (tag == "f") {
      ParseFace(values, faces, counter.fC);
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
  return obj;
}
