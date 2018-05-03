#include "dut_data.h"

dut_data::dut_data()
{
    sram_data = new QByteArray();
    raw_data = new QByteArray();
    selected_block = 0;
    data_avarible = false;
}

dut_data::~dut_data()
{

}

void dut_data::data_classify()
{
    sram_data->clear();
    if (raw_data->at(0) == 'R') {
        sram_data->append(raw_data->mid(raw_data->length()-1,1));
        data_avarible = true;
    } else if (raw_data->at(0) == 'W') {
        sram_data->append(raw_data->mid(raw_data->length()-1,2));
        data_avarible = true;
    } else if (raw_data->at(0) == 't') {
        iTID[0] = raw_data->mid(4,1).toInt();
        iTID[1] = raw_data->mid(8,5).toInt();
        iTID[2] = raw_data->mid(12,9).toInt();
        iTID[3] = raw_data->mid(16,13).toInt();
        iTID[4] = raw_data->mid(20,17).toInt();
        iTID[5] = raw_data->mid(24,21).toInt();
        iTID[6] = raw_data->mid(28,25).toInt();
        iTID[7] = raw_data->mid(32,29).toInt();
        iTID[8] = raw_data->mid(36,33).toInt();
        iTID[9] = raw_data->mid(40,37).toInt();
        iTID[10] = raw_data->mid(44,41).toInt();
        iTID[11] = raw_data->mid(48,45).toInt();
        qDebug((raw_data->toHex()));
    } else  {
        sram_data->append(raw_data->mid(raw_data->length()-1,0));
        data_avarible = true;
    }

    //sram_data = raw_data;
    //data_avarible = true;
}

void dut_data::convert_data_to_image(QImage* img)
{
    char cdata,cmask;
    // data array
    for (int x = 0; x < 16; x++)
    {
        for (int y = 0; y < 256; y++)
        {
            if ((selected_block*16*256+x*256+y)<=(raw_data->length()-1)){
                cdata = raw_data->at(selected_block*16*256+x*256+y);
            }
            else {
                cdata = 0;
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
                    img->setPixel(16*b+x, 255-y, qRgb(0, 0, 0));
                }
                cmask = cmask<<1;
            }
        }
    }

}
