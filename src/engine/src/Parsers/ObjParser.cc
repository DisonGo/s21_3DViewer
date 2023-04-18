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

vector<FaceVertex> ParsePolygon(const string& line) {
  vector<FaceVertex> polygonVertices;
  FaceVertex faceVertex;
  const char* str = line.c_str();
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

    polygonVertices.push_back(faceVertex);
    while(*str && *str == '\n') ++str;
  }
  return polygonVertices;
}
void ParseFaces(const string& line, OBJ* obj) {
  vector<FaceVertex> polygonVertices = ParsePolygon(line);

  // Transform polygon face to triangle faces
  size_t size = polygonVertices.size();
  for (size_t i = 1; i < size - 1; i++) {
    Face face;
    face.indices.push_back(polygonVertices[0]);
    face.indices.push_back(polygonVertices[i]);
    if (i + 1 < size) face.indices.push_back(polygonVertices[i + 1]);
    obj->faces.push_back(face);
  }
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
  TagCounters counter;
  for (; getline(&str, &linesz, obj_file) > 0;) {
    line.assign(str);
    tag.assign(line.substr(0, line.find(' ')));
    if (tag == "v") counter.vC++;
    if (tag == "vn") counter.vnC++;
    if (tag == "vt") counter.vtC++;
    if (tag == "f") counter.fC++;
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
  string line;
  Vertex* vertices = new Vertex[tags.vC];
  Normal* normals = new Normal[tags.vnC];
  TextureCoord* textureCords = new TextureCoord[tags.vtC];
  // Face* faces = new Face[tags.fC];

  for (; getline(&str, &linesz, obj_file) > 0;) {
    line.assign(str);
    size_t pos = line.find(' ');
    string tag = line.substr(0, pos);
    string values = line.substr(pos + 1, line.size() - 1);
    if (tag == "v") {
      vertices[counter.vC++] = ParseVertex(values);
    } else if (tag == "vn") {
      normals[counter.vnC++] = ParseNormal(values);
    } else if (tag == "vt") {
      textureCords[counter.vtC++] = ParseTextureCoord(values);
    } else if (tag == "f") {
      ParseFaces(values, &obj);
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
