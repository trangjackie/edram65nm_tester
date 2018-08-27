#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QDateTime>


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

    // UART FPGA
    uart_power_setting = new SettingsDialog;
    uart_power_setting->setdefault(1,0);
    uart_power = new QSerialPort(this);
    connect(uart_power, SIGNAL(error(QSerialPort::SerialPortError)), this,
            SLOT(uart_power_handleError(QSerialPort::SerialPortError)));
    connect(uart_power, SIGNAL(readyRead()), this, SLOT(uart_power_readData()));

    // Timer for TID auto test
        timer_tid = new QTimer();
        //connect(timer_tid, SIGNAL(timeout()), this, SLOT(tid_check()));
    // DUT databbbbcvnbcvbn
    raw_data = new dut_data;
    ba_SIPO_setdata = new QBitArray(48);
    //
    SIPOCheckbox_setup();
    onSIPOCheckbox_change();

}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
 * setup signals for checkbox
 */
void MainWindow::SIPOCheckbox_setup()
{
    connect(ui->cb_b0, SIGNAL(stateChanged(int)), this, SLOT(onSIPOCheckbox_change()));
    connect(ui->cb_b1, SIGNAL(stateChanged(int)), this, SLOT(onSIPOCheckbox_change()));
    connect(ui->cb_b2, SIGNAL(stateChanged(int)), this, SLOT(onSIPOCheckbox_change()));
    connect(ui->cb_b3, SIGNAL(stateChanged(int)), this, SLOT(onSIPOCheckbox_change()));
    connect(ui->cb_b4, SIGNAL(stateChanged(int)), this, SLOT(onSIPOCheckbox_change()));
    connect(ui->cb_b5, SIGNAL(stateChanged(int)), this, SLOT(onSIPOCheckbox_change()));
    connect(ui->cb_b6, SIGNAL(stateChanged(int)), this, SLOT(onSIPOCheckbox_change()));
    connect(ui->cb_b7, SIGNAL(stateChanged(int)), this, SLOT(onSIPOCheckbox_change()));
    connect(ui->cb_b8, SIGNAL(stateChanged(int)), this, SLOT(onSIPOCheckbox_change()));
    connect(ui->cb_b9, SIGNAL(stateChanged(int)), this, SLOT(onSIPOCheckbox_change()));
    connect(ui->cb_b10, SIGNAL(stateChanged(int)), this, SLOT(onSIPOCheckbox_change()));
    connect(ui->cb_b11, SIGNAL(stateChanged(int)), this, SLOT(onSIPOCheckbox_change()));
    connect(ui->cb_b12, SIGNAL(stateChanged(int)), this, SLOT(onSIPOCheckbox_change()));
    connect(ui->cb_b13, SIGNAL(stateChanged(int)), this, SLOT(onSIPOCheckbox_change()));
    connect(ui->cb_b14, SIGNAL(stateChanged(int)), this, SLOT(onSIPOCheckbox_change()));
    connect(ui->cb_b15, SIGNAL(stateChanged(int)), this, SLOT(onSIPOCheckbox_change()));
    connect(ui->cb_b16, SIGNAL(stateChanged(int)), this, SLOT(onSIPOCheckbox_change()));
    connect(ui->cb_b17, SIGNAL(stateChanged(int)), this, SLOT(onSIPOCheckbox_change()));
    connect(ui->cb_b18, SIGNAL(stateChanged(int)), this, SLOT(onSIPOCheckbox_change()));
    connect(ui->cb_b19, SIGNAL(stateChanged(int)), this, SLOT(onSIPOCheckbox_change()));
    connect(ui->cb_b20, SIGNAL(stateChanged(int)), this, SLOT(onSIPOCheckbox_change()));
    connect(ui->cb_b21, SIGNAL(stateChanged(int)), this, SLOT(onSIPOCheckbox_change()));
    connect(ui->cb_b22, SIGNAL(stateChanged(int)), this, SLOT(onSIPOCheckbox_change()));
    connect(ui->cb_b23, SIGNAL(stateChanged(int)), this, SLOT(onSIPOCheckbox_change()));
    connect(ui->cb_b24, SIGNAL(stateChanged(int)), this, SLOT(onSIPOCheckbox_change()));
    connect(ui->cb_b25, SIGNAL(stateChanged(int)), this, SLOT(onSIPOCheckbox_change()));
    connect(ui->cb_b26, SIGNAL(stateChanged(int)), this, SLOT(onSIPOCheckbox_change()));
    connect(ui->cb_b27, SIGNAL(stateChanged(int)), this, SLOT(onSIPOCheckbox_change()));
    connect(ui->cb_b28, SIGNAL(stateChanged(int)), this, SLOT(onSIPOCheckbox_change()));
    connect(ui->cb_b29, SIGNAL(stateChanged(int)), this, SLOT(onSIPOCheckbox_change()));
    connect(ui->cb_b30, SIGNAL(stateChanged(int)), this, SLOT(onSIPOCheckbox_change()));
    connect(ui->cb_b31, SIGNAL(stateChanged(int)), this, SLOT(onSIPOCheckbox_change()));
    connect(ui->cb_b32, SIGNAL(stateChanged(int)), this, SLOT(onSIPOCheckbox_change()));
    connect(ui->cb_b33, SIGNAL(stateChanged(int)), this, SLOT(onSIPOCheckbox_change()));
    connect(ui->cb_b34, SIGNAL(stateChanged(int)), this, SLOT(onSIPOCheckbox_change()));
    connect(ui->cb_b35, SIGNAL(stateChanged(int)), this, SLOT(onSIPOCheckbox_change()));
    connect(ui->cb_b36, SIGNAL(stateChanged(int)), this, SLOT(onSIPOCheckbox_change()));
    connect(ui->cb_b37, SIGNAL(stateChanged(int)), this, SLOT(onSIPOCheckbox_change()));
    connect(ui->cb_b38, SIGNAL(stateChanged(int)), this, SLOT(onSIPOCheckbox_change()));

}
void MainWindow::onSIPOCheckbox_change()
{
    QString st_SIPO_setdata;
    QByteArray bytes;
    int i;
    ba_SIPO_setdata->setBit(0, ui->cb_b0->isChecked());
    ba_SIPO_setdata->setBit(1, ui->cb_b1->isChecked());
    ba_SIPO_setdata->setBit(2, ui->cb_b2->isChecked());
    ba_SIPO_setdata->setBit(3, ui->cb_b3->isChecked());
    ba_SIPO_setdata->setBit(4, ui->cb_b4->isChecked());
    ba_SIPO_setdata->setBit(5, ui->cb_b5->isChecked());
    ba_SIPO_setdata->setBit(6, ui->cb_b6->isChecked());
    ba_SIPO_setdata->setBit(7, ui->cb_b7->isChecked());
    ba_SIPO_setdata->setBit(8, ui->cb_b8->isChecked());
    ba_SIPO_setdata->setBit(9, ui->cb_b9->isChecked());
    ba_SIPO_setdata->setBit(10, ui->cb_b10->isChecked());
    ba_SIPO_setdata->setBit(11, ui->cb_b11->isChecked());
    ba_SIPO_setdata->setBit(12, ui->cb_b12->isChecked());
    ba_SIPO_setdata->setBit(13, ui->cb_b13->isChecked());
    ba_SIPO_setdata->setBit(14, ui->cb_b14->isChecked());
    ba_SIPO_setdata->setBit(15, ui->cb_b15->isChecked());
    ba_SIPO_setdata->setBit(16, ui->cb_b16->isChecked());
    ba_SIPO_setdata->setBit(17, ui->cb_b17->isChecked());
    ba_SIPO_setdata->setBit(18, ui->cb_b18->isChecked());
    ba_SIPO_setdata->setBit(19, ui->cb_b19->isChecked());
    ba_SIPO_setdata->setBit(20, ui->cb_b20->isChecked());
    ba_SIPO_setdata->setBit(21, ui->cb_b21->isChecked());
    ba_SIPO_setdata->setBit(22, ui->cb_b22->isChecked());
    ba_SIPO_setdata->setBit(23, ui->cb_b23->isChecked());
    ba_SIPO_setdata->setBit(24, ui->cb_b24->isChecked());
    ba_SIPO_setdata->setBit(25, ui->cb_b25->isChecked());
    ba_SIPO_setdata->setBit(26, ui->cb_b26->isChecked());
    ba_SIPO_setdata->setBit(27, ui->cb_b27->isChecked());
    ba_SIPO_setdata->setBit(28, ui->cb_b28->isChecked());
    ba_SIPO_setdata->setBit(29, ui->cb_b29->isChecked());
    ba_SIPO_setdata->setBit(30, ui->cb_b30->isChecked());
    ba_SIPO_setdata->setBit(31, ui->cb_b31->isChecked());
    ba_SIPO_setdata->setBit(32, ui->cb_b32->isChecked());
    ba_SIPO_setdata->setBit(33, ui->cb_b33->isChecked());
    ba_SIPO_setdata->setBit(34, ui->cb_b34->isChecked());
    ba_SIPO_setdata->setBit(35, ui->cb_b35->isChecked());
    ba_SIPO_setdata->setBit(36, ui->cb_b36->isChecked());
    ba_SIPO_setdata->setBit(37, ui->cb_b37->isChecked());
    for (i=38;i<48;i++){
        ba_SIPO_setdata->setBit(i, ui->cb_b38->isChecked());
    }

    // convert bitarray to binary string
    for (i=0;i<ba_SIPO_setdata->size();i++){
        if ((i%8)==0) st_SIPO_setdata.prepend(" ");
        if (ba_SIPO_setdata->testBit(i)) st_SIPO_setdata.prepend("1");
        else st_SIPO_setdata.prepend("0");
    }
    // convert bitarray to hex string hhhh
    //bytes = my_bitsToBytes(ba_SIPO_setdata);
    //st_SIPO_setdata.append(" = ");
    //st_SIPO_setdata.append(bytes.toHex());
    ui->lineEdit_SIPO_setdata->setText(st_SIPO_setdata);

}
QByteArray MainWindow::my_bitsToBytes(QBitArray* bits) {
    QByteArray bytes;
    bytes.resize(bits->count()/8);
    bytes.fill(0);
    // Convert from QBitArray to QByteArray
    for(int b=0; b<bits->count(); ++b)
        bytes[b/8] = ( bytes.at(b/8) | ((bits->testBit(b)?1:0)<<(b%8)));
    return bytes;
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
    char cdata_org, cdata_rb ,cmask, cdata_pt;
    bool b_cell_org, b_cell_rb;
    char type_data;
    bool ok = true;
    int i;
    int datasize;
    raw_data->raw_data->clear();
    raw_data->raw_data->append(uart_fpga->readAll());
    //qDebug("data come 0");
    while (uart_fpga->waitForReadyRead(200)){
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
    type_data = raw_data->data_classify();
    if (type_data == FPGA_SIPO_CONFIG){
        ui->lineEdit_SIPO_verifydata->setText(raw_data->raw_data->toHex());

    }
    if ((type_data == FPGA_S12_READ)
            |(type_data == FPGA_S6_READ)
            |(type_data == FPGA_SEND_TEST_CHAR)
            |(type_data == FPGA_E2_WRITE)
            |(type_data == FPGA_E1_WRITE)){
        if (raw_data->data_avarible)
        {
            QImage img(128, 256, QImage::Format_RGB888);
            img.fill(QColor(Qt::white).rgb());
            raw_data->convert_data_to_image(&img,raw_data->sram_data);
            ui->label_bitmap->setPixmap(QPixmap::fromImage(img));
            int i_refeshtime = ui->lineEdit_refeshtime->text().toUInt(&ok,10);
            int i_repeatwrite = ui->lineEdit_write_times->text().toUInt(&ok,10);
            bool b_original = true;
            if ((i_refeshtime+i_repeatwrite)>0) b_original = false;
            else b_original = true;

            for (int x = 0; x < 16; x++) {
                for (int y = 0; y < 256; y++) //,
                {
                    if ((y%2==1)){
                        cdata_pt = ui->lineEdit_DUT_data1->text().toUInt(&ok,16);
                    } else {
                        cdata_pt = ui->lineEdit_DUT_data2->text().toUInt(&ok,16);
                    }
                    if ((x*256+y)<=(raw_data->sram_data->size()-1)){
                        cdata_org = raw_data->sram_data->at(x*256+y);

                    }
                    else {
                        cdata_org = 0;
                    }
                    cmask = 0x01;
                    for (int b = 0; b<8;b++)
                    {
                        if ((cdata_org&cmask)==cmask)
                        {
//                            if (b_original) {
//                                b_array_org[x*8+b][y] = true;
//                            } else {
//                                b_array_rb[x*8+b][y] = true;
//                            }
                             b_array_rb[x*8+b][y] = true;
                        }
                        else
                        {
//                            if (b_original) {
//                                b_array_org[x*8+b][y] = false;
//                            } else {
//                                b_array_rb[x*8+b][y] = false;
//                            }
                            b_array_rb[x*8+b][y] = false;
                        }
                        if ((cdata_pt&cmask)==cmask){
                            b_array_pt[x*8+b][y] = true;
                        } else {
                            b_array_pt[x*8+b][y] = false;
                        }
                        cmask = cmask<<1;
                    }
                }
            }


            // canculate error rate
            i_write_error_0 = 0;
            i_write_error_1 = 0;
            i_retension_error_0 = 0;
            i_retension_error_1 = 0;
            if (b_original){
                i_write_error_0 = 0;
                i_write_error_1 = 0;
                for (int x = 0; x < 128; x++) {
                    for (int y = 0; y < 255; y++) // except the test SA row (255th)
                    {
                        if (b_array_rb[x][y]!=b_array_pt[x][y]){
                            if (b_array_pt[x][y]==0){
                                i_write_error_0 +=1;
                            }else {
                                i_write_error_1 +=1;
                            }
                        }
                    }
                }
            } else {
                i_retension_error_0 = 0;
                i_retension_error_1 = 0;
                for (int x = 0; x < 128; x++) {
                    for (int y = 0; y < 255; y++) // do not compare the 255th row
                    {
                        if (b_array_pt[x][y]!=b_array_rb[x][y]){
                            if (b_array_pt[x][y]==0){
                                i_retension_error_0 +=1;
                            }else {
                                i_retension_error_1 +=1;
                            }
                        }
                    }
                }
            }
            // show error number
            ui->label_RetensionER0->setText("TER0="+QString::number(i_retension_error_0,10));
            ui->label_RetensionER1->setText("TER1="+QString::number(i_retension_error_1,10));
            ui->label_WriteER0->setText("WER0="+QString::number(i_write_error_0,10));
            ui->label_WriteER1->setText("WER1="+QString::number(i_write_error_1,10));
        }
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
/*
void MainWindow::on_pushButton_DUT_SRAM_Read_clicked()
{
    QString str = "U"; // Read all data from memory (DUT)
    uart_fpga_writeData(str.toLocal8Bit());
    flag_kind_ER = 'R';
}

void MainWindow::on_pushButton_TID_check_clicked()
{
    if (ui->lineEdit_timer->text().isEmpty()){
        //tid_check();
    } else {
    if (timer_tid->isActive())
        {
            timer_tid->stop();
        }
        else
        {
            // get timer time set
            int t;
            bool bOk;
            t= ui->lineEdit_timer->text().toInt(&bOk);
            if (!bOk|(t<10))
            {
                t = 10;
            }
            flag_kind_ER = 't';
            // Start counter
            timer_tid->start(t*1000);
        }
    }

}
*/


void MainWindow::write_report(QString st_data)
{
    QString filename = "eDRAM_Log_"+ui->lineEdit_chipname->text()+".txt";
    QString st_time = get_time_string();
    QFile file( filename );
    QFileInfo check_file(filename);
    // check if file exists and if yes: Is it really a file and no directory?
    if (check_file.exists() && check_file.isFile()) { // add more data to file
        if (file.open(QFile::Append))
        {
                QTextStream stream(&file);
                stream << st_time+" "+st_data+"\n" << endl;
        }
    } else { // open new file
        if ( file.open(QIODevice::ReadWrite) )
        {
            QTextStream stream( &file );
            stream << st_time+" "+st_data << endl;
        }
    }
    file.close();
}
QString MainWindow::get_time_string()
{
    QString fmt = "yyyyMMddhhmmss";
    QString timeStr = QDateTime::currentDateTime().toString(fmt);

    return timeStr;
}

void MainWindow::on_pushButton_DUT_SIPO_set_clicked()
{
    QString str;
    QByteArray payload;
    QByteArray setdata;
    setdata = my_bitsToBytes(ba_SIPO_setdata);

    payload.resize(8);
    payload[0]=8;
    payload[1]=FPGA_SIPO_CONFIG;
    payload[2]=setdata[0];
    payload[3]=setdata[1];
    payload[4]=setdata[2];
    payload[5]=setdata[3];
    payload[6]=setdata[4];
    payload[7]=setdata[5];

    str = ui->lineEdit_SIPO_setdata->text();
    str.append(" = ");
    str.append(payload.toHex());
    ui->lineEdit_SIPO_setdata->setText(str);

    uart_fpga_writeData(payload);
}

void MainWindow::on_pushButton_TestChar_clicked()
{
    QByteArray payload;
    payload.resize(2);
    payload[0]=2;
    payload[1]=FPGA_SEND_TEST_CHAR;

    uart_fpga_writeData(payload);
}


void MainWindow::on_pushButton_DUT_S12_Read_clicked()
{
    bool bStatus = false;
    QString str_write_repeat = ui->lineEdit_write_repeat->text();
    QByteArray payload;
    uint nWriterepeat = str_write_repeat.toUInt(&bStatus,10);
    QByteArray baWriterepeat;
    baWriterepeat[0] = nWriterepeat;
    baWriterepeat[1] = nWriterepeat>>8;
    baWriterepeat[2] = nWriterepeat>>16;
    baWriterepeat[3] = nWriterepeat>>24;

    payload.resize(7);
    payload[0]=7;
    payload[1]=FPGA_S12_READ;
    payload[2] = 0;
    if (ui->checkBox_Readrepeat->isChecked()){
        char mask = 1;
        mask = mask << 2;
        payload[2] = payload[2]|mask;
    }
    if (ui->checkBox_Writerepeat->isChecked()){
        char mask = 1;
        mask = mask << 3;
        payload[2] = payload[2]|mask;
    }
    if (ui->checkBox_Allrepeat->isChecked()){
        char mask = 1;
        mask = mask << 4;
        payload[2] = payload[2]|mask;
    }

    for (int i=0;i<baWriterepeat.size();i++){
        payload[3+i] = baWriterepeat[baWriterepeat.size()-i-1];
    }


    qDebug("payload "+ payload.toHex());
    uart_fpga_writeData(payload);
}

void MainWindow::on_pushButton_DUT_S12_Write_clicked()
{
    QByteArray payload;
    QString str_data1 = ui->lineEdit_DUT_data1->text();
    QString str_data2 = ui->lineEdit_DUT_data2->text();
    QString str_col = ui->lineEdit_DUT_Col->text();
    QString str_row = ui->lineEdit_DUT_Row->text();
    QString str_write_repeat = ui->lineEdit_write_repeat->text();

    bool bStatus = false;
    uint nCol = str_col.toUInt(&bStatus,16);
    uint nRow = str_row.toUInt(&bStatus,16);
    uint nData1 = str_data1.toUInt(&bStatus,16);
    uint nData2 = str_data2.toUInt(&bStatus,16);
    uint nWriterepeat = str_write_repeat.toUInt(&bStatus,10);
    QByteArray baWriterepeat;
    baWriterepeat[0] = nWriterepeat;
    baWriterepeat[1] = nWriterepeat>>8;
    baWriterepeat[2] = nWriterepeat>>16;
    baWriterepeat[3] = nWriterepeat>>24;

    payload.resize(11);
    payload[0]=11;
    payload[1]=FPGA_S12_WRITE;
    if (ui->checkBox_DUT_WriteOne->isChecked()){
        payload[2] = 1;
    } else {
        payload[2] = 0;
    }
    if (ui->checkBox_Readrepeat->isChecked()){
        char mask = 1;
        mask = mask << 2;
        payload[2] = payload[2]|mask;
    }
    if (ui->checkBox_Writerepeat->isChecked()){
        char mask = 1;
        mask = mask << 3;
        payload[2] = payload[2]|mask;
    }
    if (ui->checkBox_Allrepeat->isChecked()){
        char mask = 1;
        mask = mask << 4;
        payload[2] = payload[2]|mask;
    }
    payload[3]= nCol; // col addr 4bit
    payload[4]= nRow;
    payload[5]= nData1;
    payload[6]= nData2;
    for (int i=0;i<baWriterepeat.size();i++){
        payload[7+i] = baWriterepeat[baWriterepeat.size()-i-1];
    }
    qDebug("payload "+ payload.toHex());
    uart_fpga_writeData(payload);
}



void MainWindow::on_pushButton_DUT_eDRAM1_Write_clicked()
{
    QByteArray payload;
    QString str_data1 = ui->lineEdit_DUT_data1->text();
    QString str_data2 = ui->lineEdit_DUT_data2->text();
    QString str_col = ui->lineEdit_DUT_Col->text();
    QString str_row = ui->lineEdit_DUT_Row->text();
    QString str_refesh = ui->lineEdit_refeshtime->text();
    QString str_write_repeat = ui->lineEdit_write_repeat->text();
    QString str_repeat = ui->lineEdit_write_times->text();
    bool bStatus = false;
    uint nCol = str_col.toUInt(&bStatus,16);
    uint nRow = str_row.toUInt(&bStatus,16);
    uint nData1 = str_data1.toUInt(&bStatus,16);
    uint nData2 = str_data2.toUInt(&bStatus,16);
    uint nRefesh = str_refesh.toUInt(&bStatus,10);
    uint nWriterepeat = str_write_repeat.toUInt(&bStatus,10);
     uint nRepeat = str_repeat.toUInt(&bStatus,10);
    QByteArray baRefesh;
    QByteArray baWriterepeat;
    QByteArray baNextrepeat;
    baNextrepeat[0]=nRepeat;
    baNextrepeat[1]=nRepeat>>8;
    baNextrepeat[2]=nRepeat>>16;
    baNextrepeat[3]=nRepeat>>24;
    baRefesh[0]=nRefesh;
    baRefesh[1]=nRefesh>>8;
    baRefesh[2]=nRefesh>>16;
    baRefesh[3]=nRefesh>>24;
    qDebug("refesh "+baRefesh);
    qDebug("number %d",nRefesh);

    baWriterepeat[0] = nWriterepeat;
    baWriterepeat[1] = nWriterepeat>>8;
    baWriterepeat[2] = nWriterepeat>>16;
    baWriterepeat[3] = nWriterepeat>>24;

    payload.resize(19);
    payload.fill(0);
    payload[0]=19;
    payload[1]=FPGA_E1_WRITE;
    if (ui->checkBox_DUT_WriteOne->isChecked()){
        payload[2] = 1;
    } else {
        payload[2] = 0;
    }

    if (ui->checkBox_Readrepeat->isChecked()){
        char mask = 1;
        mask = mask << 2;
        payload[2] = payload[2]|mask;
    }
    if (ui->checkBox_Writerepeat->isChecked()){
        char mask = 1;
        mask = mask << 3;
        payload[2] = payload[2]|mask;
    }
    if (ui->checkBox_Allrepeat->isChecked()){
        char mask = 1;
        mask = mask << 4;
        payload[2] = payload[2]|mask;
    }
    payload[3]= nCol; // col addr 4bit
    payload[4]= nRow;
    payload[5]= nData1;
    payload[6]= nData2;

    for (int i=0;i<baRefesh.size();i++){
        payload[7+i] = baRefesh[baRefesh.size()-i-1];
    }
    //payload[11]= nRepeat;
    for (int i=0;i<baNextrepeat.size();i++){
        payload[11+i] = baNextrepeat[baNextrepeat.size()-i-1];
    }
    for (int i=0;i<baWriterepeat.size();i++){
        payload[15+i] = baWriterepeat[baWriterepeat.size()-i-1];
    }
    qDebug("payload "+ payload.toHex());
    uart_fpga_writeData(payload);
}

void MainWindow::on_pushButton_DUT_eDRAM2_Write_clicked()
{
    QByteArray payload;
    QString str_data1 = ui->lineEdit_DUT_data1->text();
    QString str_data2 = ui->lineEdit_DUT_data2->text();
    QString str_col = ui->lineEdit_DUT_Col->text();
    QString str_row = ui->lineEdit_DUT_Row->text();
    QString str_refesh = ui->lineEdit_refeshtime->text();
    QString str_write_repeat = ui->lineEdit_write_repeat->text();
    QString str_repeat = ui->lineEdit_write_times->text();
    bool bStatus = false;
    uint nCol = str_col.toUInt(&bStatus,16);
    uint nRow = str_row.toUInt(&bStatus,16);
    uint nData1 = str_data1.toUInt(&bStatus,16);
    uint nData2 = str_data2.toUInt(&bStatus,16);
    uint nRefesh = str_refesh.toUInt(&bStatus,10);
    uint nWriterepeat = str_write_repeat.toUInt(&bStatus,10);
    uint nRepeat = str_repeat.toUInt(&bStatus,10);
    QByteArray baRefesh;
    QByteArray baWriterepeat;
    QByteArray baNextrepeat;
    baNextrepeat[0]=nRepeat;
    baNextrepeat[1]=nRepeat>>8;
    baNextrepeat[2]=nRepeat>>16;
    baNextrepeat[3]=nRepeat>>24;
    baRefesh[0]=nRefesh;
    baRefesh[1]=nRefesh>>8;
    baRefesh[2]=nRefesh>>16;
    baRefesh[3]=nRefesh>>24;
    qDebug("refesh "+baRefesh);
    qDebug("number %d",nRefesh);

    baWriterepeat[0] = nWriterepeat;
    baWriterepeat[1] = nWriterepeat>>8;
    baWriterepeat[2] = nWriterepeat>>16;
    baWriterepeat[3] = nWriterepeat>>24;

    payload.resize(19);
    payload.fill(0);
    payload[0]=19;
    payload[1]=FPGA_E2_WRITE;
    if (ui->checkBox_DUT_WriteOne->isChecked()){
        payload[2] = 1;
    } else {
        payload[2] = 0;
    }
    if (ui->checkBox_Readrepeat->isChecked()){
        char mask = 1;
        mask = mask << 2;
        payload[2] = payload[2]|mask;
    }
    if (ui->checkBox_Writerepeat->isChecked()){
        char mask = 1;
        mask = mask << 3;
        payload[2] = payload[2]|mask;
    }
    if (ui->checkBox_Allrepeat->isChecked()){
        char mask = 1;
        mask = mask << 4;
        payload[2] = payload[2]|mask;
    }
    payload[3]= nCol; // col addr 4bit
    payload[4]= nRow;
    payload[5]= nData1;
    payload[6]= nData2;

    for (int i=0;i<baRefesh.size();i++){
        payload[7+i] = baRefesh[baRefesh.size()-i-1];
    }
    //payload[11]= nRepeat;
    for (int i=0;i<baNextrepeat.size();i++){
        payload[11+i] = baNextrepeat[baNextrepeat.size()-i-1];
    }
    for (int i=0;i<baWriterepeat.size();i++){
        payload[15+i] = baWriterepeat[baWriterepeat.size()-i-1];
    }
    qDebug("payload "+ payload.toHex());
    uart_fpga_writeData(payload);
}

void MainWindow::on_pushButton_DUT_eDRAM1_WriteReadNextCell_clicked()
{
    QByteArray payload;
    QString str_data1 = ui->lineEdit_DUT_data1->text();
    QString str_data2 = ui->lineEdit_DUT_data2->text();
    QString str_col = ui->lineEdit_DUT_Col->text();
    QString str_row = ui->lineEdit_DUT_Row->text();
    QString str_refesh = ui->lineEdit_refeshtime->text();
    QString str_repeat = ui->lineEdit_write_times->text();
    QString str_write_repeat = ui->lineEdit_write_repeat->text();
    bool bStatus = false;
    uint nCol = str_col.toUInt(&bStatus,16);
    uint nRow = str_row.toUInt(&bStatus,16);
    uint nData1 = str_data1.toUInt(&bStatus,16);
    uint nData2 = str_data2.toUInt(&bStatus,16);
    uint nRefesh = str_refesh.toUInt(&bStatus,10);
    uint nRepeat = str_repeat.toUInt(&bStatus,10);
    uint nWriterepeat = str_write_repeat.toUInt(&bStatus,10);
    QByteArray baRefesh;
    QByteArray baWriterepeat;
    QByteArray baNextrepeat;
    baNextrepeat[0]=nRepeat;
    baNextrepeat[1]=nRepeat>>8;
    baNextrepeat[2]=nRepeat>>16;
    baNextrepeat[3]=nRepeat>>24;


    baRefesh[0]=nRefesh;
    baRefesh[1]=nRefesh>>8;
    baRefesh[2]=nRefesh>>16;
    baRefesh[3]=nRefesh>>24;
    qDebug("refesh "+baRefesh);
    qDebug("number %d",nRefesh);
    baWriterepeat[0] = nWriterepeat;
    baWriterepeat[1] = nWriterepeat>>8;
    baWriterepeat[2] = nWriterepeat>>16;
    baWriterepeat[3] = nWriterepeat>>24;

    payload.resize(19);
    payload.fill(0);
    payload[0]=19;
    payload[1]=FPGA_E1_WRITE;
    if (ui->checkBox_dummy_data_pattern->isChecked()){
        if (ui->checkBox_DUT_WriteOne->isChecked()){
            payload[2] = 3; // 8b 0000 0011
        } else {
            payload[2] = 2; // 8b 0000 0010
        }
    } else {
        if (ui->checkBox_DUT_WriteOne->isChecked()){
            payload[2] = 1; // 8b 0000 0001
        } else {
            payload[2] = 0; // 8b 0000 0000
        }
    }
    if (ui->checkBox_Readrepeat->isChecked()){
        char mask = 1;
        mask = mask << 2;
        payload[2] = payload[2]|mask;
    }
    if (ui->checkBox_Writerepeat->isChecked()){
        char mask = 1;
        mask = mask << 3;
        payload[2] = payload[2]|mask;
    }
    if (ui->checkBox_Allrepeat->isChecked()){
        char mask = 1;
        mask = mask << 4;
        payload[2] = payload[2]|mask;
    }
    payload[3]= nCol; // col addr 4bit
    payload[4]= nRow;
    payload[5]= nData1;
    payload[6]= nData2;

    for (int i=0;i<baRefesh.size();i++){
        payload[7+i] = baRefesh[baRefesh.size()-i-1];
    }
    //payload[11]= nRepeat;
    for (int i=0;i<baNextrepeat.size();i++){
        payload[11+i] = baNextrepeat[baNextrepeat.size()-i-1];
    }
    for (int i=0;i<baWriterepeat.size();i++){
        payload[15+i] = baWriterepeat[baWriterepeat.size()-i-1];
    }
    qDebug("payload "+ payload.toHex());
    uart_fpga_writeData(payload);
}

void MainWindow::on_pushButton_clicked()
{
    QByteArray payload;
    QString str_data1 = ui->lineEdit_DUT_data1->text();
    QString str_data2 = ui->lineEdit_DUT_data2->text();
    QString str_col = ui->lineEdit_DUT_Col->text();
    QString str_row = ui->lineEdit_DUT_Row->text();
    QString str_refesh = ui->lineEdit_refeshtime->text();
    QString str_repeat = ui->lineEdit_write_times->text();
    QString str_write_repeat = ui->lineEdit_write_repeat->text();
    bool bStatus = false;
    uint nCol = str_col.toUInt(&bStatus,16);
    uint nRow = str_row.toUInt(&bStatus,16);
    uint nData1 = str_data1.toUInt(&bStatus,16);
    uint nData2 = str_data2.toUInt(&bStatus,16);
    uint nRefesh = str_refesh.toUInt(&bStatus,10);
    uint nRepeat = str_repeat.toUInt(&bStatus,10);
    uint nWriterepeat = str_write_repeat.toUInt(&bStatus,10);
    QByteArray baRefesh;
    QByteArray baWriterepeat;
    QByteArray baNextrepeat;
    baNextrepeat[0]=nRepeat;
    baNextrepeat[1]=nRepeat>>8;
    baNextrepeat[2]=nRepeat>>16;
    baNextrepeat[3]=nRepeat>>24;
    baRefesh[0]=nRefesh;
    baRefesh[1]=nRefesh>>8;
    baRefesh[2]=nRefesh>>16;
    baRefesh[3]=nRefesh>>24;
    qDebug("refesh "+baRefesh);
    qDebug("number %d",nRefesh);
    baWriterepeat[0] = nWriterepeat;
    baWriterepeat[1] = nWriterepeat>>8;
    baWriterepeat[2] = nWriterepeat>>16;
    baWriterepeat[3] = nWriterepeat>>24;
    payload.resize(19);
    payload.fill(0);
    payload[0]=19;
    payload[1]=FPGA_E2_WRITE;
    if (ui->checkBox_dummy_data_pattern->isChecked()){
        if (ui->checkBox_DUT_WriteOne->isChecked()){
            payload[2] = 3; // 8b 0000 0011
        } else {
            payload[2] = 2; // 8b 0000 0010
        }
    } else {
        if (ui->checkBox_DUT_WriteOne->isChecked()){
            payload[2] = 1; // 8b 0000 0001
        } else {
            payload[2] = 0; // 8b 0000 0000
        }
    }
    if (ui->checkBox_Readrepeat->isChecked()){
        char mask = 1;
        mask = mask << 2;
        payload[2] = payload[2]|mask;
    }
    if (ui->checkBox_Writerepeat->isChecked()){
        char mask = 1;
        mask = mask << 3;
        payload[2] = payload[2]|mask;
    }
    if (ui->checkBox_Allrepeat->isChecked()){
        char mask = 1;
        mask = mask << 4;
        payload[2] = payload[2]|mask;
    }
    payload[3]= nCol; // col addr 4bit
    payload[4]= nRow;
    payload[5]= nData1;
    payload[6]= nData2;

    for (int i=0;i<baRefesh.size();i++){
        payload[7+i] = baRefesh[baRefesh.size()-i-1];
    }
    //payload[11]= nRepeat;
    for (int i=0;i<baNextrepeat.size();i++){
        payload[11+i] = baNextrepeat[baNextrepeat.size()-i-1];
    }
    for (int i=0;i<baWriterepeat.size();i++){
        payload[15+i] = baWriterepeat[baWriterepeat.size()-i-1];
    }
    qDebug("payload "+ payload.toHex());
    uart_fpga_writeData(payload);
}

void MainWindow::on_pushButton_HVDD_clicked()
{
    double vdd;
    QString str;
    vdd = ui->lineEdit_HVDD->text().toDouble();
    if (vdd > 2.5){
        vdd = 2.5;
    } else if (vdd<0){
        vdd = 0;
    }
    str = "VSET1:"+QString::number(vdd,'f',3)+"\n";
    uart_power_writeData(str.toLocal8Bit());
}

void MainWindow::on_pushButton_NVSS_clicked()
{
    double vdd;
    QString str;
    vdd = ui->lineEdit_NVSS->text().toDouble();
    if (vdd<0) {
       vdd = -vdd;
    }
    if (vdd > 1.5){
        vdd = 1.5;
    }
    str = "VSET2:"+QString::number(vdd,'f',3)+"\n";
    uart_power_writeData(str.toLocal8Bit());
}

void MainWindow::on_pushButton_power_on_clicked()
{
    QString str = "OUT1\n"; // output  on
    uart_power_writeData(str.toLocal8Bit());
    ui->pushButton_power_on->setEnabled(false);
    ui->pushButton_power_off->setEnabled(true);
}

void MainWindow::on_pushButton_power_off_clicked()
{
    QString str = "OUT0\n"; // output  off
    uart_power_writeData(str.toLocal8Bit());
    ui->pushButton_power_on->setEnabled(true);
    ui->pushButton_power_off->setEnabled(false);
}

void MainWindow::on_pushButton_uart_power_setting_clicked()
{
    uart_power_setting->show();
}

void MainWindow::on_pushButton_uart_power_connect_clicked()
{
    if (ui->pushButton_uart_power_connect->text()=="Connect") // have not connected
    {
        SettingsDialog::Settings p = uart_power_setting->settings();
        uart_power->setPortName(p.name);
        uart_power->setBaudRate(p.baudRate);
        uart_power->setDataBits(p.dataBits);
        uart_power->setParity(p.parity);
        uart_power->setStopBits(p.stopBits);
        uart_power->setFlowControl(p.flowControl);
        if (uart_power->open(QIODevice::ReadWrite)) {
            ui->pushButton_uart_power_connect->setToolTip("Click to disconnect UART.");
            ui->pushButton_uart_power_connect->setText("Disconnect");
            ui->pushButton_uart_power_setting->setEnabled(false);
            ui->statusBar->showMessage(QString("Connected to %1 : %2, %3, %4, %5, %6")
                              .arg(p.name).arg(p.stringBaudRate).arg(p.stringDataBits)
                              .arg(p.stringParity).arg(p.stringStopBits).arg(p.stringFlowControl));
        } else {
            QMessageBox::critical(this, tr("Error"), uart_power->errorString());
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
            if (uart_power->isOpen())
                uart_power->close();
            //console->setEnabled(false);
            ui->pushButton_uart_power_connect->setText("Connect");
            ui->pushButton_uart_power_connect->setToolTip("Click to connect UART.");
            ui->pushButton_uart_power_setting->setEnabled(true);
            ui->statusBar->showMessage("UART power disconnected");
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

void MainWindow::uart_power_readData()
{
    uart_power_rxdata = uart_fpga->readAll();
    qDebug("Data successfully received from port "+uart_power->portName().toLatin1());
    ui->plainTextEdit_console->clear();
    ui->plainTextEdit_console->insertPlainText(QString(uart_power_rxdata));
}

void MainWindow::uart_power_writeData(const QByteArray &data)
{
    uart_power->write(data);
}

void MainWindow::uart_power_handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
    QMessageBox::critical(this, QString("Critical Error"), uart_power->errorString());
    }
}

void MainWindow::on_lineEdit_write_repeat_editingFinished()
{

}

void MainWindow::on_pushButton_DUT_S6_Write_clicked()
{
    QByteArray payload;
    QString str_data1 = ui->lineEdit_DUT_data1->text();
    QString str_data2 = ui->lineEdit_DUT_data2->text();
    QString str_col = ui->lineEdit_DUT_Col->text();
    QString str_row = ui->lineEdit_DUT_Row->text();
    QString str_write_repeat = ui->lineEdit_write_repeat->text();

    bool bStatus = false;
    uint nCol = str_col.toUInt(&bStatus,16);
    uint nRow = str_row.toUInt(&bStatus,16);
    uint nData1 = str_data1.toUInt(&bStatus,16);
    uint nData2 = str_data2.toUInt(&bStatus,16);
    uint nWriterepeat = str_write_repeat.toUInt(&bStatus,10);
    QByteArray baWriterepeat;
    baWriterepeat[0] = nWriterepeat;
    baWriterepeat[1] = nWriterepeat>>8;
    baWriterepeat[2] = nWriterepeat>>16;
    baWriterepeat[3] = nWriterepeat>>24;

    payload.resize(11);
    payload[0]=11;
    payload[1]=FPGA_S6_WRITE;
    if (ui->checkBox_DUT_WriteOne->isChecked()){
        payload[2] = 1;
    } else {
        payload[2] = 0;
    }
    if (ui->checkBox_Readrepeat->isChecked()){
        char mask = 1;
        mask = mask << 2;
        payload[2] = payload[2]|mask;
    }
    if (ui->checkBox_Writerepeat->isChecked()){
        char mask = 1;
        mask = mask << 3;
        payload[2] = payload[2]|mask;
    }
    if (ui->checkBox_Allrepeat->isChecked()){
        char mask = 1;
        mask = mask << 4;
        payload[2] = payload[2]|mask;
    }
    payload[3]= nCol; // col addr 4bit
    payload[4]= nRow;
    payload[5]= nData1;
    payload[6]= nData2;
    for (int i=0;i<baWriterepeat.size();i++){
        payload[7+i] = baWriterepeat[baWriterepeat.size()-i-1];
    }
    qDebug("payload "+ payload.toHex());
    uart_fpga_writeData(payload);
}

void MainWindow::on_pushButton_DUT_S6_Read_clicked()
{
    bool bStatus = false;
    QString str_write_repeat = ui->lineEdit_write_repeat->text();
    QByteArray payload;
    uint nWriterepeat = str_write_repeat.toUInt(&bStatus,10);
    QByteArray baWriterepeat;
    baWriterepeat[0] = nWriterepeat;
    baWriterepeat[1] = nWriterepeat>>8;
    baWriterepeat[2] = nWriterepeat>>16;
    baWriterepeat[3] = nWriterepeat>>24;

    payload.resize(7);
    payload[0]=7;
    payload[1]=FPGA_S6_READ;
    payload[2]=0;
    if (ui->checkBox_Readrepeat->isChecked()){
        char mask = 1;
        mask = mask << 2;
        payload[2] = payload[2]|mask;
    }
    if (ui->checkBox_Writerepeat->isChecked()){
        char mask = 1;
        mask = mask << 3;
        payload[2] = payload[2]|mask;
    }
    if (ui->checkBox_Allrepeat->isChecked()){
        char mask = 1;
        mask = mask << 4;
        payload[2] = payload[2]|mask;
    }

    for (int i=0;i<baWriterepeat.size();i++){
        payload[3+i] = baWriterepeat[baWriterepeat.size()-i-1];
    }


    qDebug("payload "+ payload.toHex());
    uart_fpga_writeData(payload);
}
