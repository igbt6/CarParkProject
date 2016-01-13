#include <mbed.h>
#include "US-015.h"
 
 
#define TRIGGER_PIN PC_1
#define ECHO_PIN PC_0
Serial debugPort(SERIAL_TX, SERIAL_RX); //Default 9600 bauds, 8-bit data, no parity
 
void measurementFinished(int resultVal){
   debugPort.printf("%d",resultVal);
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
