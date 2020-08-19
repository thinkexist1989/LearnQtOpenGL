#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "widget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

public slots:
    void on_checkBox_stateChanged(int state);

    void on_jointSlider1_valueChanged(int value);

    void on_jointSlider2_valueChanged(int value);

    void on_jointSlider3_valueChanged(int value);

    void on_jointSlider4_valueChanged(int value);

    void on_jointSlider5_valueChanged(int value);

    void on_jointSlider6_valueChanged(int value);
};

#endif // MAINWINDOW_H
