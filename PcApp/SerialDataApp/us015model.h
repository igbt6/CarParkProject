#ifndef US015MODEL_H
#define US015MODEL_H

#include <QtCore>
#include <frame.h>

class US015Model
{
public:
    US015Model();

    QList<QString> parseFrame(const QByteArray& data);
    void setFrameParameters(char startChar,int nrOfBytes, CRC::CrcType crcType);

private:
    int value;      // [mm]
    static const char startChar ='x';
    static const int nrOfBytesFrame =4; //4
    static const CRC::CrcType crcType =CRC::_16Bit;
    Frame frame;
};

#endif // US015MODEL_H
