#include <Romi32U4.h>
#include "PIDController.cpp"
#include <Timer.h>
class driveBaseV2{
    private:
    bool active;
    enum modes{stopped, direct, distance};
    modes driveMode;
    double baseWidth;
    double wheelDiam;
    int gearRatio;//between encoder and wheel
    int encoderRes;//Encoder counts per revolution
    double L_Target_Dist;
    double R_Target_Dist;
    double L_Position;
    double R_Position;
    int max_Throttle;
    Romi32U4Motors driveMotors;
    Romi32U4Encoders driveEncoders;
    PIDController steerPID();
    Timer driveTimer();
    public:
    void driveBaseV2::tankDrive(double L_Throttle, double R_Throttle);
    void driveBaseV2::arcadeDrive(double yAxis, double xAxis);
    void runDrive();
    void driveWheelsDist(double left_dist, double right_dist);
    void driveDist(double dist);
    void turnAngle(double angle);
    driveBaseV2();
};