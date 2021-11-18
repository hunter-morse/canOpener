#include <Arduino.h>
#include "StepperDriver.h"
#include <Stepper.h>

StepperDriver::StepperDriver(uint8_t new_id, uint8_t stepsPerRev, uint32_t pin1, uint32_t pin2, uint32_t pin3, uint32_t pin4, uint32_t enable)
{
    id = new_id;
    pin_A = pin1;
    pin_Abar = pin2;
    pin_B = pin3;
    pin_Bbar = pin4;
    pin_enable = enable;
    pinMode(pin_enable, OUTPUT);
    digitalWrite(pin_enable, HIGH);
    p_Stepper = new Stepper(stepsPerRev, pin1, pin2, pin3, pin4);
}