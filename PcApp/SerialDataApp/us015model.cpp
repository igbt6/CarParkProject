#include "us015model.h"

US015Model::US015Model():frame(startChar,nrOfBytesFrame,crcType)
{

}

QList<QString> US015Model::parseFrame(const QByteArray& data){

    QList<QString> frameVal;
    if(frame.isFrameCorrect(data))
    {

        qDebug()<<"NEW_FRAME ARRIVED:";
        foreach(char byte, data ){
            qDebug()<<"0x"<<QString::number(byte, 16);
        }
        frameVal.append(QString(QDate::currentDate().toString()));
        frameVal.append(QString::fromStdString(data.toStdString()));
        frameVal.append(QString::fromStdString("[mm]"));
    }
    else
    {
        frameVal.append(QString::fromStdString("---"));
        frameVal.append(QString::fromStdString("---"));
        frameVal.append(QString::fromStdString("---"));
    }
    return  frameVal;
}



char  US015Model:: getStartCharacter(void) const
{
    return startChar;
}

int  US015Model::getNrOfDataBytesInFrame(void) const
{
    return nrOfBytesFrame;
}

int  US015Model:: getLengthOfRawDataInFrame(void) const
{
  return 1+1+nrOfBytesFrame+crcType;    //startChar+lengthByte+rawDataBytes+CRC bytes
}
