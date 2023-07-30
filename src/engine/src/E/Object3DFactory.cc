#include "E/Object3DFactory.h"

#include "QFileInfo"
#define MAP_CONTAINS(map, val) (map.find(val) != map.end())
namespace s21 {
void Object3DFactory::SetParser(BaseParser *parser) {
  if (parser_) delete parser_;
  for (auto &[type, importer] : importers_)
    if (importer.importer_ptr) delete importer.importer_ptr;
  parser_ = parser;
}

void Object3DFactory::InstallImporter(OBJImportStrategy *importer) {
  if (!importer) return;
  auto importer_type = importer->GetType();
  if (!importers_.count(importer_type)) {
    importers_.insert({importer_type, {importer, true}});
  }
}

void Object3DFactory::DeleteImporter(OBJImportStrategyType importer_type) {
  if (importers_.count(importer_type)) {
    auto ptr = importers_[importer_type].importer_ptr;
    if (ptr) delete ptr;
    importers_.erase(importer_type);
  }
}
void Object3DFactory::ToggleImporter(OBJImportStrategyType importer_type) {
  if (importers_.count(importer_type)) {
    importers_[importer_type].on = !importers_[importer_type].on;
  }
}

Object3D Object3DFactory::GetObject(const char *file_path) {
  auto object = Object3D();
  if (!parser_) return object;
  auto parser_type = parser_->GetType();
  std::string file_name = QFileInfo(file_path).fileName().toStdString();
  if (parser_type == kOBJParser) {
    try {
      auto datas = static_cast<OBJParser *>(parser_)->Parse(file_path);
      object.SetFileName(file_name);
      for (const auto &data : datas)
        for (const auto &[type, importer] : importers_)
          if (importer.on) object.UploadMesh(data, importer.importer_ptr);
    } catch (...) {
      std::cout << "no file";
    }
  }
  return object;
}

Object3DFactory &Object3DFactory::operator=(Object3DFactory &&other) {
  if (this == &other) return *this;
  if (parser_) delete parser_;
  parser_ = nullptr;
  for (auto &[type, importer] : importers_) {
    if (importer.importer_ptr) delete importer.importer_ptr;
    importer.importer_ptr = nullptr;
  }
  std::swap(parser_, other.parser_);
  std::swap(importers_, other.importers_);
  return *this;
}
Object3DFactory &Object3DFactory::operator=(const Object3DFactory &other) {
  if (this == &other) return *this;

  if (parser_) delete parser_;
  if (other.parser_)
    parser_ = other.parser_->GetType() == s21::kOBJParser
                  ? new OBJParser(*static_cast<OBJParser *>(other.parser_))
                  : nullptr;
  else
    parser_ = other.parser_;
  for (auto &[type, importer] : other.importers_) {
    if (!importer.importer_ptr) continue;
    OBJImportStrategy *imp_ptr = nullptr;
    if (type == s21::kStandartImport)
      imp_ptr = new OBJImportStandartStrategy(
          *static_cast<OBJImportStandartStrategy *>(importer.importer_ptr));
    else if (type == s21::kWireframeImport)
      imp_ptr = new OBJImportWireframeStrategy(
          *static_cast<OBJImportWireframeStrategy *>(importer.importer_ptr));
    else if (type == s21::kTriangleImport)
      imp_ptr = new OBJImportTriangleStrategy(
          *static_cast<OBJImportTriangleStrategy *>(importer.importer_ptr));
    else if (type == s21::kVertexOnlyImport)
      imp_ptr = new OBJImportVertexOnlyStrategy(
          *static_cast<OBJImportVertexOnlyStrategy *>(importer.importer_ptr));
    importers_.insert({type, {imp_ptr, importer.on}});
  }
  return *this;
}

}  // namespace s21
