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
  connect(ui->LineWidthSB, &QDoubleSpinBox::valueChanged, this,
          &Object3DConfigView::SetLineWidth);
  connect(ui->PointSizeSB, &QDoubleSpinBox::valueChanged, this,
          &Object3DConfigView::SetPointSize);
}

void Object3DConfigView::SetValuesFromConfig() {
  if (!object_spacer_) return;
  auto line_width = object_spacer_->GetEdgesThicknessValue();
  auto point_size = object_spacer_->GetVerticesSizeValue();
  ui->LineWidthSB->setValue(line_width);
  ui->PointSizeSB->setValue(point_size);

  auto line_type = object_spacer_->GetUITypeValue();
  auto point_type = object_spacer_->GetDisplayMethodValue();

  ui->PointTypeNoneB->setChecked(point_type == s21::PointDisplayType::kNone);
  ui->PointTypeCircleB->setChecked(point_type ==
                                   s21::PointDisplayType::kCircle);
  ui->PointTypeSquareB->setChecked(point_type ==
                                   s21::PointDisplayType::kSquare);

  ui->LineTypeSolidB->setChecked(line_type == s21::kSolid);
  ui->LineTypeDashedB->setChecked(line_type == s21::kDashed);

  auto line_color = object_spacer_->GetEdgesColorValue();
  Vector3D line_color_vec(line_color.red(), line_color.green(),
                          line_color.blue());
  ui->LineColorTriplet->SetValues(line_color_vec);

  auto point_color = object_spacer_->GetVerticesColorValue();
  Vector3D point_color_vec(point_color.red(), point_color.green(),
                           point_color.blue());
  ui->PointColorTriplet->SetValues(point_color_vec);

  auto base_color = object_spacer_->GetBaseColorValue();
  Vector3D base_color_vec(base_color.red(), base_color.green(),
                           base_color.blue());
  ui->BaseColorTriplet->SetValues(base_color_vec);
}

void Object3DConfigView::SetColor(const Vector3D &color) {
  if (!object_spacer_) return;

  auto new_color = QColor(color.X(), color.Y(), color.Z());

  auto widget_ptr = static_cast<TripletWidget *>(sender());

  auto style = QString("background: rgba(%1,%2,%3,0.3);")
                   .arg(color.X())
                   .arg(color.Y())
                   .arg(color.Z());

  if (widget_ptr == ui->LineColorTriplet) {
    object_spacer_->SetEdgesColorValue(new_color);
    widget_ptr->setStyleSheet("#LineColorTriplet{" + style + "}");
  }
  if (widget_ptr == ui->PointColorTriplet) {
    object_spacer_->SetVerticesColorValue(new_color);
    widget_ptr->setStyleSheet("#PointColorTriplet{" + style + "}");
  }
  if (widget_ptr == ui->BaseColorTriplet) {
    object_spacer_->SetBaseColorValue(new_color);
    widget_ptr->setStyleSheet("#PointColorTriplet{" + style + "}");
  }
  emit UpdateRequest();
}

void Object3DConfigView::SetLineType(bool checked) {
  Q_UNUSED(checked)
  if (!object_spacer_) return;
  auto widget_ptr = static_cast<QRadioButton *>(sender());
  if (widget_ptr == ui->LineTypeSolidB)
    object_spacer_->SetUITypeValue(s21::kSolid);
  if (widget_ptr == ui->LineTypeDashedB)
    object_spacer_->SetUITypeValue(s21::kDashed);
  emit UpdateRequest();
}

void Object3DConfigView::SetPointType(bool checked) {
  Q_UNUSED(checked)
  if (!object_spacer_) return;
  auto widget_ptr = static_cast<QRadioButton *>(sender());
  if (widget_ptr == ui->PointTypeNoneB)
    object_spacer_->SetDisplayMethodValue(s21::PointDisplayType::kNone);
  if (widget_ptr == ui->PointTypeCircleB)
    object_spacer_->SetDisplayMethodValue(s21::PointDisplayType::kCircle);
  if (widget_ptr == ui->PointTypeSquareB)
    object_spacer_->SetDisplayMethodValue(s21::PointDisplayType::kSquare);
  emit UpdateRequest();
}

void Object3DConfigView::SetLineWidth(double width) {
  if (!object_spacer_) return;
  object_spacer_->SetEdgesThicknessValue(width);
  emit UpdateRequest();
}

void Object3DConfigView::SetPointSize(double size) {
  if (!object_spacer_) return;
  object_spacer_->SetVerticesSizeValue(size);
  emit UpdateRequest();
}
}  // namespace s21
