#ifndef CRC16_H
#define CRC16_H
#include <QByteArray>


#define CRC16_POLYNOMIAL        0x9EB2
#define CRC16_INITIAL_VALUE     0xFFFF

class CRC16
{
public:
    CRC16();

     ushort computeCRC16(const QByteArray &data);
};

#endif // CRC16_H
