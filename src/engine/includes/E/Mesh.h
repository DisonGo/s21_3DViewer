#ifndef MESH_H
#define MESH_H
#include <QMatrix4x4>
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
#include "Strategies/Import/OBJImportWireframeStrategy.h"
using std::map;
class Mesh : public EObject, protected QOpenGLFunctions {
 public:
  Mesh();
  Mesh(const s21::OBJ& obj);
  ~Mesh();
  void Draw(GLenum type);
  void Import(const s21::OBJ& obj, s21::OBJImportStrategy* importer);

  virtual EObjectType GetType() const override { return type_; };

 protected:
  EObjectType type_ = EObjectType::kMesh;

 private:
//  struct VAOmap_ {

//  };
  map<s21::OBJImportStrategyType, VAO*> VAOmap_;
  int indicesN_ = 0;
  DrawConfig* draw_config_;
  VAO vertex_only_VAO_;
  VAO mix_VAO_;
};

#endif  // MESH_H
