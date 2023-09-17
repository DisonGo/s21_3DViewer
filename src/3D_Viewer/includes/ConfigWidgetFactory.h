#ifndef CONFIGWIDGETFACTORY_H
#define CONFIGWIDGETFACTORY_H

#include <CameraConfig/CameraConfigView.h>
#include <LightConfig/LightConfigView.h>
#include <MeshConfig/MeshConfigView.h>
#include <Object3DConfig/Object3DConfigView.h>
#include <TransformConfig/TransformConfigView.h>

#include "E/EObject.h"
#include "Logger.h"
namespace s21 {
class ConfigWidgetFactory {
 public:
  ConfigWidgetFactory() = default;
  static ConfigWidget* CreateWidget(s21::EObject* object,
                                    QWidget* parent = nullptr);

 private:
  static ConfigWidget* CreatekNone(QWidget* parent);
  static ConfigWidget* CreatekCamera(s21::EObject* object, QWidget* parent);
  static ConfigWidget* CreatekTransform(s21::EObject* object, QWidget* parent);
  static ConfigWidget* CreatekMesh(s21::EObject* object, QWidget* parent);
  static ConfigWidget* CreatekObject3D(s21::EObject* object, QWidget* parent);
  static ConfigWidget* CreatekLight(s21::EObject* object, QWidget* parent);
};
}  // namespace s21
#endif  // CONFIGWIDGETFACTORY_H
