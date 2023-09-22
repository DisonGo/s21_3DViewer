#ifndef OBJECT_3D_SPACER_H
#define OBJECT_3D_SPACER_H

#include <QObject>

#include "E/Object3D.h"
namespace s21 {
class Object3DSpacer : public QObject {
  Q_OBJECT
 public:
  Object3DSpacer(Object3D& object, QObject* parent = nullptr)
      : QObject(parent), object_(object){};
  Material& GetMaterial() { return object_.GetMaterial(); };
  void SetMaterial(const Material& new_material) {
    object_.SetMaterial(new_material);
    emit ConfigUpdated();
  };
 signals:
  void ConfigUpdated();

 private:
  Object3D& object_;
};
}  // namespace s21
#endif  // OBJECT_3D_SPACER_H
