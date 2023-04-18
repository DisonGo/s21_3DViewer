#include "ObjParser.h"

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <stdexcept>

#include "Types/Normal.h"
#include "Types/TextureCoord.h"
#define SHOW_TIMINGS
using std::isspace;
using std::string;
using std::vector;
Normal ParseNormal(const string& line) {
  Normal normal;
  const char* str = line.c_str();
  while (*str && isspace(*str)) ++str;
  normal.x = atof(str);
  while (*str && !isspace(*str)) ++str;
  while (*str && isspace(*str)) ++str;
  normal.y = atof(str);
  while (*str && !isspace(*str)) ++str;
  normal.z = atof(str);
  return normal;
}

TextureCoord ParseTextureCoord(const string& line) {
  TextureCoord textureCoord;
  const char* str = line.c_str();
  while (*str && isspace(*str)) ++str;
  textureCoord.u = atof(str);
  while (*str && !isspace(*str)) ++str;
  textureCoord.v = atof(str);
  return textureCoord;
}

Vertex ParseVertex(const string& line) {
  Vertex vert;
  const char* str = line.c_str();
  while (*str && isspace(*str)) ++str;
  vert.x = atof(str);
  while (*str && !isspace(*str)) ++str;
  while (*str && isspace(*str)) ++str;
  vert.y = atof(str);
  while (*str && !isspace(*str)) ++str;
  vert.z = atof(str);
  //  qDebug() << vert.x << vert.y << vert.z;
  return vert;
}

size_t CountFaceVertices(const char* line) {
  size_t count = 0;
  for (; *line; ++line) {
    if (*line && !isspace(*line)) {
      count++;
      while (*line && !isspace(*line)) ++line;
    }
  }
  return count;
}

std::pair<FaceVertex*, size_t> ParsePolygon(const string& line) {
  FaceVertex faceVertex;
  const char* str = line.c_str();
  size_t size = CountFaceVertices(str);
  FaceVertex* faceVertices = new FaceVertex[size];
  size_t vertexI = 0;
  while (*str && isspace(*str)) ++str;
  while (*str) {
    while (*str && isspace(*str)) ++str;
    for (int i = 0; i < 3; ++i) {
      int index = 0;
      index = atof(str);
      while (*str && std::isdigit(*str)) ++str;
      index -= 1;
      if (i == 0) {
        faceVertex.vIndex = index;
      } else if (i == 1) {
        faceVertex.tIndex = index;
      } else if (i == 2) {
        faceVertex.nIndex = index;
      }
      if (*str == '/')
        ++str;
      else
        i = 2;
    }

    faceVertices[vertexI++] = faceVertex;
    while (*str && *str == '\n') ++str;
  }
  return {faceVertices, vertexI};
}
void ParseFaces(const string& line, OBJ& obj) {
  std::pair<FaceVertex*, size_t> faceVertexPair = ParsePolygon(line);
  FaceVertex* polygonVertices = faceVertexPair.first;
  size_t size = faceVertexPair.second - 2;


  // Transform polygon face to triangle faces
  for (size_t i = 1, j = 0; j < size; i++, j++)  {
    // CRASH: if size is much bigger then usual polygons (50+) (Heap overflow?)
    Face face;
    FaceVertex triangle[] = {polygonVertices[0], polygonVertices[i], polygonVertices[i + 1]};
    size_t triangleSize = sizeof(triangle) / sizeof(FaceVertex);
    face.indices.assign(triangle, triangle + triangleSize);
    obj.faces.push_back(face);
  }
  delete[] polygonVertices;
}
typedef struct _TagCounters {
  long vC = 0, vnC = 0, vtC = 0, fC = 0;
} TagCounters;
long totalElementsCount = 0;
double totalTime = 0;
TagCounters CountTags(const string filePath) {
  FILE* obj_file = NULL;
  obj_file = fopen(filePath.c_str(), "r");
  if (!obj_file) throw std::invalid_argument("Can't open file");
  size_t linesz = 0;
  char* str = nullptr;
  string line;
  string tag;
  string values;
  TagCounters counter;
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
void OutputTime(clock_t* s, clock_t* f, TagCounters& counter) {
  *f = clock();
  if (*s != 0 && *f != 0) {
    QString tag = "None";
    long count = 0;
    if (counter.vC)
      tag = "Vertices";
    else if (counter.vnC)
      tag = "Normals";
    else if (counter.vtC)
      tag = "TextureCords";
    else if (counter.fC)
      tag = "Faces";
    if (counter.vC)
      count = counter.vC;
    else if (counter.vnC)
      count = counter.vnC;
    else if (counter.vtC)
      count = counter.vtC;
    else if (counter.fC)
      count = counter.fC;
    double time = (double)(*f - *s) / (double)CLOCKS_PER_SEC * 1000;
    qDebug() << "Parsed" << count << tag << "in" << time << "ms";
    totalTime += time;
    totalElementsCount += count;
  }
  counter.vC = 0;
  counter.vnC = 0;
  counter.vtC = 0;
  counter.fC = 0;
  *s = clock();
}
OBJ ObjParser::Parse(string filePath) {
  FILE* obj_file = NULL;
  obj_file = fopen(filePath.c_str(), "r");
  if (!obj_file) throw std::invalid_argument("Can't open file");
  OBJ obj;
  TagCounters tags = CountTags(filePath);
  obj.vertices.reserve(tags.vC);
  obj.normals.reserve(tags.vnC);
  obj.textureCoords.reserve(tags.vtC);
  obj.faces.reserve(tags.fC);
  TagCounters counter;
  size_t linesz = 0;
  char* str = nullptr;
  Vertex* vertices = new Vertex[tags.vC];
  Normal* normals = new Normal[tags.vnC];
  TextureCoord* textureCords = new TextureCoord[tags.vtC];
  string line;
  string tag;
  string values;
  for (; getline(&str, &linesz, obj_file) > 0;) {
    line.assign(str);
    size_t pos = line.find(' ');
    tag = line.substr(0, pos);
    values = line.substr(pos + 1, line.size() - 1);
    if (tag == "v") {
      vertices[counter.vC++] = ParseVertex(values);
    } else if (tag == "vn") {
      normals[counter.vnC++] = ParseNormal(values);
    } else if (tag == "vt") {
      textureCords[counter.vtC++] = ParseTextureCoord(values);
    } else if (tag == "f") {
      ParseFaces(values, obj);
    }
  }
  obj.vertices.insert(obj.vertices.end(), vertices, &vertices[counter.vC - 1]);
  obj.normals.insert(obj.normals.end(), normals, &normals[counter.vnC - 1]);
  obj.textureCoords.insert(obj.textureCoords.end(), textureCords,
                           &textureCords[counter.vtC - 1]);

  delete[] vertices;
  delete[] normals;
  delete[] textureCords;
  free(str);
  fclose(obj_file);
  //  for (auto& face : obj.faces) {
  //    std::ostringstream oss;
  //    oss << "f ";
  //    for (auto i : face.indices)
  //      oss << i.vIndex << "/" << i.tIndex << "/" << i.nIndex << " ";
  //    qDebug() << oss.str().c_str();
  //  }
  return obj;
}
