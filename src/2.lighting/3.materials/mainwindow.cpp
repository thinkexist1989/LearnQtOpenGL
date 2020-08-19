
#include <src/3.model_loading/1.model_loading/mainwindow.h>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_checkBox_stateChanged(int state)
{
    qDebug() << "state is: " << state;
    if(state == 0)
    {
        ui->openGLWidget->setPolygonLineMode(false);
    }
    if(state == 2)
    {
        ui->openGLWidget->setPolygonLineMode(true);
    }
}
