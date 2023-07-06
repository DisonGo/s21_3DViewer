#ifndef OBJIMPORTSTRATEGY_H
#define OBJIMPORTSTRATEGY_H

#include "GL/EBO.h"
#include "GL/VAO.h"
#include "Strategies/Import/ImportStrategy.h"
#include "Types/OBJ.h"
#include "Types/VertexData.h"
namespace s21 {
enum OBJImportStrategyType {
  kNone, kStandart, kTriangle, kWireframe
};
class OBJImportStrategy : public ImportStrategy {
public:
  virtual OBJImportStrategyType GetType() const { return type_; };
  virtual VAO Import(const OBJ& obj) const = 0;
protected:
  OBJImportStrategyType type_ = kNone;
  virtual std::vector<VertexData> GetVertexDataArray(const OBJ& obj) const = 0;
};
}  // namespace s21

#endif  // OBJIMPORTSTRATEGY_H
