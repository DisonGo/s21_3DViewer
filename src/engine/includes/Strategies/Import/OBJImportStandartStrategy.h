#ifndef OBJIMPORTSTANDARTSTRATEGY_H
#define OBJIMPORTSTANDARTSTRATEGY_H
#include "Strategies/Import/OBJImportStrategy.h"
namespace s21 {
class OBJImportStandartStrategy : public OBJImportStrategy {
 public:
  virtual OBJImportStrategyType GetType() const override { return type_; };
  virtual VAO Import(const OBJ& obj) const override;

 protected:
  OBJImportStrategyType type_ = kStandartImport;
  virtual std::vector<VertexData> GetVertexDataArray(
      const OBJ& obj) const override;
};
}  // namespace s21
#endif  // OBJIMPORTSTANDARTSTRATEGY_H
