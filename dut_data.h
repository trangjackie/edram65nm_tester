#ifndef DUT_DATA_H
#define DUT_DATA_H

#include <QImage>

/*
 * define command char for fpga
 *
*/
#define FPGA_SEND_TEST_CHAR 'T'
#define FPGA_SIPO_CONFIG 'U'
#define FPGA_S12_READ 'D'
#define FPGA_S12_WRITE 'A'

class dut_data
{
public:
    dut_data();
    ~dut_data();
    QByteArray *raw_data;

    bool data_avarible;
    void convert_data_to_image(QImage* img);
    char data_classify();



private:
    QByteArray *sram_data;

};

#endif // DUT_DATA_H
