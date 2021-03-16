#include <blueMotor.h>

long oldValue;
long newValue;
long errorCount;
long count = 0;

const char X = 5;
char encoderArray[4][4] = {
    {0, -1, 1, X},
    {1, 0, X, -1},
    {-1, X, 0, 1},
    {X, 1, -1, 0}};

int deadBands[3][2] = {
    {194, 227},//Unloaded up / down
    {194, 227},//Plastic panel up / down
    {207, 235} //Aluminum panel up / down
};


void blueMotor::setEffort(int effort, bool clockwise){
    if(clockwise){
        setEffort(effort);
    }
    else{
        setEffort(-1 * effort);
    }
}

void blueMotor::setEffort(float effort){
    if(effort > 0){
        digitalWrite(AIN1, HIGH);
        digitalWrite(AIN2, LOW);
        OCR1C = effort;
    }
    else{
        digitalWrite(AIN1, LOW);
        digitalWrite(AIN2, HIGH);
        OCR1C = abs(effort);
    }
}

void blueMotor::moveTo(long position){
    blueMotor::targetPosition = position;
    blueMotor::armPID.init(getPosition(), position);
}
void blueMotor::moveToAngle(float angle){
    long position = angle / 360 * EncoderRatio;
    blueMotor::moveTo(position);
}
long blueMotor::getPosition(){
    return count;
}

void blueMotor::reset(){
    count = 0;
}

void blueMotor::EncoderISR(){
    newValue = (digitalRead(3) << 1) | digitalRead(2);
    char value = encoderArray[oldValue][newValue];
    if(value == X){
        errorCount++;
    }
    else{
        count -= value;
    }
    oldValue = newValue;
}

void blueMotor::setup(){
    //PWM Setup
    TCCR1A = 0xA8;
    TCCR1B = 0x11;
    ICR1 = 400;
    OCR1C = 0;

    //Encoder Setup
    const int encPin1 = 2;
    const int encPin2 = 3;
    pinMode(encPin1, INPUT);//Encoder in 1
    pinMode(encPin2, INPUT);//Encoder in 2

    pinMode(4, OUTPUT);
    pinMode(11, OUTPUT);
    Serial.begin(9600);
    attachInterrupt(digitalPinToInterrupt(encPin1), EncoderISR, CHANGE);
    attachInterrupt(digitalPinToInterrupt(encPin2), EncoderISR, CHANGE);
    //PID Setup
    blueMotor::armPID.setPID(.01, 0, 0);
}

float blueMotor::getRadians(){
    float position = getPosition();
    return (position / EncoderRatio * 2 * PI);
}

float blueMotor::getVelocity(){
    float currentPosition = count;
    long currentTime = millis();
    float positionDifference = (currentPosition - previousPosition) / EncoderRatio;
    double timeDifference = (currentTime - previousTime);

    previousPosition = currentPosition;     //Reset position
    previousTime = currentTime;             //Reset time
    // return timeDifference;
    return(positionDifference / timeDifference) * 1000 * 60;
}
bool blueMotor::runMotor(){
    if(abs(targetPosition - getPosition()) < tolerance){
        blueMotor::setEffort(0);
        return true;
    }
    else{
        armPID.runPID(getPosition(), targetPosition);
        float throttleFrac = armPID.getPID();
        if(abs(throttleFrac) > 1){
            throttleFrac = sign(throttleFrac);
        }
        float throttle = throttleFrac * 400;
        setEffortDBand(throttle);




        return false;
    }
}


int blueMotor::checkDeadzone(int dir){
    blueMotor::reset();
    int i = 0;
    bool complete = false;
    while(!complete){
        setEffortDBand(i * dir);
        i++;
        delay(5);
        if(abs(count) > 1){
            complete = true;
        }
    }
    setEffort(0);
    return i;
}

void blueMotor::setObject(int obj){
    object = obj;
    upDBand = deadBands[obj][0];
    downDBand = deadBands[obj][1];
}

int blueMotor::setEffortDBand(float effort){
    if(abs(effort) > 400){
        effort = sign(effort) * 400;
    }
    int dBand;
    if(effort < 0){
        dBand = blueMotor::downDBand;
    }
    else{
        dBand = blueMotor::upDBand;
    }

    float throttle = effort / 400;
    float mEffort = dBand + throttle * (400 - dBand);

    // Serial.println(mEffort);
    blueMotor::setEffort(mEffort);
    return mEffort;
}

void blueMotor::testDBands(int obj){
    const int runs = 25;
int total = 0;
for(int i = 0; i < runs; i++){
    total += blueMotor::checkDeadzone(1);
    delay(100);
    Serial.print("Completed: Up Run ");
    Serial.print(i + 1);
    Serial.print(" of ");
    Serial.println(runs);
}
total /= runs;
int upzone = total;

total = 0;
for(int i = 0; i < runs; i++){
    total += blueMotor::checkDeadzone(-1);
    delay(100);
    Serial.print("Completed: Down Run ");
    Serial.print(i + 1);
    Serial.print(" of ");
    Serial.println(runs);
}
total /= runs;
Serial.print("Up deadzone = ");
Serial.println(upzone);
Serial.print("Down deadzone = ");
Serial.println(total);
blueMotor::setEffort(0);
}