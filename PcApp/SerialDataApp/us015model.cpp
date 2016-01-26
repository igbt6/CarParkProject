#include "us015model.h"

US015Model::US015Model():frame(startChar,nrOfBytesFrame,crcType)
{
        this->value=-1;
}

bool US015Model::parseFrame(const QByteArray& data){

    if(frame.isFrameCorrect(data))
    {
        /*
        qDebug()<<"NEW_FRAME ARRIVED:";
        foreach(char byte, data ){
            qDebug()<<"0x"<<QString::number(byte, 16);
        }
        */
        return true;
    }
    return false;
}


int US015Model:: getDistanceValue(void)
{
    QByteArray* rawDataPtr= frame.getRawData();
    this->value =0;
    for(int i=0; i<getNrOfDataBytesInFrame();i++)
    {
        try{
            //qDebug()<<"RAW DATA PTR: "<<QString::number(rawDataPtr->at(i), 16);
            this->value|= ((rawDataPtr->at(i)&0xFF)<<(i*8));
        }
        catch(const std::exception& e){
            break;
        }
    }
    return this->value;

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
