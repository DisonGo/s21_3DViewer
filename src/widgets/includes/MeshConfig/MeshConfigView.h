#ifndef MESHCONFIGVIEW_H
#define MESHCONFIGVIEW_H

#include "ConfigWidget.h"
#include "Spacers/MeshSpacer.h"
namespace Ui {
class MeshConfigView;
}

class MeshConfigView : public ConfigWidget {
  Q_OBJECT

 public:
  explicit MeshConfigView(QWidget* parent = nullptr);
  explicit MeshConfigView(s21::MeshSpacer* mesh_spacer,
                          QWidget* parent = nullptr);
  ~MeshConfigView();
 public slots:
  void SetMeshSpacer(s21::MeshSpacer* mesh_spacer);
  void SetValuesFromConfig();
  void SetBufferToggle(int value);

 private:
  void Setup();
  s21::MeshSpacer* mesh_spacer_ = nullptr;
  Ui::MeshConfigView* ui;
};

#endif  // MESHCONFIGVIEW_H
