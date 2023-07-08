#ifndef MESHSPACER_H
#define MESHSPACER_H

#include <QObject>

#include "E/Mesh.h"
namespace s21 {
class MeshSpacer : public QObject {
  Q_OBJECT
 public:
  MeshSpacer(Mesh& mesh, QObject* parent = nullptr)
      : QObject(parent), mesh_(mesh){};
  bool GetBufferToogleValue(OBJImportStrategyType type);
  void SetBufferToogleValue(OBJImportStrategyType type, bool value);

 private:
  Mesh& mesh_;
};
}  // namespace s21
#endif  // MESHSPACER_H
