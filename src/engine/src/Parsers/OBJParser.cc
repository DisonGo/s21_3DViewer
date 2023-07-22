#include "Parsers/OBJParser.h"

#include <godison/Vectors.h>
using godison::vectors::Vector3D;
#include "fstream"
namespace s21 {
TagCounters OBJParser::CountTags(const string filePath) {
  std::ifstream file(filePath, std::ios_base::in);
  string line;
  string tag;
  string values;
  TagCounters counter;
  for (; file.good();) {
    std::getline(file, line);
    size_t pos = line.find(' ');
    tag.assign(line.substr(0, pos));
    if (tag == "v") counter.vC++;
    if (tag == "vn") counter.vnC++;
    if (tag == "vt") counter.vtC++;
    if (tag == "f") counter.fC++;
  }
  file.close();
  return counter;
}

void OBJParser::ParseFace(const string values, Face* faces, size_t& index) {
  FaceVertex* vertices = nullptr;
  size_t vCount = 0;
  vertices = ParsePolygon(values, vCount);
  faces[index].indices.insert(faces[index].indices.end(), vertices,
                              vertices + vCount);
  ++index;
  delete[] vertices;
}

void OBJParser::CenterVertices(std::vector<Vertex>& vertices, Vertex center) {
  if (vertices.empty()) return;
  for (auto& vertex : vertices) center += vertex;
  godison::vectors::Vector3D mean(center.x, center.y, center.z);
  mean /= vertices.size();
  center = Vertex(mean.X(), mean.Y(), mean.Z());
  for (auto& vertex : vertices) vertex -= center;
}

void OBJParser::ElevateVerticesToGround(std::vector<Vertex>& vertices) {
  if (vertices.empty()) return;
  float min = vertices.front().y;
  for (auto& vertex : vertices) min = std::min(min, vertex.y);
  if (min >= 0) return;
  min = fabs(min);
  for (auto& vertex : vertices) vertex.y += min;
}

void OBJParser::CalculateNegativeIndices(std::vector<Face>& faces,
                                         size_t vertices_max_size) {
  if (faces.empty()) return;
  for (auto& face : faces)
    for (auto& index : face.indices)
      if (index.v_index < 0) index.v_index += vertices_max_size + 1;
}

void OBJParser::GenerateNormals(OBJ& obj) {
  if (obj.vertices.empty()) return;
  if (obj.normals.size() == obj.vertices.size()) return;
  obj.normals.clear();
  obj.normals = vector<Normal>(obj.vertices.size());
  for (const auto& face : obj.faces) {
    auto indices_count = face.indices.size();
    if (indices_count < 3) {
      // either a point or a line -> no well-defined normal vector
      for (size_t i = 0; i < indices_count; ++i)
        obj.normals[face.indices[i].v_index] = Normal();
      continue;
    }

    const Vertex& pV1_ = (obj.vertices[face.indices[0].v_index]);
    const Vertex& pV2_ = (obj.vertices[face.indices[1].v_index]);
    const Vertex& pV3_ =
        (obj.vertices[face.indices[face.indices.size() - 1].v_index]);

    const Vector3D pV1(pV1_.x, pV1_.y, pV1_.z);
    const Vector3D pV2(pV2_.x, pV2_.y, pV2_.z);
    const Vector3D pV3(pV3_.x, pV3_.y, pV3_.z);

    const Vector3D vNor =
        (((Vector3D)(pV2 - pV1)).CrossProduct(pV3 - pV1)).Normalized();

    for (const auto& index_bundle : face.indices)
      obj.normals[index_bundle.v_index] = {vNor.X(), vNor.Y(), vNor.Z()};
  }
}

OBJ OBJParser::Parse(string filePath) {
  std::ifstream file(filePath, std::ios_base::in);
  OBJ obj;

  // Count total amount of tags in file for memory allocation

  TagCounters tags = CountTags(filePath);

  // std::vector memory allocation

  obj.vertices.reserve(tags.vC);
  obj.normals.reserve(tags.vnC);
  obj.texture_coords.reserve(tags.vtC);
  obj.faces.reserve(tags.fC);

  // Dynamic arrays memory allocation

  Vertex* vertices = new Vertex[tags.vC];
  Normal* normals = new Normal[tags.vnC];
  TextureCoord* textureCoords = new TextureCoord[tags.vtC];
  Face* faces = new Face[tags.fC];

  TagCounters counter;  // Index counter for dynamic arrays
  string line;
  string tag;
  string values;

  for (; file.good();) {
    // Find sub strings of tag and it's values
    std::getline(file, line);
    size_t pos = line.find(' ');
    tag.assign(line.substr(0, pos));
    values.assign(line.substr(pos + 1, line.size() - 1));
    //    qDebug() << QString(values.c_str());

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
      ParseFace(values, faces, counter.fC);
    }
  }

  // Insert values from dynamic arrays to OBJ std::vector`s

  obj.vertices.insert(obj.vertices.end(), vertices, vertices + tags.vC);
  obj.normals.insert(obj.normals.end(), normals, normals + tags.vnC);
  obj.texture_coords.insert(obj.texture_coords.end(), textureCoords,
                            textureCoords + tags.vtC);
  obj.faces.insert(obj.faces.end(), faces, faces + tags.fC);
  CenterVertices(obj.vertices, {0, 0, 0});
  ElevateVerticesToGround(obj.vertices);

  CalculateNegativeIndices(obj.faces, obj.vertices.size());
  GenerateNormals(obj);

  //  for (auto& vert : obj.vertices)
  //    std::cout << vert << "\n";
  //  for (auto& norm : obj.normals)
  //    std::cout << norm.x << " " <<  norm.y << " " << norm.z << "\n";

  // Cleaning
  delete[] vertices;
  delete[] normals;
  delete[] textureCoords;
  delete[] faces;
  file.close();

  return obj;
}
}  // namespace s21
