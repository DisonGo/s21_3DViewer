#include "E/Object3DFactory.h"
#define MAP_CONTAINS(map, val) (map.find(val) != map.end())
namespace s21 {
void Object3DFactory::SetParser(BaseParser *parser) {
  if (parser_) delete parser_;
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
  if (parser_type == kOBJParser) {
    try {
      auto data = static_cast<OBJParser *>(parser_)->Parse(file_path);
      for (const auto &[type, importer] : importers_)
        if (importer.on) object.UploadMesh(data, importer.importer_ptr);
    } catch (...) {
      std::cout << "no file";
    }
  }
  return object;
}

}  // namespace s21
