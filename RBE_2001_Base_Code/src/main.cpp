#include <Arduino.h>
#include <Romi32U4.h>
#include <driveBase.cpp>

void setup() {
  // put your setup code here, to run once:
  driveBase drive = driveBase();
  delay(5000);  
  drive.driveTest("FORWARDS", 1);
  delay(1000);
  drive.driveTest("BACKWARDS", 1);
  delay(1000);
  drive.driveTest("LEFT", 1);
  delay(1000);
  drive.driveTest("RIGHT", 1);
}

void loop() {
  // put your main code here, to run repeatedly:
  
}