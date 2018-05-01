#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "uart/settingsdialog.h"
#include "dut_data.h"


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

    void on_pushButton_DUT_SRAM_Read_clicked();

    void on_pushButton_TID_check_clicked();

    void on_pushButton_DUT_SRAM_Write_FF_clicked();

    void on_pushButton_DUT_SRAM_Write_00_clicked();

    void on_pushButton_DUT_SRAM_Write_55_clicked();

    void on_pushButton_DUT_SRAM_Write_A5_clicked();

    void on_pushButton_DUT_SRAM_Write_clicked();

    void block_select_handle();

private:
    Ui::MainWindow *ui;
    SettingsDialog *uart_fpga_setting;
    QSerialPort *uart_fpga;
    char flag_kind_ER;
    dut_data *raw_data;
    int flag_data_pattern;

    void uart_fpga_writeData(const QByteArray &data);
    void radiobutton_block_select_setup();

};

#endif // MAINWINDOW_H
