#include "DrawConfig/DrawConfigView.h"

#include "ui_DrawConfigView.h"
namespace s21 {
DrawConfigView::DrawConfigView(s21::DrawConfig& draw_config, QWidget* parent)
    : ConfigWidget(parent),
      draw_config_spacer_(draw_config, this),
      ui(new Ui::DrawConfigView) {
  ui->setupUi(this);
  ui->PointsCheckBox->setChecked(draw_config_spacer_.GetPoints());
  ui->LinesCheckBox->setChecked(draw_config_spacer_.GetLines());
  ui->TrianglesCheckBox->setChecked(draw_config_spacer_.GetTriangles());
  ui->TrianglesStripCheckBox->setChecked(
      draw_config_spacer_.GetTrianglesStrip());
  connect(ui->PointsCheckBox, SIGNAL(stateChanged(int)), &draw_config_spacer_,
          SLOT(SetPoints(int)));
  connect(ui->LinesCheckBox, SIGNAL(stateChanged(int)), &draw_config_spacer_,
          SLOT(SetLines(int)));
  connect(ui->TrianglesCheckBox, SIGNAL(stateChanged(int)),
          &draw_config_spacer_, SLOT(SetTriangles(int)));
  connect(ui->TrianglesStripCheckBox, SIGNAL(stateChanged(int)),
          &draw_config_spacer_, SLOT(SetTrianglesStrip(int)));
  connect(ui->PointsCheckBox, SIGNAL(stateChanged(int)), this,
          SIGNAL(DrawConfigUpdated()));
  connect(ui->LinesCheckBox, SIGNAL(stateChanged(int)), this,
          SIGNAL(DrawConfigUpdated()));
  connect(ui->TrianglesCheckBox, SIGNAL(stateChanged(int)), this,
          SIGNAL(DrawConfigUpdated()));
  connect(ui->TrianglesStripCheckBox, SIGNAL(stateChanged(int)), this,
          SIGNAL(DrawConfigUpdated()));
}

DrawConfigView::~DrawConfigView() { delete ui; }
}  // namespace s21
