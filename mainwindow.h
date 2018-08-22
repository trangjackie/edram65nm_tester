#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "uart/settingsdialog.h"
#include "dut_data.h"
#include <QTimer>
#include <QBitArray>



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

    void uart_power_readData();

    void uart_power_handleError(QSerialPort::SerialPortError error);

    void onSIPOCheckbox_change();

    void on_pushButton_DUT_SIPO_set_clicked();

    void on_pushButton_TestChar_clicked();

    void on_pushButton_DUT_S12_Read_clicked();

    void on_pushButton_DUT_S12_Write_clicked();


    void on_pushButton_DUT_eDRAM1_Write_clicked();

    void on_pushButton_DUT_eDRAM2_Write_clicked();

    void on_pushButton_DUT_eDRAM1_WriteReadNextCell_clicked();

    void on_pushButton_clicked();

    void on_pushButton_HVDD_clicked();

    void on_pushButton_NVSS_clicked();

    void on_pushButton_power_on_clicked();

    void on_pushButton_power_off_clicked();

    void on_pushButton_uart_power_setting_clicked();

    void on_pushButton_uart_power_connect_clicked();

    void on_lineEdit_write_repeat_editingFinished();

private:
    Ui::MainWindow *ui;
    SettingsDialog *uart_fpga_setting;
    QSerialPort *uart_fpga;
    SettingsDialog *uart_power_setting;
    QSerialPort *uart_power;
    QByteArray uart_power_rxdata;
    dut_data *raw_data;
    QBitArray *ba_SIPO_setdata;

    bool b_array_org[128][256];
    bool b_array_rb[128][256];
    bool b_array_pt[128][256];

    QByteArray memdata_readback;
    int i_retension_error_0;
    int i_retension_error_1;
    int i_write_error_0;
    int i_write_error_1;

    char flag_kind_ER;

    int flag_data_pattern;

    QTimer *timer_tid;

    void uart_fpga_writeData(const QByteArray &data);
     void uart_power_writeData(const QByteArray &data);
    void radiobutton_block_select_setup();

    void write_report(QString str_data);
    QString get_time_string();

    void SIPOCheckbox_setup();
    QByteArray my_bitsToBytes(QBitArray* bits);
};

#endif // MAINWINDOW_H
