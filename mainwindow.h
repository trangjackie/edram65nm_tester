#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
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

private slots:
    void on_pushButton_app_close_clicked();

    void on_pushButton_uart_fpga_setting_clicked();

    void on_pushButton_uart_fpga_connect_clicked();

    void uart_fpga_readData();

    void uart_fpga_handleError(QSerialPort::SerialPortError error);

private:
    Ui::MainWindow *ui;
    SettingsDialog *uart_fpga_setting;
    QSerialPort *uart_fpga;
};

#endif // MAINWINDOW_H
