#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // UART FPGA
    uart_fpga_setting = new SettingsDialog;
    uart_fpga_setting->setdefault(0,3);
    uart_fpga = new QSerialPort(this);
    connect(uart_fpga, SIGNAL(error(QSerialPort::SerialPortError)), this,
            SLOT(uart_fpga_handleError(QSerialPort::SerialPortError)));
    connect(uart_fpga, SIGNAL(readyRead()), this, SLOT(uart_fpga_readData()));

    // DUT data
    raw_data = new dut_data;
    radiobutton_block_select_setup();
    ui->radioButton_b0->setChecked(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_app_close_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Quit program.");
    msgBox.setInformativeText("Do you want to leave?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    int ret = msgBox.exec();
    switch (ret) {
      case QMessageBox::Yes:
          // Yes was clicked
        QApplication::quit();
          break;
      case QMessageBox::Cancel:
          // Cancel was clicked
          break;
      default:
          // should never be reached
          break;
    }
}

void MainWindow::on_pushButton_uart_fpga_setting_clicked()
{
    uart_fpga_setting->show();
}

void MainWindow::radiobutton_block_select_setup()
{
    connect(ui->radioButton_b0 ,SIGNAL(clicked()),this,SLOT(block_select_handle()));
    connect(ui->radioButton_b1 ,SIGNAL(clicked()),this,SLOT(block_select_handle()));
    connect(ui->radioButton_b2 ,SIGNAL(clicked()),this,SLOT(block_select_handle()));
    connect(ui->radioButton_b3 ,SIGNAL(clicked()),this,SLOT(block_select_handle()));
    connect(ui->radioButton_b4 ,SIGNAL(clicked()),this,SLOT(block_select_handle()));
    connect(ui->radioButton_b5 ,SIGNAL(clicked()),this,SLOT(block_select_handle()));
    connect(ui->radioButton_b6 ,SIGNAL(clicked()),this,SLOT(block_select_handle()));
    connect(ui->radioButton_b7 ,SIGNAL(clicked()),this,SLOT(block_select_handle()));
    connect(ui->radioButton_b8 ,SIGNAL(clicked()),this,SLOT(block_select_handle()));
    connect(ui->radioButton_b9 ,SIGNAL(clicked()),this,SLOT(block_select_handle()));
    connect(ui->radioButton_b10 ,SIGNAL(clicked()),this,SLOT(block_select_handle()));
    connect(ui->radioButton_b11 ,SIGNAL(clicked()),this,SLOT(block_select_handle()));
    connect(ui->radioButton_b12 ,SIGNAL(clicked()),this,SLOT(block_select_handle()));
    connect(ui->radioButton_b13 ,SIGNAL(clicked()),this,SLOT(block_select_handle()));
    connect(ui->radioButton_b14 ,SIGNAL(clicked()),this,SLOT(block_select_handle()));
    connect(ui->radioButton_b15 ,SIGNAL(clicked()),this,SLOT(block_select_handle()));
    connect(ui->radioButton_b1tid ,SIGNAL(clicked()),this,SLOT(block_select_handle()));
}

void MainWindow::block_select_handle()
{
    if (ui->radioButton_b0->isChecked()){raw_data->selected_block = 0; }
    if (ui->radioButton_b1->isChecked()){raw_data->selected_block = 1; }
    if (ui->radioButton_b2->isChecked()){raw_data->selected_block = 2; }
    if (ui->radioButton_b3->isChecked()){raw_data->selected_block = 3; }
    if (ui->radioButton_b4->isChecked()){raw_data->selected_block = 4; }
    if (ui->radioButton_b5->isChecked()){raw_data->selected_block = 5; }
    if (ui->radioButton_b6->isChecked()){raw_data->selected_block = 6; }
    if (ui->radioButton_b7->isChecked()){raw_data->selected_block = 7; }
    if (ui->radioButton_b8->isChecked()){raw_data->selected_block = 8; }
    if (ui->radioButton_b9->isChecked()){raw_data->selected_block = 9; }
    if (ui->radioButton_b10->isChecked()){raw_data->selected_block = 10; }
    if (ui->radioButton_b11->isChecked()){raw_data->selected_block = 11; }
    if (ui->radioButton_b12->isChecked()){raw_data->selected_block = 12; }
    if (ui->radioButton_b13->isChecked()){raw_data->selected_block = 13; }
    if (ui->radioButton_b14->isChecked()){raw_data->selected_block = 14; }
    if (ui->radioButton_b15->isChecked()){raw_data->selected_block = 15; }
    if (ui->radioButton_b1tid->isChecked()){raw_data->selected_block = 16; }
    if (raw_data->data_avarible)
    {
        QImage img(128, 256, QImage::Format_RGB888);
        img.fill(QColor(Qt::white).rgb());
        raw_data->convert_data_to_image(&img);
        ui->label_bitmap->setPixmap(QPixmap::fromImage(img));
    }
}

void MainWindow::on_pushButton_uart_fpga_connect_clicked()
{
    if (ui->pushButton_uart_fpga_connect->text()=="Connect") // have not connected
    {
        SettingsDialog::Settings p = uart_fpga_setting->settings();
        uart_fpga->setPortName(p.name);
        uart_fpga->setBaudRate(p.baudRate);
        uart_fpga->setDataBits(p.dataBits);
        uart_fpga->setParity(p.parity);
        uart_fpga->setStopBits(p.stopBits);
        uart_fpga->setFlowControl(p.flowControl);
        if (uart_fpga->open(QIODevice::ReadWrite)) {
            ui->pushButton_uart_fpga_connect->setToolTip("Click to disconnect UART.");
            ui->pushButton_uart_fpga_connect->setText("Disconnect");
            ui->pushButton_uart_fpga_setting->setEnabled(false);
            ui->statusBar->showMessage(QString("Connected to %1 : %2, %3, %4, %5, %6")
                              .arg(p.name).arg(p.stringBaudRate).arg(p.stringDataBits)
                              .arg(p.stringParity).arg(p.stringStopBits).arg(p.stringFlowControl));
        } else {
            QMessageBox::critical(this, tr("Error"), uart_fpga->errorString());
            ui->statusBar->showMessage("Open error");
        }
    }
    else // connected already
    {
        QMessageBox msgBox;
        msgBox.setText("Disconnect serial port");
        msgBox.setInformativeText("Are you sure?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        int ret = msgBox.exec();
        switch (ret) {
          case QMessageBox::Yes:
            // Yes was clicked--> disconnect
            if (uart_fpga->isOpen())
                uart_fpga->close();
            //console->setEnabled(false);
            ui->pushButton_uart_fpga_connect->setText("Connect");
            ui->pushButton_uart_fpga_connect->setToolTip("Click to connect UART.");
            ui->pushButton_uart_fpga_setting->setEnabled(true);
            ui->statusBar->showMessage("UART fpga disconnected");
              break;
          case QMessageBox::Cancel:
            // Cancel was clicked
            break;
          default:
            // should never be reached
            break;
        }
    }
}

void MainWindow::uart_fpga_readData()
{
    raw_data->raw_data->clear();
    raw_data->raw_data->append(uart_fpga->readAll());
    qDebug("data come 0");
    while (uart_fpga->waitForReadyRead(50)){
            //qDebug("data come 1");
            raw_data->raw_data->append(uart_fpga->readAll());
    }

    if (uart_fpga->error() == QSerialPort::ReadError) {
        qDebug("Failed to read from port "+uart_fpga->portName().toLatin1()+", error: "+uart_fpga->errorString().toLatin1());
    } else if (uart_fpga->error() == QSerialPort::TimeoutError && raw_data->raw_data->isEmpty()) {
        qDebug("No data was currently available for reading from port "+uart_fpga->portName().toLatin1());
    }

    qDebug("Data successfully received from port "+uart_fpga->portName().toLatin1());
    ui->statusBar->showMessage("Data length "+QString::number(raw_data->raw_data->length(),10));
    ui->plainTextEdit_console->clear();
    ui->plainTextEdit_console->insertPlainText(QString(*raw_data->raw_data));

    // classify data after read
    raw_data->data_classify();
    // update TID if have
    ui->label_f_TID_0->setText(QString::number(raw_data->iTID[0]));
    ui->label_f_TID_1->setText(QString::number(raw_data->iTID[1]));

    if (raw_data->data_avarible)
    {
        QImage img(128, 256, QImage::Format_RGB888);
        img.fill(QColor(Qt::white).rgb());
        raw_data->convert_data_to_image(&img);
        ui->label_bitmap->setPixmap(QPixmap::fromImage(img));
    }

}

void MainWindow::uart_fpga_writeData(const QByteArray &data)
{
    uart_fpga->write(data);
}

void MainWindow::uart_fpga_handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
    QMessageBox::critical(this, QString("Critical Error"), uart_fpga->errorString());
    }
}

void MainWindow::on_pushButton_DUT_SRAM_Read_clicked()
{
    QString str = "U"; // Read all data from memory (DUT)
    uart_fpga_writeData(str.toLocal8Bit());
    flag_kind_ER = 'R';
}

void MainWindow::on_pushButton_TID_check_clicked()
{
    QString str = "t"; // check TID (DUT)
    uart_fpga_writeData(str.toLocal8Bit());
    flag_kind_ER = 't';
}

void MainWindow::on_pushButton_DUT_SRAM_Write_FF_clicked()
{
    QString str = "F"; // Write data to memory (DUT)
    uart_fpga_writeData(str.toLocal8Bit());
    flag_data_pattern = 0b11111111;
    flag_kind_ER = 'W';
}

void MainWindow::on_pushButton_DUT_SRAM_Write_00_clicked()
{
    QString str = "0"; // Write data to memory (DUT)
    uart_fpga_writeData(str.toLocal8Bit());
    flag_data_pattern = 0b00000000;
    flag_kind_ER = 'W';
}

void MainWindow::on_pushButton_DUT_SRAM_Write_55_clicked()
{
    QString str = "6"; // Write data to memory (DUT)
    uart_fpga_writeData(str.toLocal8Bit());
    flag_data_pattern = 0b01010101;
    flag_kind_ER = 'W';
}

void MainWindow::on_pushButton_DUT_SRAM_Write_A5_clicked()
{
    QString str = "5"; // Write data to memory (DUT)
    uart_fpga_writeData(str.toLocal8Bit());
    flag_data_pattern = 0b10100101;
    flag_kind_ER = 'W';
}

void MainWindow::on_pushButton_DUT_SRAM_Write_clicked()
{
    QString str = "A"; // Write data to memory (DUT)
    uart_fpga_writeData(str.toLocal8Bit());
    flag_data_pattern = 0b10101010;
    flag_kind_ER = 'W';
}
