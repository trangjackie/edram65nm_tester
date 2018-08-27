#include "dut_data.h"

dut_data::dut_data()
{
    sram_data = new QByteArray();
    raw_data = new QByteArray();
    data_avarible = false;
}

dut_data::~dut_data()
{

}

char dut_data::data_classify()
{

    char ret = 'X';
    sram_data->clear();
    if (raw_data->at(0) == FPGA_SEND_TEST_CHAR) {
        sram_data->append(raw_data->mid(1,raw_data->length()-1));
        data_avarible = true;
        ret = FPGA_SEND_TEST_CHAR;
    } else if (raw_data->at(0) == FPGA_S12_WRITE) {
        //sram_data->append(raw_data->mid(raw_data->length()-1,2));
        data_avarible = true;
        ret = FPGA_S12_WRITE;
    } else if (raw_data->at(0) == FPGA_SIPO_CONFIG) {
        //sram_data->append(raw_data->mid(raw_data->length()-1,1));
        data_avarible = true;
        ret = FPGA_SIPO_CONFIG;
    } else if (raw_data->at(0) == FPGA_S12_READ) {
        sram_data->append(raw_data->mid(1,raw_data->length()-1));
        data_avarible = true;
        ret = FPGA_S12_READ;
    } else if (raw_data->at(0) == FPGA_E2_WRITE) {
        sram_data->append(raw_data->mid(1,raw_data->length()-1));
        data_avarible = true;
        ret = FPGA_E2_WRITE;
    } else if (raw_data->at(0) == FPGA_E1_WRITE) {
        sram_data->append(raw_data->mid(1,raw_data->length()-1));
        data_avarible = true;
        ret = FPGA_E1_WRITE;
    } else if (raw_data->at(0) == FPGA_S6_READ) {
        sram_data->append(raw_data->mid(1,raw_data->length()-1));
        data_avarible = true;
        ret = FPGA_S6_READ;
    }

    return ret;
}

void dut_data::convert_data_to_image(QImage* img, QByteArray* data)
{
    char cdata,cmask;
    bool color = false;
    // data array
    for (int x = 0; x < 16; x++)
    {
        for (int y = 0; y < 256; y++)
        {
            if ((x*256+y)<=(data->length()-1)){
                cdata = data->at(x*256+y);
                color = false;
            }
            else {
                cdata = 0;
                color = true;
            }
            cmask = 0x01;
            for (int b = 0; b<8;b++)
            {
                if ((cdata&cmask)==cmask)
                {
                    img->setPixel(16*b+x, 255-y, qRgb(255, 255, 255));
                }
                else
                {
                    if (color){
                        img->setPixel(16*b+x, 255-y, qRgb(50, 240, 10));
                    } else {
                        img->setPixel(16*b+x, 255-y, qRgb(0, 0, 0));
                    }

                }
                cmask = cmask<<1;
            }
        }
    }

}
