#ifndef OBJIMPORTVERTEXONLYSTRATEGY_H
#define OBJIMPORTVERTEXONLYSTRATEGY_H
#include "Strategies/Import/OBJImportStrategy.h"
namespace s21 {
class OBJImportVertexOnlyStrategy : public OBJImportStrategy {
 public:
  virtual OBJImportStrategyType GetType() const override { return type_; };
  virtual VAO Import(const OBJ& obj) const override;

 protected:
  OBJImportStrategyType type_ = kVertexOnlyImport;
  virtual std::vector<VertexData> GetVertexDataArray(
      const OBJ& obj) const override;
};
}  // namespace s21
#endif  // OBJIMPORTVERTEXONLYSTRATEGY_H
