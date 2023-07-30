#ifndef OBJECT3DFACTORY_H
#define OBJECT3DFACTORY_H

#include <map>

#include "E/Object3D.h"
#include "Parsers/OBJParser.h"
#include "Strategies/Import/OBJImportStandartStrategy.h"
#include "Strategies/Import/OBJImportStrategy.h"
#include "Strategies/Import/OBJImportTriangleStrategy.h"
#include "Strategies/Import/OBJImportVertexOnlyStrategy.h"
#include "Strategies/Import/OBJImportWireframeStrategy.h"
namespace s21 {
class Object3DFactory {
  using ImporterBundle = struct Bundle {
    OBJImportStrategy* importer_ptr = nullptr;
    bool on = false;
  };

 public:
  Object3DFactory() = default;
  Object3DFactory(const Object3DFactory& other) {
    *this = other;
  }

  Object3DFactory(Object3DFactory&& other) {
    *this = other;
  }

  Object3DFactory& operator=(const Object3DFactory& other);
  Object3DFactory& operator=(Object3DFactory&& other);
  ~Object3DFactory() {
    if (parser_) delete parser_;
  };
  Object3D GetObject(const char* file_path);
  void SetParser(BaseParser* parser);
  void InstallImporter(OBJImportStrategy* importer);
  void ToggleImporter(OBJImportStrategyType importer_type);
  void DeleteImporter(OBJImportStrategyType importer_type);

 private:
  BaseParser* parser_ = nullptr;
  std::map<OBJImportStrategyType, ImporterBundle> importers_;
};
}  // namespace s21
#endif  // OBJECT3DFACTORY_H
