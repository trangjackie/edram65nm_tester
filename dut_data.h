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
#define FPGA_E2_WRITE 'E'
#define FPGA_E1_WRITE 'F'

class dut_data
{
public:
    dut_data();
    ~dut_data();
    QByteArray *raw_data;

    bool data_avarible;
    void convert_data_to_image(QImage* img, QByteArray* data);
    char data_classify();

       QByteArray *sram_data;


};

#endif // DUT_DATA_H
