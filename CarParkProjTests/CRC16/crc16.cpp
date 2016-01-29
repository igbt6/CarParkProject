#include "crc16.h"


uint16_t CRC16::computeCRC16(uint8_t const *data_p, uint8_t len)
{
    uint8_t i;
    uint16_t data;
    uint16_t crc = CRC16_INITIAL_VALUE;
    
    if(len==0)
        return (~crc);
    do
    {
        for (i = 0, data = (unsigned int)0xff & *data_p++;
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


