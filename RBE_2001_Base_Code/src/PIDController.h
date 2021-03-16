#pragma once
class PIDController{
    private:
    double pVal;
    double iVal;
    double dVal;
    double target;
    double actual;
    double output;
    double pError;
    double iError;
    double dError;
    double pFactor;
    double iFactor;
    double dFactor;
    double prevError;
    public:
    void setPID(float P, float I, float D);
    void init(double currValue, double targetValue);
    void runPID(double currValue, double targetValue);
    double getPID();
    
};