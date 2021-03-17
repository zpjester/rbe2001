#include "Ultrasonic.h"
#include <pcint.h>
#include <Timer.h>

static const int triggerPin = 12;
static const int echoPin = 17;
static unsigned long startTime;
static unsigned long roundTripTime;

/**
 * Interrupt service routine for the echo pin
 * The echo pin goes high when the ultrasonic burst is sent out and goes low when the
 * echo is received. On the burst, the time is recorded, and on the echo the round trip
 * time is computed. This is used when requesting a distance by the getDistance methods.
 */
void ultrasonicISR()
{
    if (digitalRead(echoPin))
    {
        startTime = micros();
    }
    else
    {
        roundTripTime = micros() - startTime;
    }
}

/**
 * setup is called from the arduino setup method
 * Sets up the ports and the ISR. The ports are fixed rather than passed in since
 * there will only be one sensor and only on those ports.
 */
void Ultrasonic::setup()
{
    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);
    //    attachInterrupt(digitalPinToInterrupt(echoPin), ultrasonicISR, CHANGE);
    attachPCInt(PCINT0, ultrasonicISR);
}

/**
 * loop is called from the arduino loop method
 * Loop triggers the ultrasonic burst output every 100ms making a timer not
 * necessary for this task. 100ms is longer than the longest time for an echo
 * return from the sensor.
 */

Timer pingTimer(100);

void Ultrasonic::loop()
{
    if (pingTimer.isExpired())
    {
        digitalWrite(triggerPin, LOW);
        delayMicroseconds(2);
        digitalWrite(triggerPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(triggerPin, LOW);
    }
}

/**
 * getDistanceCM returns the distance in centimeters for the nearest object
 * Use the round trip time from the echo return to compute the distance to any
 * objects in front of the sensor. Note: interrupts must be disabled while 
 * referencing "roundTripTime" in case there is an echo interrupt while fetching
 * the long value.
 */
float Ultrasonic::getDistanceCM()
{
    long rt;
    cli();
    rt = roundTripTime;
    sei();
    float distance = (rt * 0.0343) / 2.0;
    return distance;
}
