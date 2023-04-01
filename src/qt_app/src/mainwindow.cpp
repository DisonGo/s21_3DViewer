#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setUnifiedTitleAndToolBarOnMac(true);
    connect(ui->toolButton_tab1, SIGNAL(clicked()), this, SLOT(choose_file()));
//    connect(ui->pushButton_colorLine, SIGNAL(clicked()), this, SLOT(choose_color()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::choose_file(){
    QString name = qgetenv("USER");
    if (name.isEmpty())
          name = qgetenv("USERNAME");
    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "/Users/" + name,
                "Objects (*.obj)"
                );
    ui->comboBox_tab1->addItem(filename);
    ui->comboBox_tab1->setCurrentIndex(ui->comboBox_tab1->findText(filename));

}

void MainWindow::choose_color(){
    QColor color = QColorDialog::getColor(Qt::red, this);

}

void MainWindow::on_pushButton_loadFile_clicked()
{
    QString filePath = ui->comboBox_tab1->currentText();
    if (filePath == "") return;
    ui->openGLWidget->importObjFile(filePath);
}

