#include "ConfigWidgetFactory.h"

ConfigWidget *ConfigWidgetFactory::CreateWidget(s21::EObject *object,
                                                QWidget *parent) {
  if (!object) return CreatekNone(parent);
  ConfigWidget *widget = nullptr;
  auto type = object->GetType();
  if (type == s21::kNone) widget = CreatekNone(parent);
  if (type == s21::kCamera) widget = CreatekCamera(object, parent);
  if (type == s21::kTransform) widget = CreatekTransform(object, parent);
  if (type == s21::kMesh) widget = CreatekMesh(object, parent);
  if (type == s21::kObject3D) widget = CreatekObject3D(object, parent);
  if (widget){
    widget->setAttribute(Qt::WA_DeleteOnClose);
    widget->setObjectName("ConfigView");
  }
  return widget;
}

ConfigWidget *ConfigWidgetFactory::CreatekNone(QWidget *parent) {
  return new ConfigWidget(parent);
}
ConfigWidget *ConfigWidgetFactory::CreatekCamera(s21::EObject *object,
                                                 QWidget *parent) {
  auto obj_ptr = static_cast<s21::Camera *>(object);
  auto spacer = new s21::CameraSpacer(*obj_ptr, parent);
  auto view = new CameraConfigView(spacer, parent);
  return view;
}

ConfigWidget *ConfigWidgetFactory::CreatekTransform(s21::EObject *object,
                                                    QWidget *parent) {
  auto obj_ptr = static_cast<s21::Transform *>(object);
  auto spacer = new s21::TransformSpacer(*obj_ptr, parent);
  auto view = new TransformConfigView(spacer, parent);
  return view;
}

ConfigWidget *ConfigWidgetFactory::CreatekMesh(s21::EObject *object,
                                               QWidget *parent) {
  auto obj_ptr = static_cast<s21::Mesh *>(object);
  auto spacer = new s21::MeshSpacer(*obj_ptr, parent);
  auto view = new MeshConfigView(spacer, parent);
  return view;
}

ConfigWidget *ConfigWidgetFactory::CreatekObject3D(s21::EObject *object,
                                                   QWidget *parent) {
  auto obj_ptr = static_cast<s21::Object3D *>(object);
  auto spacer = new s21::Object3DSpacer(*obj_ptr, parent);
  auto view = new Object3DConfigView(spacer, parent);
  return view;
}
