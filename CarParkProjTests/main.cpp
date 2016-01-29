#include <mbed.h>
#include "US-015.h"
#include "US015DataParser.h" 
#include "crc16.h"
#include "BufferedSerial.h"

#define TRIGGER_PIN PC_1
#define ECHO_PIN PC_0

BufferedSerial debugSerial(SERIAL_TX, SERIAL_RX); //Default 9600 bauds, 8-bit data, no parity
//Serial debugSerial(SERIAL_TX, SERIAL_RX); //Default 9600 bauds, 8-bit data, no parity
 
void measurementFinished(int resultVal){
   uint16_t crc=CRC16::computeCRC16((uint8_t const *)&resultVal, 4);
   
   uint8_t buf[8];
   memset(buf,0,sizeof(buf)*sizeof(uint8_t));
   buf[0]='x'; //frame start
   buf[1]=sizeof(resultVal);
   memcpy(&buf[2],(uint8_t *)&resultVal,sizeof(resultVal));
   memcpy(&buf[2+sizeof(resultVal)],(uint8_t *)&crc,sizeof(crc));
   debugSerial.write(buf,sizeof(buf));
   /*for(int i=0; i<sizeof(buf);i++)
   {
        debugSerial.putc(buf[i]);   
   } 
   */
   
}
int main()
{
    debugSerial.baud(9600);
    
    US015 us015(TRIGGER_PIN,ECHO_PIN,US015::convertMaxDistanceToMaxTimeout(MAX_DISTANCE_FOR_US015_SENSOR_CM) );
    us015.setFinishCallback(measurementFinished);
    bool timeoutFlag=true;
    while (1) {
        wait_ms(500);  
        us015.doMeasurement();
        while(us015.getTimePassedValue()<us015.getTimeoutValue())
        {
            if(us015.isMeasurementRuning())
            {
                timeoutFlag=true;
            }
            else
            {
                timeoutFlag =false;
                break;
            }
        }  
        if(timeoutFlag){
            //debugSerial.printf("Timeout Happened");
            us015.resetMeasuremnt();
        }
        
    }
}
