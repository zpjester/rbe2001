#include <iostream>
#include <cmath>
class motor{//Generic motor, only value is throttle
    protected:
    double currThrottle; //-1 to 1
    int ESCPin;
    std::string status;
    public:
    void setThrottle(double newThrottle){
        currThrottle = newThrottle;
        status = "driving";
        //ESC interface code goes here
    }
    double getThrottle(){
        return currThrottle;//Return the current throttle
    }
    motor(int pin){
        currThrottle = 0;//Motors should be shut down upon inititalization
        ESCPin = pin;//Bind the motor to a pin
    }
    motor(){//Don't use this
        currThrottle = 0;
        ESCPin = 0;
    }
    std::string getStatus(){
        return status;
    }
    void kill(){
        setThrottle(0);
        status = "off";
    }
    
};