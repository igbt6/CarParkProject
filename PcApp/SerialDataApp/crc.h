#ifndef CRC_H
#define CRC_H
#include <QByteArray>


#define CRC16_POLYNOMIAL        0x8408
#define CRC16_INITIAL_VALUE     0xFFFF

class CRC
{
public:
    CRC();

    enum CrcType{
        _8Bit=1,    //describes nrOfBytes used by this
        _16Bit=2,
        _32Bit=4
    };


     static uchar computeCRC8(const QByteArray &data);
     static ushort computeCRC16(const QByteArray &data);
     static uint computeCRC32(const QByteArray &data);
};

#endif // CRC_H
