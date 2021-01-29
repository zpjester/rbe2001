#include "encoderMotor.cpp";
class driveBase{
    private:
    motor leftMotor;
    motor rightMotor;


    public:
    //stuff

    //constructor
    driveBase(){
        //Default motor params, edit these
        int leftPin = 0;
        int rightPin = 0;
        int leftEncPin = 0;
        int rightEncPin = 0;
        int driveEncResolution = 0;
        bool driveEncFlipped = false;
        double driveGearRatio = 0;
        int leftTrim = -1;//left motor is flipped
        int rightTrim = 1;

        encoderMotor leftMotor = encoderMotor(leftPin, leftEncPin, driveEncFlipped, driveGearRatio / leftTrim, driveEncResolution);
        encoderMotor rightMotor = encoderMotor(rightPin, rightEncPin, driveEncFlipped, driveGearRatio / rightTrim, driveEncResolution);
    }
};