#include <mbed.h>



class US015{
    
public:
    US015(PinName triggerPin, PinName echoPin);
    
    int doMeasurement(void);
    
    int convertTimeToDistanceValue(int timeMs);
    
    void getDistanceValue(void);
    
private:
    DigitalOut trigger;
    DigitalIn echoInPin;
    InterruptIn echoIn;
    
};