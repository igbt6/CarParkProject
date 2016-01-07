#include "mbed.h"
#include "US-015.h"
 
 
 #define TRIGGER_PIN PC_1
 #define ECHO_PIN PC_0
//------------------------------------
// Hyperterminal configuration
// 9600 bauds, 8-bit data, no parity
//------------------------------------
 
Serial debugPort(SERIAL_TX, SERIAL_RX);
InterruptIn mybutton(USER_BUTTON);
DigitalOut myled(LED1);
 

int main()
{
    US015 us015(TRIGGER_PIN,ECHO_PIN );
    while (1) {
        wait_ms(500);
        debugPort.printf("%d",us015.convertTimeToDistanceValue(us015.doMeasurement()));
    }
}
