#include <mbed.h>
#include "US-015.h"
#include "US015DataParser.h" 
#include "crc16.h"
 
#define TRIGGER_PIN PC_1
#define ECHO_PIN PC_0
Serial debugPort(SERIAL_TX, SERIAL_RX); //Default 9600 bauds, 8-bit data, no parity
 
void measurementFinished(int resultVal){
   
   uint16_t crc=CRC16::computeCRC16((uint8_t const *)resultVal, 4);
   uint8_t buf[9];
   buf[0]='x';
   buf[1]=sizeof(resultVal);
   memcpy(&buf[2],(uint8_t *)resultVal,sizeof(resultVal));
   memcpy(&buf[2+sizeof(resultVal)],(uint8_t *)crc,sizeof(crc));
   buf[8]='\0'; //to get a correct printf formatting
   debugPort.printf("%s",buf);
}
int main()
{
    
    US015 us015(TRIGGER_PIN,ECHO_PIN,US015::convertMaxDistanceToMaxTimeout(MAX_DISTANCE_FOR_US015_SENSOR_CM) );
    us015.setFinishCallback(measurementFinished);
    bool timeoutFlag=true;
    while (1) {
        wait_ms(1000);  
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
            debugPort.printf("Timeout Happened");
            us015.resetMeasuremnt();
        }
        
    }
}
