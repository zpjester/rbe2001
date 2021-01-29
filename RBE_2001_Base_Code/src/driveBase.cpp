#include <Arduino.h>
#include <Romi32U4.h>
class driveBase{
    private:
        double gearRatio;
        int encoderRes;
        double wheelDiam;
        double wheelBase;
        Romi32U4Motors motors;
        Romi32U4Encoders encoders;
    public:
        //constructor
        driveBase(){
            gearRatio = 0;
            encoderRes = 0;
            wheelDiam = 0;//inches
            wheelBase = 0;//inches
        }

        //Get angular position of a wheel
        double getWheelAngle(String side){
            if(side.equals("Left")){
                return (encoders.getCountsLeft() / encoderRes * gearRatio);
            }
            else if(side.equals("Right")){
                return (encoders.getCountsRight() / encoderRes * gearRatio);
            }
            else if(side.equals("Avg")){
                return ((encoders.getCountsLeft() / encoderRes * gearRatio + encoders.getCountsRight() / encoderRes * gearRatio) / 2);
            }
            else{
                return 0;
            }
        }
        double getWheelDistance(String side){
            return (getWheelAngle(side)) * PI / 180 * (wheelDiam / 2);
        }
        
        void driveTest(String direction, double speed){//direction = FORWARDS, BACKWARDS, LEFT, RIGHT; 0 <= speed <= 1
        int leftThrottle;
        int rightThrottle;
        int leftDir;
        int rightDir;
        int maxThrottle = 300;
            if(direction.equals("FORWARDS")){
                 leftDir = 1;
                rightDir = 1;
            }
            else if(direction.equals("BACKWARDS")){
                 leftDir = -1;
                rightDir = -1;
            }
            else if(direction.equals("LEFT")){
                 leftDir = -1;
                rightDir = 1;
            }
            else if(direction.equals("RIGHT")){
                 leftDir = 1;
                rightDir = -1;
            }
            else{
                leftDir = 0;
                rightDir = 0;
                Serial.println("Error, invalid direction");
            }
            leftThrottle = leftDir * maxThrottle;
            rightThrottle = rightDir * maxThrottle;
            motors.setEfforts(leftThrottle, rightThrottle);
        }
        

};