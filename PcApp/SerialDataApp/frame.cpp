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
        data.append(frame[2+i]);
    }
/*
    foreach(uchar byte,data)
    {
         qDebug()<<"rawData "<<QString::number(byte);
    }
    */
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
    int crc= (frame.at(nrOfBytes+3)<<8)&0xFF00;
    crc|=frame.at(nrOfBytes+2)&0xFF;
/*
    qDebug()<<" CRC RES:"<<crcResult<<" "<<crc;//static_cast<ushort>(((frame.at(nrOfBytes+3)<<8)&0xFF00)|(frame.at(nrOfBytes+2)));
    qDebug()<<(frame.at(nrOfBytes+3))<<"    ---------   "<<frame.at(nrOfBytes+2);
    qDebug()<<"CRC_Result: "<<QString("%1").arg(((crcResult>>8)&0xFF) , 0, 16) <<" " <<QString("%1").arg((crcResult&0xFF) , 0, 16);
    qDebug()<<QString("%1").arg(frame.at(nrOfBytes+3) , 0, 16);
    qDebug()<<QString("%1").arg(frame.at(nrOfBytes+2) , 0, 16);
    qDebug()<<QString("%1").arg(crc , 0, 16);
    qDebug()<<"----------------------";
*/
    if(crcResult==static_cast<ushort>(crc))
    {

        //qDebug()<<"NR OF BYTES::-- "<<this->rawData->size()<<"---------- "<<this->nrOfBytes;
        this->rawData->resize(nrOfBytes);
        for(int i=0;i<nrOfBytes; i++)
        {
            rawData->insert(i,frame[i+2]);
        }
        //qDebug()<<"SIZE::--------------------- "<<this->rawData->size();
        return true;
    }
    else
        return false;
}
