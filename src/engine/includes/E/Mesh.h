#ifndef MESH_H
#define MESH_H
#include <QOpenGLFunctions>

#include "DrawConfig.h"
#include "E/Camera.h"
#include "E/EObject.h"
#include "E/Transform.h"
#include "GL/EBO.h"
#include "GL/VAO.h"
#include "Shaders/Program.h"
#include "Strategies/Import/OBJImportStandartStrategy.h"
#include "Strategies/Import/OBJImportStrategy.h"
#include "Strategies/Import/OBJImportTriangleStrategy.h"
#include "Strategies/Import/OBJImportVertexOnlyStrategy.h"
#include "Strategies/Import/OBJImportWireframeStrategy.h"
using std::map;
namespace s21 {
class Mesh : public EObject, protected QOpenGLFunctions {
 public:
  Mesh();
  ~Mesh();
  Mesh(const OBJ& obj);
  void Draw(GLenum type);
  void Import(const OBJ& obj, OBJImportStrategy* importer);
  void SetBufferToggle(OBJImportStrategyType type, bool value);
  bool GetBufferToggle(OBJImportStrategyType type);
  virtual EObjectType GetType() const override { return type_; };

 protected:
  EObjectType type_ = EObjectType::kMesh;

 private:
  map<OBJImportStrategyType, bool> buffer_toggle_{{kStandartImport, false},
                                                  {kWireframeImport, false},
                                                  {kTriangleImport, true},
                                                  {kVertexOnlyImport, false}};
  map<OBJImportStrategyType, VAO*> VAO_map_;
  DrawConfig* draw_config_;
};
}  // namespace s21

#endif  // MESH_H
