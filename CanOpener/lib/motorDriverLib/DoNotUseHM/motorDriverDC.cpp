/**
 * 
 * 
 */

#include "motorDriverDC.h"

MotorDriverDC::MotorDriverDC(uint8_t motorID, uint8_t enablePin, uint8_t pin1, uint8_t pin2){
    // Set protected values
    this->motorID = motorID;
    this->enablePin = enablePin;
    this->pin1 = pin1;
    this->pin2 = pin2;

    movingForward = true;

    // Setup pins as output
    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
    pinMode(enablePin, OUTPUT);

}

uint8_t MotorDriverDC::getID(void){
    return motorID;
}

uint8_t MotorDriverDC::move(int8_t pwm){
    // Map the -128 to 127 value to 0 to 100
    PWM = (int8_t)map(pwm, -128, 127, 0, 100);

    // Check if should be moving forward or backward
    if(pwm < 0){
        movingForward = false;
    } else if (pwm > 0){
        movingForward = true;
    }
}
