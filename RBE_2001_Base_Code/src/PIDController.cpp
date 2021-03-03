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
    PIDController(double P, double I, double D){
        pVal = P;
        iVal = I;
        dVal = D;
    }
    PIDController(){
        pVal = 0;
        iVal = 0;
        dVal = 0;
    }
    void setPID(double P, double I, double D){
        pVal = P;
        iVal = I;
        dVal = D;
    }
    void init(double currValue, double targetValue){
        target = targetValue;
        actual = currValue;
        output = 0;
        pError = currValue - targetValue;
        prevError = pError;
        iError = 0;
        dError = 0;
        timesRun = 0;
    }
    void runPID(double currValue, double targetValue){
        timesRun++;
        target = targetValue;
        actual = currValue;
        //Proportional
        pError = currValue - targetValue;
        pFactor = pError * pVal;

        //Integral
        //yes this is technically an incorrect implementation
        iError += pError;
        iFactor = iError / timesRun * iVal;

        //Differential
        //Seriously you should probably stop reading now if you are a math major
        dError = pError - prevError;
        prevError = pError;
        dFactor = dError * dVal;
        output = pFactor + iFactor + dFactor;
    }
    double getPID(){
        return output;
    }
};