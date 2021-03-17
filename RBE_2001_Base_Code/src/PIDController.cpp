    #include <PIDController.h>
    
    void PIDController::setPID(double P, double I, double D){
        pVal = P;
        iVal = I;
        dVal = D;
    }
    void PIDController::init(double currValue, double targetValue){
        target = targetValue;
        actual = currValue;
        output = 0;
        pError = currValue - targetValue;
        prevError = pError;
        iError = 0;
        dError = 0;
        timesRun = 0;
    }
    void PIDController::runPID(double currValue, double targetValue){
        timesRun++;
        target = targetValue;
        actual = currValue;
        //Proportional
        pError = currValue - targetValue;
        pFactor = pError * pVal;

        //Integral
        iError += pError;
        iFactor = -iError * iVal;

        //Differential
        dError = pError - prevError;
        prevError = pError;
        dFactor = dError * dVal;
        output = pFactor + iFactor + dFactor;
    }
    double PIDController::getPID(){
        return output;
    }
