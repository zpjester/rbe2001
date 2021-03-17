#pragma once
class PIDController{
    private:
    double pVal;
    double iVal;
    double dVal;
    double target;
    double actual;
    double output;
    int timesRun;
    double pError;
    double iError;
    double dError;
    double pFactor;
    double iFactor;
    double dFactor;
    double prevError;
    public:
    
    // PIDController();
    void setPID(double P, double I, double D);
    
    void init(double currValue, double targetValue);
    void runPID(double currValue, double targetValue);
    double getPID();
};