#ifndef EOBJECT_H
#define EOBJECT_H
enum EObjectType { kNone = 0, kMesh, kCamera, kTransform, kObject3D };
class EObject {
 public:
  EObjectType type = kNone;
  virtual EObjectType GetType() const { return type; };
  virtual ~EObject() = default;
  bool SameType(const EObject& obj) { return GetType() == obj.GetType(); };
};
#endif  // EOBJECT_H
