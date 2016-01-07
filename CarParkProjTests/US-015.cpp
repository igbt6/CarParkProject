#include "US-015.h"



    US015::US015(PinName triggerPin, PinName echoPin):trigger(triggerPin),echoInPin(echoPin),echoIn(echoPin){
        echoIn.rise(this, &US015::getDistanceValue);
    }
    
    int US015::doMeasurement(void){
        Timer tim;
        int timeUs=0;
        trigger.write(1);  //trigger
        wait_us(30);
        trigger.write(0);
        
        while(echoInPin==0);
        
        tim.start();
        int start= tim.read_us();
        while(echoInPin==1);
        timeUs= tim.read_us()-start;
        return timeUs;
    }
     
     
    int US015::convertTimeToDistanceValue(int timeUs){
        
        return ((timeUs) * 34/100)/2;  //(0.34mm/us)
    } 
    void US015::getDistanceValue(void){
        
        
    }
    