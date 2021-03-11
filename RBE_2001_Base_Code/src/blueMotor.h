#include <Arduino.h>
#include <utils.h>
#pragma once
class blueMotor{
    private:
    float targetAngle;//radians
    float targetPosition;//counts

    void setEffort(int effort, bool clockwise);
        static void EncoderISR();
        const int tolerance = 3;
        const int PWMOutPin = 11;
        const int AIN2 = 4;
        const int AIN1 = 13;
        const int ENCA = 0;
        const int ENCB = 1;
        const int EncoderRatio = 540;

        long previousTime = 0;
        float previousPosition = 0;       

    public:
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

    // blueMotor();
};