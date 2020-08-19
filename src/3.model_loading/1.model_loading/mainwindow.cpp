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

void MainWindow::on_checkBox_stateChanged(int state) {
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

void MainWindow::on_jointSlider1_valueChanged(int value)
{
    ui->openGLWidget->setJointValue(0, value/10.0);
}

void MainWindow::on_jointSlider2_valueChanged(int value)
{
    ui->openGLWidget->setJointValue(1, value/10.0);
}

void MainWindow::on_jointSlider3_valueChanged(int value)
{
    ui->openGLWidget->setJointValue(2, value/10.0);
}

void MainWindow::on_jointSlider4_valueChanged(int value)
{
    ui->openGLWidget->setJointValue(3, value/10.0);
}

void MainWindow::on_jointSlider5_valueChanged(int value)
{
    ui->openGLWidget->setJointValue(4, value/10.0);
}

void MainWindow::on_jointSlider6_valueChanged(int value)
{
    ui->openGLWidget->setJointValue(5, value/10.0);
}
