#include "Parsers/OBJParser.h"

#include <godison/Vectors.h>

#include <set>

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
    tag.assign(line.substr(0, line.find(' ')));
    if (tag == "v") counter.vC++;
    if (tag == "vn") counter.vnC++;
    if (tag == "vt") counter.vtC++;
    if (tag == "f") counter.fC++;
  }
  file.close();
  return counter;
}

void OBJParser::ParseFace(const string values, Face* faces, size_t& index,
                          size_t vertex_index) {
  FaceVertex* vertices = nullptr;
  size_t vCount = 0;
  vertices = ParsePolygon(values, vCount, vertex_index);
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

void OBJParser::FetchVertexDataByFaces(const OBJ& source, OBJ& output,
                                       std::vector<Face>& faces) {
  std::set<const Vertex*> existing_vertices;
  std::set<const TextureCoord*> existing_uvs;
  std::map<size_t, size_t> v_indices_map;
  std::vector<Face> calibrated_faces;

  const auto faces_size = faces.size();
  bool has_uvs = source.HasUvs();
  bool fetch_by_vertices =
      source.vertices.size() > source.texture_coords.size();

  for (size_t i = 0; i < faces_size; ++i) {
    calibrated_faces.push_back(faces[i]);
    for (auto& index : calibrated_faces[i].indices) {
      if (fetch_by_vertices) {
        auto vertex = &source.vertices[index.v_index];
        bool vertex_found =
            existing_vertices.find(vertex) != existing_vertices.end();
        if (!vertex_found) {
          existing_vertices.insert(vertex);
          v_indices_map.insert({index.v_index, output.vertices.size()});
          output.vertices.emplace_back(source.vertices[index.v_index]);
          if (has_uvs)
            output.texture_coords.emplace_back(
                source.texture_coords[index.t_index]);
          output.normals.emplace_back(source.normals[index.v_index]);
        }
      } else {
        auto uv = &source.texture_coords[index.t_index];
        bool uv_found = existing_uvs.find(uv) != existing_uvs.end();
        if (!uv_found) {
          existing_uvs.insert(uv);
          v_indices_map.insert({index.t_index, output.vertices.size()});
          output.texture_coords.emplace_back(*uv);
          output.vertices.emplace_back(source.vertices[index.v_index]);
          output.normals.emplace_back(source.normals[index.v_index]);
        }
      }
    }
    for (auto& index : calibrated_faces[i].indices) {
      auto ind = fetch_by_vertices ? index.v_index : index.t_index;
      index.v_index = v_indices_map.at(ind);
    }
  }
  // logger_.Log(
  //     "Calibrated vertices arr size:" +
  //     std::to_string(output.vertices.size()), Logger::LogLevel::kInfo);
  // logger_.Log(
  //     "Calibrated normals arr size:" + std::to_string(output.normals.size()),
  //     Logger::LogLevel::kInfo);
  // logger_.Log("Calibrated texture_coords arr size:" +
  //                 std::to_string(output.texture_coords.size()),
  //             Logger::LogLevel::kInfo);

  faces = std::move(calibrated_faces);
}

void OBJParser::NormalizeVertices(std::vector<Vertex>& vertices,
                                  float normalizeSize) {
  float minX = std::numeric_limits<float>::max();
  float minY = std::numeric_limits<float>::max();
  float minZ = std::numeric_limits<float>::max();
  float maxX = std::numeric_limits<float>::min();
  float maxY = std::numeric_limits<float>::min();
  float maxZ = std::numeric_limits<float>::min();
  for (const auto& vertex : vertices) {
    minX = std::min(minX, vertex.x);
    minY = std::min(minY, vertex.y);
    minZ = std::min(minZ, vertex.z);
    maxX = std::max(maxX, vertex.x);
    maxY = std::max(maxY, vertex.y);
    maxZ = std::max(maxZ, vertex.z);
  }

  // Calculate the center and maximum absolute distance from the center
  auto centerX = (maxX + minX) / 2.0f;
  auto centerY = (maxY + minY) / 2.0f;
  auto centerZ = (maxZ + minZ) / 2.0f;
  auto maxDistance =
      std::max(std::max(maxX - centerX, maxY - centerY), maxZ - centerZ);

  // Scale the vertices
  auto scaleFactor = normalizeSize / maxDistance;
  for (auto& vertex : vertices) {
    vertex.x = (vertex.x - centerX) * scaleFactor;
    vertex.y = (vertex.y - centerY) * scaleFactor;
    vertex.z = (vertex.z - centerZ) * scaleFactor;
  }
}

std::vector<OBJ> OBJParser::CalculateObjects(OBJ& all_data,
                                             std::vector<Object> objects) {
  std::vector<OBJ> datas;
  std::vector<Face>& faces = all_data.faces;
  if (objects.empty()) {
    logger_.Log("Vector of objects if empty", Logger::LogLevel::kWarning);
    return datas;
  }
  // if (objects.size() == 1) {
  //   all_data.name = objects.front().name;
  //   datas.push_back(std::move(all_data));
  //   return datas;
  // }
  for (auto& object : objects) {
    if (object.i_start > object.i_end) {
      logger_.Log(object.name + ": Invalid group: start > end",
                  Logger::LogLevel::kError);
      continue;
    }
    OBJ data;
    data.name = object.name;
    data.faces = std::vector<Face>(faces.begin() + object.i_start,
                                   faces.begin() + object.i_end);
    FetchVertexDataByFaces(all_data, data, data.faces);
    datas.push_back(data);
  }
  return datas;
}
void OBJParser::GenerateNormals(OBJ& obj) {
  if (obj.vertices.empty()) return;
  if (obj.normals.size() == obj.vertices.size()) return;
  logger_.Log("Bad normals array. Generating new array",
              Logger::LogLevel::kWarning);
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
std::vector<OBJ> OBJParser::Parse(string filePath) {
  std::ifstream file(filePath, std::ios_base::in);
  if (file.bad()) {
    logger_.Log("Bad file. Empty array will be returned",
                Logger::LogLevel::kError);
    return std::vector<OBJ>();
  }
  OBJ obj;

  // Count total amount of tags in file for memory allocation

  TagCounters tags = CountTags(filePath);

  // std::vector memory allocation
  if (!tags.vC) logger_.Log("No vertices", Logger::LogLevel::kWarning);
  if (!tags.vnC) logger_.Log("No normals", Logger::LogLevel::kWarning);
  if (!tags.vtC) logger_.Log("No uv's", Logger::LogLevel::kWarning);
  if (!tags.fC) logger_.Log("No faces", Logger::LogLevel::kWarning);
  obj.vertices.reserve(tags.vC);
  obj.normals.reserve(tags.vnC);
  obj.texture_coords.reserve(tags.vtC);
  obj.faces.reserve(tags.fC);

  // Dynamic arrays memory allocation
  std::vector<Object> objects;
  Object current_object;
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
      vertices[counter.vC++] = ParseVertex(values);
    } else if (tag == "vt") {
      textureCoords[counter.vtC++] = ParseTextureCoord(values);
    } else if (tag == "vn") {
      normals[counter.vnC++] = ParseNormal(values);
    } else if (tag == "f") {
      ParseFace(values, faces, counter.fC, counter.vC);
    } else if (tag == "o" || tag == "g") {
      current_object.i_end = counter.fC;
      if (!current_object.IsEmpty()) objects.push_back(current_object);
      current_object = Object();
      current_object.name = values;
      auto next_index = counter.fC + (counter.fC != 0);
      current_object.i_start = next_index != tags.fC ? next_index : counter.fC;
    }
  }
  current_object.i_end = counter.fC;
  if (!current_object.IsEmpty()) objects.push_back(current_object);

  // Insert values from dynamic arrays to OBJ std::vector`s
  obj.vertices.insert(obj.vertices.end(), vertices, vertices + tags.vC);
  obj.normals.insert(obj.normals.end(), normals, normals + tags.vnC);
  obj.texture_coords.insert(obj.texture_coords.end(), textureCoords,
                            textureCoords + tags.vtC);
  obj.faces.insert(obj.faces.end(), faces, faces + tags.fC);
  CenterVertices(obj.vertices, {0, 0, 0});
  NormalizeVertices(obj.vertices, 2);
  GenerateNormals(obj);

  // Cleaning
  std::string log = counter.vtC > counter.vC    ? "vt > v"
                    : counter.vtC == counter.vC ? "vt == v"
                                                : "vt < v";
  if (counter.vtC == 0) log = "No vt";
  logger_.Log(log, Logger::LogLevel::kInfo);
  delete[] vertices;
  delete[] normals;
  delete[] textureCoords;
  delete[] faces;
  file.close();
  return CalculateObjects(obj, objects);
}
}  // namespace s21
