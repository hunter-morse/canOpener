/**
 * @file
 * */

#include "MotorDriver.h"
#include <Arduino.h>

MotorDriver::MotorDriver(uint8_t new_id, uint32_t pos, uint32_t neg, uint32_t enable, uint8_t PWM_bound, 
                        uint16_t delay)
{
    //Set class variables to parameters
    id = new_id;
    pinA = pos;
    pinB = neg;
    pinEN = enable;

    //ensure that the max and min PWM are not above 100
    PWM_bound = constrain(PWM_bound, 0, 100);

    PWM_max = PWM_bound;
    PWM_min = -1 * PWM_bound;
    brake_delay = delay;

    //Set the motor and enable pins to OUTPUT
    pinMode(pinA, OUTPUT);
    pinMode(pinB, OUTPUT);
    pinMode(pinEN, OUTPUT);

    //Set the enable pin high
    digitalWrite(pinEN, HIGH);

    //Set the current direction -1: reverse, 0: stopped, 1: forward
    direction = 0;
    
}

void MotorDriver::move(float new_PWM)
{
    //Brake motor if the motor is switching directions for time specified by brake_delay - this is blocking
    if (direction*new_PWM < 0)
    {
        brake();
        delay(brake_delay);
    }
    
    //Check if PWM input is within bounds
    if (new_PWM > PWM_max)
    {
        PWM = PWM_max;
    }
    else if (new_PWM < PWM_min)
    {
        PWM = PWM_min;
    }
    else
    {
        PWM = new_PWM;
    }

    //Use analog write to set PWM value of the motor to the new value
    uint8_t motor_val = 0;
    if (PWM > 0)
    {
        motor_val = (int16_t) round(map(PWM, 0, 100, 0, 255));
        //Disable motor briefly, change values on control pins, and then re-enable motor;
        digitalWrite(pinEN, LOW);
        analogWrite(pinA, motor_val);
        analogWrite(pinB, 0);
        digitalWrite(pinEN, HIGH);
        direction = 1;
    }
    else if (PWM < 0)
    {
        PWM *= -1;
        motor_val = (int16_t) round(map(PWM, 0, 100, 0, 255));
        //Disable motor briefly, change values on control pins, and then re-enable motor;
        digitalWrite(pinEN, LOW);
        analogWrite(pinB, motor_val);
        analogWrite(pinA, 0);
        digitalWrite(pinEN, HIGH);
        direction = -1;
    }
    else
    {
        digitalWrite(pinEN, LOW);
        analogWrite(pinB, 0);
        analogWrite(pinA, 0);
        digitalWrite(pinEN, HIGH);
        direction = 0;
    }
}

void MotorDriver::brake(void)
{
    //Brake the motor with the max PWM allowed by the PWM_max value
    //The L298N motor driver allows for a fast motor stop when both inputs are high
    uint8_t stop = (uint8_t) round(map(PWM_max, 0, 100, 0, 255));
    digitalWrite(pinEN, LOW);
    analogWrite(pinB, stop);
    analogWrite(pinA, stop);
    digitalWrite(pinEN, HIGH);
    direction = 0;
}