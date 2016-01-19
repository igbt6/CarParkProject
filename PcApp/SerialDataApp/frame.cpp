#include "frame.h"


#include <QDebug>
Frame::Frame(char startChar ,int nrOfBytes ,CRC::CrcType crcType )
{
    this->startChar= startChar;
    this->nrOfBytes= nrOfBytes;
    this->crcType= crcType;
    this->rawData = new QByteArray();
}

Frame::~Frame()
{
  delete rawData;
  rawData= NULL;
}



QByteArray* Frame:: getRawData(){

    return rawData;
}


bool Frame:: isFrameCorrect(const QByteArray& frame){

    if(frame.at(0)!=startChar)
        return false;

    if(frame.length()<static_cast<int>(frame.at(1))+static_cast<int>(crcType)+1)
        return false;

    if(nrOfBytes!=static_cast<int>(frame.at(1)))
       return false;

    QByteArray data;
    for(int i=0;i<nrOfBytes; i++)
    {
        data.append(frame[i+2]);
    }
    foreach(uchar byte,data)
    {
         //qDebug()<<"FROM BUF: "<<QString::number(byte);
         qDebug()<<"rawData "<<QString::number(byte);

    }

    uint crcResult = false;
    switch(crcType)
    {
        case CRC::_8Bit:
           crcResult= CRC::computeCRC8(data);
        break;

        case CRC::_16Bit:
           crcResult= CRC::computeCRC16(data);
        break;

        case CRC::_32Bit:
           crcResult= CRC::computeCRC32(data);
        break;

    }
    qDebug()<<" CRC RES:"<<crcResult<<" "<<static_cast<uint>((frame.at(nrOfBytes+3)<<8)|(frame.at(nrOfBytes+2)));
        qDebug()<<"----------------------";
    if(crcResult==static_cast<uint>((frame.at(nrOfBytes+3)<<8)|(frame.at(nrOfBytes+2))))
    {
        this->rawData->resize(nrOfBytes);
        for(int i=0;i<nrOfBytes; i++)
        {
            rawData->insert(i,frame[i+2]);
        }
        return true;
    }
    else
        return false;
}
