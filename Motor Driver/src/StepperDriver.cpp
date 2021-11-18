#include <Arduino.h>
#include "StepperDriver.h"
#include <Stepper.h>

StepperDriver::StepperDriver(uint8_t new_id, uint8_t stepsPerRev, uint32_t pin1, uint32_t pin2, 
                            uint32_t pin3, uint32_t pin4, uint32_t enable, uint8_t new_speed)
{
    id = new_id;
    pin_A = pin1;
    pin_Abar = pin2;
    pin_B = pin3;
    pin_Bbar = pin4;
    pin_enable = enable;
    speed = new_speed;
    p_Stepper = new Stepper(stepsPerRev, pin1, pin2, pin3, pin4);
    p_Stepper->setSpeed(speed);

    curr_pos = 0;

    pinMode(pin_enable, OUTPUT);
    digitalWrite(pin_enable, HIGH);
}

void StepperDriver::move(int16_t steps)
{
    p_Stepper->step(steps);
    curr_pos += steps;
}

int32_t StepperDriver::getPosition(void)
{
    return curr_pos;
}

void StepperDriver::setPosition(int32_t new_pos)
{
    curr_pos = new_pos;
}

void StepperDriver::setSpeed(uint16_t new_speed)
{
    p_Stepper->setSpeed(new_speed);
    speed = new_speed;
}

uint16_t StepperDriver::getSpeed(void)
{
    return speed;
}

uint8_t StepperDriver::getID(void)
{
    return id;
}