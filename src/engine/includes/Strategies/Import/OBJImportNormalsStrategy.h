#ifndef OBJIMPORTNORMALSSTRATEGY_H
#define OBJIMPORTNORMALSSTRATEGY_H
#include "Strategies/Import/OBJImportStrategy.h"
namespace s21 {
class OBJImportNormalsStrategy : public OBJImportStrategy {
 public:
  virtual OBJImportStrategyType GetType() const override { return type_; };
  virtual VAO Import(const OBJ& obj) const override;

 protected:
  OBJImportStrategyType type_ = kNormalsImport;
  virtual std::vector<VertexData> GetVertexDataArray(
      const OBJ& obj) const override;
  static std::vector<Face> GetNormalsIndexArray(const OBJ& obj);
};
}  // namespace s21
#endif  // OBJIMPORTNORMALSSTRATEGY_H
