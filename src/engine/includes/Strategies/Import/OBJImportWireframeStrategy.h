#ifndef OBJIMPORTWIREFRAMESTRATEGY_H
#define OBJIMPORTWIREFRAMESTRATEGY_H
#include "Strategies/Import/OBJImportStrategy.h"
namespace s21 {
class OBJImportWireframeStrategy : public OBJImportStrategy {
 public:
  virtual OBJImportStrategyType GetType() const { return type_; };
  virtual VAO Import(const OBJ& obj) const override;

 protected:
  OBJImportStrategyType type_ = kWireframe;
  virtual std::vector<VertexData> GetVertexDataArray(
      const OBJ& obj) const override;
  static std::vector<Face> GetWireFrameIndexArray(const OBJ& obj);
};
}  // namespace s21
#endif  // OBJIMPORTWIREFRAMESTRATEGY_H
