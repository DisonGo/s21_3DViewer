#include "ObjParser.h"
#include "Types/Normal.h"
#include "Types/TextureCoord.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#define SHOW_TIMINGS
using std::string;
using std::vector;
using std::isspace;
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
      while (*str && !isspace(*str) && *str != '/') {
        index = index * 10 + (*str - '0');
        ++str;
      }
      index -= 1;
      if (i == 0) {
        faceVertex.vIndex = index;
      } else if (i == 1) {
        faceVertex.tIndex = index;
      } else if (i == 2) {
        faceVertex.nIndex = index;
      }
      if (*str == '/') ++str;
    }

    polygonVertices.push_back(faceVertex);
  }
  return polygonVertices;
}
void ParseFaces(const string& line, OBJ *obj) {
  vector<FaceVertex> polygonVertices = ParsePolygon(line);

  // Transform polygon face to triangle faces
  size_t size = polygonVertices.size();
  for (size_t i = 1; i < size - 1; i++) {
    Face face;
    face.indices.push_back(polygonVertices[0]);
    face.indices.push_back(polygonVertices[i]);
    if (i + 1 < size)
      face.indices.push_back(polygonVertices[i + 1]);
    obj->faces.push_back(face);
  }
}
typedef struct _TagCounters{
  long vC = 0, vnC = 0, vtC = 0, fC = 0;
}TagCounters;
long totalElementsCount = 0;
double totalTime = 0;
TagCounters CountTags(const string filePath) {
  std::ifstream obj_file;
  obj_file.open(filePath, std::ios_base::in);
  if (!obj_file.is_open())
    throw std::invalid_argument("Can't open file");
  TagCounters counter;
  for (string line; getline( obj_file, line );) {
    string tag = line.substr(0, line.find(' '));
    if (tag == "v") counter.vC++;
    if (tag == "vn") counter.vnC++;
    if (tag == "vt") counter.vtC++;
    if (tag == "f") counter.fC++;
  }
  obj_file.close();
  return counter;
}
void OutputTime(clock_t *s, clock_t *f, TagCounters &counter) {
  *f = clock();
  if (*s != 0 && *f != 0) {
    QString tag = "None";
    long count = 0;
    if (counter.vC) tag = "Vertices";
    else if (counter.vnC) tag = "Normals";
    else if (counter.vtC) tag = "TextureCords";
    else if (counter.fC) tag = "Faces";
    if (counter.vC) count = counter.vC;
    else if (counter.vnC) count = counter.vnC;
    else if (counter.vtC) count = counter.vtC;
    else if (counter.fC) count = counter.fC;
    double time = (double)(*f - *s)/(double)CLOCKS_PER_SEC * 1000;
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
OBJ ObjParser::Parse(string filePath)
{

  std::ifstream obj_file;
  obj_file.open(filePath, std::ios_base::in);
  if (!obj_file.is_open())
    throw std::invalid_argument("Can't open file");
  OBJ obj;
  TagCounters counter = CountTags(filePath);
  obj.vertices.reserve(counter.vC);
  obj.normals.reserve(counter.vnC);
  obj.textureCoords.reserve(counter.vtC);
  obj.faces.reserve(counter.fC);
#ifdef SHOW_TIMINGS
  totalElementsCount = 0;
  totalTime = 0;
  counter = {0};
  clock_t start = 0, end = 0;
#endif
  for (string line; getline( obj_file, line );) {
    size_t pos = line.find(' ');
    string tag = line.substr(0, pos);
    string values = line.substr(pos + 1, line.size() - 1);
    if (tag == "v") {
#ifdef SHOW_TIMINGS
      if (counter.vC == 0)
        OutputTime(&start, &end, counter);
      counter.vC++;
#endif
      obj.vertices.push_back(ParseVertex(values));
    } else if (tag == "vn") {
#ifdef SHOW_TIMINGS
      if (counter.vnC == 0)
        OutputTime(&start, &end, counter);
      counter.vnC++;
#endif
      obj.normals.push_back(ParseNormal(values));
    } else if (tag == "vt") {
#ifdef SHOW_TIMINGS
      if (counter.vtC == 0)
        OutputTime(&start, &end, counter);
      counter.vtC++;
#endif
      obj.textureCoords.push_back(ParseTextureCoord(values));
    } else if (tag == "f") {
#ifdef SHOW_TIMINGS
      if (counter.fC == 0)
        OutputTime(&start, &end, counter);
      counter.fC++;
#endif
      ParseFaces(values, &obj);
    }
  }
#ifdef SHOW_TIMINGS
//  for (auto face : obj.faces) {
//      std::ostringstream oss;
//      oss << "f ";
//      for (auto i : face.indices)
//          oss << i.vIndex << "/" << i.tIndex << "/" << i.nIndex << " ";
//      qDebug() << oss.str().c_str();
//  }
  OutputTime(&start, &end, counter);
  qDebug() << "Total lines count:" << totalElementsCount;
  qDebug() << "Total parsing time:" << totalTime << "ms";
#endif
  obj_file.close();
  return obj;
}
