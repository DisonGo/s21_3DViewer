#include "DrawConfig/DrawConfigView.h"

#include "ui_DrawConfigView.h"

DrawConfigView::DrawConfigView(QWidget *parent)
    : QWidget(parent), drawConfigSpacer_(this), ui(new Ui::DrawConfigView) {
  ui->setupUi(this);
  ui->PointsCheckBox->setChecked(drawConfigSpacer_.GetPoints());
  ui->LinesCheckBox->setChecked(drawConfigSpacer_.GetLines());
  ui->TrianglesCheckBox->setChecked(drawConfigSpacer_.GetTriangles());
  ui->TrianglesStripCheckBox->setChecked(drawConfigSpacer_.GetTrianglesStrip());
  ui->RoundCircleCheckBox->setChecked(drawConfigSpacer_.GetRoundCircle());
  ui->DashedLinesCheckBox->setChecked(drawConfigSpacer_.GetDashedLines());
  connect(ui->PointsCheckBox, SIGNAL(stateChanged(int)), &drawConfigSpacer_,
          SLOT(SetPoints(int)));
  connect(ui->LinesCheckBox, SIGNAL(stateChanged(int)), &drawConfigSpacer_,
          SLOT(SetLines(int)));
  connect(ui->TrianglesCheckBox, SIGNAL(stateChanged(int)), &drawConfigSpacer_,
          SLOT(SetTriangles(int)));
  connect(ui->TrianglesStripCheckBox, SIGNAL(stateChanged(int)),
          &drawConfigSpacer_, SLOT(SetTrianglesStrip(int)));
  connect(ui->RoundCircleCheckBox, SIGNAL(stateChanged(int)),
          &drawConfigSpacer_, SLOT(SetRoundCircle(int)));
  connect(ui->DashedLinesCheckBox, SIGNAL(stateChanged(int)),
          &drawConfigSpacer_, SLOT(SetDashedLines(int)));
  connect(ui->IndexDrawCheckBox, SIGNAL(stateChanged(int)), &drawConfigSpacer_,
          SLOT(SetIndexDraw(int)));
  connect(ui->VertexOnlyDrawCheckBox, SIGNAL(stateChanged(int)),
          &drawConfigSpacer_, SLOT(SetVertexOnlyDraw(int)));

  connect(ui->PointsCheckBox, SIGNAL(stateChanged(int)), this,
          SIGNAL(DrawConfigUpdated()));
  connect(ui->LinesCheckBox, SIGNAL(stateChanged(int)), this,
          SIGNAL(DrawConfigUpdated()));
  connect(ui->TrianglesCheckBox, SIGNAL(stateChanged(int)), this,
          SIGNAL(DrawConfigUpdated()));
  connect(ui->TrianglesStripCheckBox, SIGNAL(stateChanged(int)), this,
          SIGNAL(DrawConfigUpdated()));
  connect(ui->RoundCircleCheckBox, SIGNAL(stateChanged(int)), this,
          SIGNAL(DrawConfigUpdated()));
  connect(ui->DashedLinesCheckBox, SIGNAL(stateChanged(int)), this,
          SIGNAL(DrawConfigUpdated()));
  connect(ui->IndexDrawCheckBox, SIGNAL(stateChanged(int)), this,
          SIGNAL(DrawConfigUpdated()));
  connect(ui->VertexOnlyDrawCheckBox, SIGNAL(stateChanged(int)), this,
          SIGNAL(DrawConfigUpdated()));
}

DrawConfigView::~DrawConfigView() { delete ui; }
