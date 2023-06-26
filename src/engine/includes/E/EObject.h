#ifndef EOBJECT_H
#define EOBJECT_H
enum EObjectType { kNone, kMesh, kCamera, kTransform };
class EObject {
 public:
  EObjectType type = kNone;
  bool SameType(const EObject& obj) { return type == obj.type; };
};
#endif  // EOBJECT_H
