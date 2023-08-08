#ifndef EOBJECT_H
#define EOBJECT_H
namespace s21 {
enum EObjectType {
  kNone = 0,
  kMesh,
  kCamera,
  kTransform,
  kObject3D,
  kLight,
  kLightObject
};
class EObject {
 protected:
  EObjectType type_ = kNone;

 public:
  virtual EObjectType GetType() const { return type_; };
  virtual ~EObject() = default;
  bool SameType(const EObject& obj) { return GetType() == obj.GetType(); };
};
}  // namespace s21
#endif  // EOBJECT_H
