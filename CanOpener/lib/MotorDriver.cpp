/**
 * @file MotorDriver.cpp
 * @brief Contains the functionality of the MotorDriver class
 * 
 * @author Ben Bons
 * @date Nov 30, 2021
 * */

#include "MotorDriver.h"
#include <Arduino.h>

/**
 * @brief Constructor for the MotorDriver class
 * @details This constructor sets various parameters for the MotorDriver object. These include the pins the motor is connected to,
 *          the enable pin, the max/min PWM that can be sent to the motors, the braking delay, and an ID. Note that the braking delay
 *          at this point is blocking, so only short delays should be used, if at all. Another note - if the PWM bound is set to a
 *          number above 100, the bound will be set to 100.
 * 
 * @param new_id The ID of the motor, which has no effect on the function of the MotorDriver object
 * @param pos The pin name, i.e. PA0 or PC5, of the pin that is connected to the positive terminal of the motor.
 * @param neg The pin name of the pin that is connected to the negative terminal of the motor
 * @param enable The pin name of the pin that is connected to the enable pin on the physical motor driver chip
 * @param PWM_bound The PWM value, from 0 to 100, that is the maximum PWM value that can be written to either the positive or negative pin
 * @param b_delay The delay in ms, that the motor will break before switching the rotation direction of the motor - delay is blocking
 * */
MotorDriver::MotorDriver(uint8_t new_id, uint32_t pos, uint32_t neg, uint32_t enable, uint8_t PWM_bound, 
                        uint16_t b_delay)
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
    brake_delay = b_delay;

    //Set the motor and enable pins to OUTPUT
    pinMode(pinA, OUTPUT);
    pinMode(pinB, OUTPUT);
    pinMode(pinEN, OUTPUT);

    //Set the enable pin high
    digitalWrite(pinEN, HIGH);

    //Set the current direction -1: reverse, 0: stopped, 1: forward
    direction = 0;
    
}

/**
 * @brief Sets a new PWM value for the motor to be driven at
 * @details This PWM value is allowed to be any number from -1*PWM_bound (from the constructor) to PWM_bound.
 *          If a PWM value is outside the bounds, the motor will be driven at the appropriate bound. A positive PWM
 *          is moving forward, negative moving backward. Note that these PWM values are the percentage. Calling @c MotorDriver::move(1)
 *          will rotate forward at 1% PWM, not 100%.
 * 
 * @param new_PWM The PWM that the motor will be driven at, from -1*PWMbound <= new_PWM <= PWM_bound
 * */
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

/**
 * @brief Puts the motor into braking mode
 * @details When this function is called, PWM_bound is sent to both the positive and negative poles of the motor. This is braking mode
 *          for many motor drivers, instead of coast mode, as MotorDriver::move(0) would cause
 * */
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

/**
 * @brief Returns the PWM value that the motor is currently being driven at
 * @details
 * 
 * @return The current PWM value being sent to the motor
 * */
float MotorDriver::getPWM(void)
{
    return PWM;
}

/**
 * @brief Returns the ID set in the constructor
 * @details
 * 
 * @return The ID of the MotorDriver object
 * */
uint8_t MotorDriver::getID(void)
{
    return id;
}

/**
 * @brief Returns the current direction the motor is spinning
 * @details If the motor is spinning forward, 1 is returned. If spinning backwards, -1 is returned.
 *          If the motor is stopped, 0 is returned.
 * 
 * @return The direction of the motor, as specified above
 * */
int8_t MotorDriver::getDirection(void)
{
    return direction;
}