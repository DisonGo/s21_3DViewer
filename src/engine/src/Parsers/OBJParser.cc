#include "Parsers/OBJParser.h"

#include <godison/Vectors.h>

#include "fstream"
#include <set>
namespace s21 {
TagCounters OBJParser::CountTags(const string filePath) {
  // FILE* obj_file = NULL;
  // obj_file = fopen(filePath.c_str(), "r");
  // if (!obj_file) throw std::invalid_argument("Can't open file");
  std::ifstream file(filePath, std::ios_base::in);
  size_t linesz = 0;
  char* str = nullptr;
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

  // free(str);
  // fclose(obj_file);
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

void OBJParser::FetchVerticesByFaces(const std::vector<Vertex> &source, std::vector<Vertex> &output, std::vector<Face> &faces)
{
  std::set<const Vertex*> existing_vertices;
  std::map<size_t ,size_t> v_indices_map;
  std::vector<Face> calibrated_faces;

  const auto faces_size = faces.size();

  for (size_t i = 0; i < faces_size; ++i) {

    calibrated_faces.push_back(faces[i]);

    for (auto& index : calibrated_faces[i].indices) {
      // Fetch only unique vertices
      auto vertex = &source[index.v_index];
      bool vertex_exists = existing_vertices.find(vertex) != existing_vertices.end();
      if (!vertex_exists) {
        existing_vertices.insert(vertex);
        v_indices_map.insert({index.v_index, output.size()});
        output.push_back(*vertex);
      }
    }
    // Map used indices to new vertex array
    for (auto& index : calibrated_faces[i].indices)
      index.v_index =  v_indices_map.at(index.v_index);
  }
  faces = std::move(calibrated_faces);
}

void OBJParser::FetchNormalsByFaces(const std::vector<Normal> &source, std::vector<Normal> &output, std::vector<Face> &faces)
{

}

std::vector<OBJ> OBJParser::CalculateObjects(OBJ &all_data, std::vector<object> objects)
{
  std::vector<OBJ> datas;
  std::vector<Face>& faces = all_data.faces;
  if (objects.empty()) return datas;
  if (objects.size() == 1) {
    all_data.name = objects.front().name;
    datas.push_back(std::move(all_data));
    return datas;
  }
  for (auto& object : objects) {
    OBJ data;
    data.name = object.name;
    data.faces = std::vector<Face>(faces.begin() + object.i_start, faces.begin() + object.i_end);
    FetchVerticesByFaces(all_data.vertices, data.vertices, data.faces);
//    data.normals = all_data.normals;
    datas.push_back(data);
  }
  return datas;
}

std::vector<OBJ> OBJParser::Parse(string filePath) {
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
  std::vector<object> objects;
  object current_object;
  Vertex* vertices = new Vertex[tags.vC];
  Normal* normals = new Normal[tags.vnC];
  TextureCoord* textureCoords = new TextureCoord[tags.vtC];
  Face* faces = new Face[tags.fC];

  TagCounters counter;  // Index counter for dynamic arrays
  size_t linesz = 0;
  char* str = nullptr;
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
    } else if (tag == "o") {
          current_object.i_end = counter.fC;
          bool empty = current_object.i_end == current_object.i_start;
          if (!empty) objects.push_back(current_object);
          current_object = object();
          current_object.name = values;
          auto next_index = counter.fC + (counter.fC != 0);
          current_object.i_start = next_index != tags.fC ? next_index : counter.fC;
    }
  }
  current_object.i_end = counter.fC;
  bool empty = current_object.i_end == current_object.i_start;
  if (!empty) objects.push_back(current_object);


  // Insert values from dynamic arrays to OBJ std::vector`s

  obj.vertices.insert(obj.vertices.end(), vertices, vertices + tags.vC);
  obj.normals.insert(obj.normals.end(), normals, normals + tags.vnC);
  obj.texture_coords.insert(obj.texture_coords.end(), textureCoords,
                            textureCoords + tags.vtC);
  obj.faces.insert(obj.faces.end(), faces, faces + tags.fC);
  //  for (auto& face : obj.faces) {
  //    QString str;
  //    for (auto& index : face.indices)
  //      str += QString().number(index.v_index) + " ";
  //    qDebug() << str;
  //  }
  for (const auto& object : objects)
    qDebug() << "Start:" << object.i_start << "End:" << object.i_end << "Name:" << object.name.c_str();
  CenterVertices(obj.vertices, {0, 0, 0});
  ElevateVerticesToGround(obj.vertices);
  CalculateNegativeIndices(obj.faces, obj.vertices.size());

  // Cleaning
  delete[] vertices;
  delete[] normals;
  delete[] textureCoords;
  delete[] faces;
  file.close();
  // if (str) free(str);
  // fclose(obj_file);
  return CalculateObjects(obj, objects);
}
}  // namespace s21
