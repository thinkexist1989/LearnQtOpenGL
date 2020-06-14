#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(this, &MainWindow::setPolygonLineMode, ui->openGLWidget, &Widget::setPolygonLineMode);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_checkBox_stateChanged(int state) {
    qDebug() << "state is: " << state;
    if(state == 0)
    {
        emit setPolygonLineMode(false);
//        ui->openGLWidget->setPolygonLineMode(false);
    }
    if(state == 2)
    {
        emit setPolygonLineMode(true);
//        ui->openGLWidget->setPolygonLineMode(true);
    }
}


