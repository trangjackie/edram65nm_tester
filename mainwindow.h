#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "uart/settingsdialog.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    SettingsDialog *uart_fpga_setting;

};

#endif // MAINWINDOW_H
