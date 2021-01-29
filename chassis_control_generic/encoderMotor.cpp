#include <iostream>
#include <cmath>
#include "motor.cpp";


class encoderMotor: public motor{
    private:
    //Encoder stuff
        int encoderPin;
        long int encoderPos;
        double gearRatio;//Ratio between the encoder shaft and the main wheel, higher value = faster output.
        bool encoderFlipped;//Does the encoder rotate backwards?
        int flipMod;//If encoder rotates in reverse direction, set to -1;
        int encoderResolution;//Number of encoder steps for 1 full revolution of the output shaft;

    //Positional control
        double control_P;//PID control
        double control_I;
        double control_D;
        double tolerance;//Fudge angle to determine end condtitions of drive commands
    public:
        int getPosition(){//Raw encoder position
            return encoderPos;
        };
        double getAngle(){//Angle of wheel since last reset, in degrees
            return encoderPos / encoderResolution * gearRatio * 360 * flipMod;
        };
        void resetEncoder(){
            encoderPos = 0;
        };
        void setTolerance(double newTol){
            tolerance = newTol;
        };
        double getTolerance(){
            return tolerance;
        };
        /*
        Drive motor to a target angle at specified throttle, then release. Will overshoot. Requires running repeatedly to allow other code to run, will return true when complete.
        Throttle should be between 0 and 1      
        */
        bool goToPos(double pos, double throttle){
            if(std::abs (getAngle() - pos) < getTolerance()){
                kill;//Release motor
                return true;//Exit with true condition
            }
            else if(getAngle() - pos < 0){//If set point is ahead
                setThrottle(throttle * flipMod);
                return false;
            }
            else{
                setThrottle(throttle * flipMod * -1);
                return false;
            }
        }

        double getP(){
            return control_P;
        }
        double getI(){
            return control_I;
        }
        double getD(){
            return control_D;
        }
        void setPID(double newP, double newI, double newD){
            control_P = newP;
            control_I = newI;
            control_D = newD;
        }
        
    //constructor
    encoderMotor(int ESC_Pin, int encPin, bool flippedEncoder, double gear_Ratio, int encoder_Resolution){
        ESCPin = ESC_Pin;
        currThrottle = 0;
        status = "initialized";
        encoderPin = encPin;
        encoderFlipped = flippedEncoder;
        if(encoderFlipped){
            flipMod = -1;
        }
        else{
            flipMod = 1;
        };
        gearRatio = gear_Ratio;
        encoderResolution = encoder_Resolution;
        encoderPos = 0;
        tolerance = 5;//default, degrees
        control_P = 0;//PID requires calibration
        control_I = 0;
        control_D = 0;
    }

};
