#include <Romi.cpp>//This should handle all required includes
#include <IRdecoder.cpp>
Romi robot = Romi();//Create robot object
IRDecoder IR = IRDecoder();
int i;
void setup(){
//Put your setup code here, to run once.
Serial.begin(9600);
// IR.handleIRsensor();
IR.init();
// robot.motherBoard.irSensor.init();
i = 0;
}
void loop(){
//Put your loop code here, to run repeatedly.
/*
robot.motherBoard.irSensor.handleIRsensor();
Serial.println(robot.motherBoard.irSensor.getKeyCode());*/
// IR.handleIRsensor();
i++;
if(i==20){
// Serial.println(IR.getKeyCode());
i = 0;
}

delay(5);
};


