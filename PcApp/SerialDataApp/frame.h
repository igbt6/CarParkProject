#ifndef FRAME_H
#define FRAME_H
#include <QByteArray>
#include <crc.h>
class Frame
{
public:

    Frame(char startChar ='x',int nrOfBytes =4,CRC::CrcType crcType =CRC::_16Bit );
    ~Frame();

    bool isFrameCorrect(const QByteArray& frame);

    QByteArray* getRawData();
private:
    char startChar;
    int nrOfBytes;
    CRC::CrcType crcType;
    QByteArray* rawData;

};

#endif // FRAME_H
