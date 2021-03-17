#include <Arduino.h>
#include <utils.h>
#include <PIDController.h>
#pragma once
class blueMotor{
    private:
    
    PIDController liftPID;
    void setEffort(int effort, bool clockwise);
        static void EncoderISR();
        const int tolerance = 8;
        const int PWMOutPin = 11;
        const int AIN2 = 4;
        const int AIN1 = 13;
        const int ENCA = 0;
        const int ENCB = 1;
        const int EncoderRatio = 540;

        long previousTime = 0;
        float previousPosition = 0;       

        int object = 0;
        int upDBand = 194;
        int downDBand = 227;

        float PID_P = .1;
        float PID_I = -.000001;
        float PID_D = .0001;

        

    public:
    int currEffort;
    int currEffortCorrected;
    float targetAngle;//radians
    float targetPosition;//counts
    void reset();
    void setup();
    void setEffort(float effort);
    void resetEncoder();//init
    long getPosition();
    float getRadians();//get current angle
    float getVelocity();
    void moveTo(long position);
    void moveToAngle(float angle);//Set target angle (rad)
    bool runMotor();//Move towards target angle, return true if finished

    int checkDeadzone(int dir);
    void setObject(int id);
    int setEffortDBand(float effort);
    void testDBands(int obj);
};