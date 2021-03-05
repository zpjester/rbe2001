class blueMotor{
    private:
    float targetAngle;//radians
    float currThrottle;//0-1
    public:
    void resetEncoder();//init
    float getAngle();//get current angle
    void setTargetAngle(float angle);//Set target angle (rad)
    void setTargetAngle(float angle, float throttle);//Set target angle (rad) and throttle (0-1)
    bool runArm();//Move towards target angle, return true if finished

    blueMotor();
};