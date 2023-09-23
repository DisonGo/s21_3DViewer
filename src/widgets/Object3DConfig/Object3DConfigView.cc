#include "Object3DConfig/Object3DConfigView.h"

#include "ui_Object3DConfigView.h"
namespace s21 {
Object3DConfigView::Object3DConfigView(QWidget *parent)
    : ConfigWidget(parent), ui(new Ui::Object3DConfigView) {
  Setup();
}

Object3DConfigView::Object3DConfigView(s21::Object3DSpacer *object_spacer,
                                       QWidget *parent)
    : Object3DConfigView(parent) {
  SetupSpacer(object_spacer);
  SetValuesFromConfig();
}

Object3DConfigView::~Object3DConfigView() { delete ui; }

void Object3DConfigView::Setup() {
  ui->setupUi(this);
  ui->LineColorTriplet->SetTexts("r:", "g:", "b:");
  ui->PointColorTriplet->SetTexts("r:", "g:", "b:");
  ui->BaseColorTriplet->SetTexts("r:", "g:", "b:");

  ui->LineColorTriplet->SetRange(0, 255);
  ui->PointColorTriplet->SetRange(0, 255);
  ui->BaseColorTriplet->SetRange(0, 255);

  ui->LineColorTriplet->SetStep(1);
  ui->PointColorTriplet->SetStep(1);
  ui->BaseColorTriplet->SetStep(1);

  SetupConnects();
}

void Object3DConfigView::SetupSpacer(s21::Object3DSpacer *object_spacer) {
  object_spacer_ = object_spacer;
  if (!object_spacer_) return;
  connect(object_spacer_, &s21::Object3DSpacer::ConfigUpdated, this,
          &Object3DConfigView::SetValuesFromConfig);
}

void Object3DConfigView::SetupConnects() {
  connect(ui->LineColorTriplet, &TripletWidget::InputsChanged, this,
          &Object3DConfigView::SetColor);
  connect(ui->PointColorTriplet, &TripletWidget::InputsChanged, this,
          &Object3DConfigView::SetColor);
  connect(ui->BaseColorTriplet, &TripletWidget::InputsChanged, this,
          &Object3DConfigView::SetColor);
  for (auto &but : ui->PointTypeG->buttons())
    connect(but, &QRadioButton::toggled, this,
            &Object3DConfigView::SetPointType);
  for (auto &but : ui->LineTypeG->buttons())
    connect(but, &QRadioButton::toggled, this,
            &Object3DConfigView::SetLineType);
  for (auto &but : ui->DisplayTypeG->buttons())
    connect(but, &QRadioButton::toggled, this,
            &Object3DConfigView::SetDisplayType);
  connect(ui->LineWidthSB, &QDoubleSpinBox::valueChanged, this,
          &Object3DConfigView::SetLineWidth);
  connect(ui->PointSizeSB, &QDoubleSpinBox::valueChanged, this,
          &Object3DConfigView::SetPointSize);
  connect(ui->texture_toggleCB, &QCheckBox::stateChanged, this,
          &Object3DConfigView::SetTextureToggle);
  connect(ui->lighting_toggleCB, &QCheckBox::stateChanged, this,
          &Object3DConfigView::SetLightingToggle);
}

void Object3DConfigView::SetValuesFromConfig() {
  if (!object_spacer_) return;
  auto &mat = object_spacer_->GetMaterial();
  ui->LineWidthSB->setValue(mat.edges_thickness);
  ui->PointSizeSB->setValue(mat.vertices_size);

  ui->PointTypeNoneB->setChecked(mat.point_display_method == kNoPoint);
  ui->PointTypeCircleB->setChecked(mat.point_display_method == kCircle);
  ui->PointTypeSquareB->setChecked(mat.point_display_method == kSquare);

  ui->LineTypeSolidB->setChecked(mat.line_display_type == kSolid);
  ui->LineTypeDashedB->setChecked(mat.line_display_type == kDashed);

  ui->DisplayTypeWireframeB->setChecked(mat.object_display_type == kWireframe);
  ui->DisplayTypeFlatB->setChecked(mat.object_display_type == kFlatShading);
  ui->DisplayTypeSmoothB->setChecked(mat.object_display_type == kSmoothShading);

  ui->LineColorTriplet->SetValues(mat.edges_color);

  ui->PointColorTriplet->SetValues(mat.vertices_color);

  ui->BaseColorTriplet->SetValues(mat.base_color);
  ui->texture_toggleCB->setChecked(mat.texture_on);
  ui->lighting_toggleCB->setChecked(mat.lighting_on);
}

void Object3DConfigView::SetColor(const Vector3D &color) {
  if (!object_spacer_) return;

  auto widget_ptr = static_cast<TripletWidget *>(sender());

  auto style = QString("background: rgba(%1,%2,%3,0.3);")
                   .arg(color.X())
                   .arg(color.Y())
                   .arg(color.Z());
  auto &mat = object_spacer_->GetMaterial();
  if (widget_ptr == ui->LineColorTriplet) {
    mat.edges_color = color;
    widget_ptr->setStyleSheet("#LineColorTriplet{" + style + "}");
  }
  if (widget_ptr == ui->PointColorTriplet) {
    mat.vertices_color = color;
    widget_ptr->setStyleSheet("#PointColorTriplet{" + style + "}");
  }
  if (widget_ptr == ui->BaseColorTriplet) {
    mat.base_color = color;
    widget_ptr->setStyleSheet("#PointColorTriplet{" + style + "}");
  }
  emit UpdateRequest();
}

void Object3DConfigView::SetLineType(bool checked) {
  Q_UNUSED(checked)
  if (!object_spacer_) return;
  auto &mat = object_spacer_->GetMaterial();
  auto widget_ptr = static_cast<QRadioButton *>(sender());
  if (widget_ptr == ui->LineTypeSolidB) mat.line_display_type = s21::kSolid;
  if (widget_ptr == ui->LineTypeDashedB) mat.line_display_type = s21::kDashed;
  emit UpdateRequest();
}

void Object3DConfigView::SetPointType(bool checked) {
  Q_UNUSED(checked)
  if (!object_spacer_) return;
  auto &mat = object_spacer_->GetMaterial();
  auto widget_ptr = static_cast<QRadioButton *>(sender());
  if (widget_ptr == ui->PointTypeNoneB)
    mat.point_display_method = s21::kNoPoint;
  if (widget_ptr == ui->PointTypeCircleB)
    mat.point_display_method = s21::kCircle;
  if (widget_ptr == ui->PointTypeSquareB)
    mat.point_display_method = s21::kSquare;
  emit UpdateRequest();
}

void Object3DConfigView::SetDisplayType(bool checked) {
  Q_UNUSED(checked)
  if (!object_spacer_) return;

  auto widget_ptr = static_cast<QRadioButton *>(sender());
  if (widget_ptr == ui->DisplayTypeWireframeB)
    object_spacer_->SetObjectDisplayType(s21::kWireframe);
  if (widget_ptr == ui->DisplayTypeFlatB)
    object_spacer_->SetObjectDisplayType(s21::kFlatShading);
  if (widget_ptr == ui->DisplayTypeSmoothB)
    object_spacer_->SetObjectDisplayType(s21::kSmoothShading);
  emit UpdateRequest();
}

void Object3DConfigView::SetLineWidth(double width) {
  if (!object_spacer_) return;
  auto &mat = object_spacer_->GetMaterial();
  mat.edges_thickness = width;
  emit UpdateRequest();
}

void Object3DConfigView::SetPointSize(double size) {
  if (!object_spacer_) return;
  auto &mat = object_spacer_->GetMaterial();
  mat.vertices_size = size;
  emit UpdateRequest();
}

void Object3DConfigView::SetTextureToggle(int state) {
  if (!object_spacer_) return;
  auto &mat = object_spacer_->GetMaterial();
  mat.texture_on = state;
  emit UpdateRequest();
}

void Object3DConfigView::SetLightingToggle(int state) {
  if (!object_spacer_) return;
  auto &mat = object_spacer_->GetMaterial();
  mat.lighting_on = state;
  emit UpdateRequest();
}
}  // namespace s21
