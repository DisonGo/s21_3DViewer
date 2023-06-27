#ifndef EOBJECT_H
#define EOBJECT_H
enum EObjectType { kNone, kMesh, kCamera, kTransform, kObject3D };
class EObject {
 public:
  EObjectType type = kNone;
  virtual EObjectType GetType() const { return type; };
  bool SameType(const EObject& obj) { return GetType() == obj.GetType(); };
};
#endif  // EOBJECT_H
