#ifndef EOBJECT_H
#define EOBJECT_H
enum EObjectType { kNone = 0, kMesh, kCamera, kTransform, kObject3D };
class EObject {
 public:
  EObjectType type_ = kNone;
  virtual EObjectType GetType() const { return type_; };
  virtual ~EObject() = default;
  bool SameType(const EObject& obj) { return GetType() == obj.GetType(); };
};
#endif  // EOBJECT_H
