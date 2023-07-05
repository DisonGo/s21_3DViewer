#ifndef OBJIMPORTTRIANGLESTRATEGY_H
#define OBJIMPORTTRIANGLESTRATEGY_H
#include "Strategies/Import/OBJImportStrategy.h"
namespace s21 {
class OBJImportTriangleStrategy : public OBJImportStrategy {
 public:
  virtual VAO Import(const OBJ& obj) const override;

 protected:
  virtual std::vector<VertexData> GetVertexDataArray(
      const OBJ& obj) const override;
  static std::vector<Face> GetTriangleIndexArray(const OBJ& obj);
};
}  // namespace s21
#endif  // OBJIMPORTTRIANGLESTRATEGY_H
