#include "crc.h"

CRC::CRC()
{

}


uchar CRC::computeCRC8(const QByteArray &data)
{

 return 0; //TODO

}



ushort CRC::computeCRC16(const QByteArray &byteArr)
{
    unsigned char i;
    ushort data;
    ushort crc = CRC16_INITIAL_VALUE;
    int len =byteArr.size();

    do
    {
        for (i = 0, data = (unsigned int)0xff & byteArr.at(i);
                i < 8;
                i++, data >>= 1
            )
        {
            if ((crc & 0x0001) ^ (data & 0x0001))
                crc = (crc >> 1) ^ CRC16_POLYNOMIAL;
            else
                crc >>= 1;
        }
    } while (--len);

    crc = ~crc;
    data = crc;
    crc = (crc << 8) | (data >> 8 & 0xff);

    return (crc);
}

uint CRC::computeCRC32(const QByteArray &data)
{
    return 0;   //TODO
}
