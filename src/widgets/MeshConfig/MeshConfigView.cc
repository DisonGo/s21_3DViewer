#include "MeshConfig/MeshConfigView.h"

#include "ui_MeshConfigView.h"

MeshConfigView::MeshConfigView(QWidget *parent)
    : ConfigWidget(parent), ui(new Ui::MeshConfigView) {
  Setup();
}

MeshConfigView::MeshConfigView(s21::MeshSpacer *mesh_spacer, QWidget *parent)
    : MeshConfigView(parent) {
  SetMeshSpacer(mesh_spacer);
}

MeshConfigView::~MeshConfigView() {
  if (mesh_spacer_) delete mesh_spacer_;
  delete ui;
}

void MeshConfigView::SetMeshSpacer(s21::MeshSpacer *mesh_spacer) {
  if (mesh_spacer_) delete mesh_spacer_;
  mesh_spacer_ = mesh_spacer;
  if (!mesh_spacer_) return;
  SetValuesFromConfig();
}

void MeshConfigView::SetValuesFromConfig() {
  ui->standartBufferCheckBox->setChecked(
      mesh_spacer_->GetBufferToogleValue(s21::kStandartImport));
  ui->triangleBufferCheckBox->setChecked(
      mesh_spacer_->GetBufferToogleValue(s21::kTriangleImport));
  ui->wireframeBufferCheckBox->setChecked(
      mesh_spacer_->GetBufferToogleValue(s21::kWireframeImport));
  ui->vertexOnlyBufferCheckBox->setChecked(
      mesh_spacer_->GetBufferToogleValue(s21::kVertexOnlyImport));
}

void MeshConfigView::SetBufferToggle(int value) {
  auto checkbox_ptr = static_cast<QCheckBox *>(sender());
  if (!checkbox_ptr || !mesh_spacer_) return;
  if (checkbox_ptr == ui->standartBufferCheckBox)
    mesh_spacer_->SetBufferToogleValue(s21::kStandartImport, value);
  if (checkbox_ptr == ui->triangleBufferCheckBox)
    mesh_spacer_->SetBufferToogleValue(s21::kTriangleImport, value);
  if (checkbox_ptr == ui->wireframeBufferCheckBox)
    mesh_spacer_->SetBufferToogleValue(s21::kWireframeImport, value);
  if (checkbox_ptr == ui->vertexOnlyBufferCheckBox)
    mesh_spacer_->SetBufferToogleValue(s21::kVertexOnlyImport, value);
  emit UpdateRequest();
}

void MeshConfigView::Setup() {
  if (ui) ui->setupUi(this);
  connect(ui->standartBufferCheckBox, &QCheckBox::stateChanged, this,
          &MeshConfigView::SetBufferToggle);
  connect(ui->triangleBufferCheckBox, &QCheckBox::stateChanged, this,
          &MeshConfigView::SetBufferToggle);
  connect(ui->wireframeBufferCheckBox, &QCheckBox::stateChanged, this,
          &MeshConfigView::SetBufferToggle);
  connect(ui->vertexOnlyBufferCheckBox, &QCheckBox::stateChanged, this,
          &MeshConfigView::SetBufferToggle);
}
