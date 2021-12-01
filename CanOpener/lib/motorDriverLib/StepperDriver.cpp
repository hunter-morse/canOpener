/**
 * @file StepperDriver.cpp
 * @brief Contains the functionality for the StepperDriver class
 * 
 * @author Ben Bons
 * @date Nov 30, 2021
 * */

#include <Arduino.h>
#include "StepperDriver.h"
#include <Stepper.h>

/**
 * @brief Constructor for the StepperDriver object
 * @details In the constructor, the pins for the stepper are defined, and the enable pin.
 *          In the constructor, the position is initialized to 0, the enable pin is set high, and
 *          a new Stepper object is created from the Arduino library. The object also contains an id
 *          that can be read from the object
 * 
 * @param new_id The ID to be set to the object
 * @param stepsPerRev The number of steps per revolution for the given stepper motor, which equals 360 degrees/degrees per step
 * @param pin1 The pin that is connected to the positive side of the first loop - also known as Phase A.
 * @param pin2 The pin that is connected to the negative side of the first loop - also known as Phase A-Bar.
 * @param pin3 The pin that is connected to the positive side of the second loop - also known as Phase B.
 * @param pin4 The pin that is connected to the negative side of the second loop - also known as Phase B-Bar.
 * @param enable The pin that is connected to the enable pin of the motor driver.
 * @param new_speed The speed in RPM that you want the stepper motor to spin at.
 * */
StepperDriver::StepperDriver(uint8_t new_id, uint8_t stepsPerRev, uint8_t pin1, uint8_t pin2, 
                            uint8_t pin3, uint8_t pin4, uint8_t enable, uint8_t new_speed)
{
    id = new_id;
    pin_A = pin1;
    pin_Abar = pin2;
    pin_B = pin3;
    pin_Bbar = pin4;
    pin_enable = enable;
    
    p_Stepper = new Stepper(stepsPerRev, pin1, pin2, pin3, pin4);
    
    setSpeed(new_speed);

    setPosition(0);

    pinMode(pin_enable, OUTPUT);
    digitalWrite(pin_enable, HIGH);
}


/**
 * @brief Moves the stepper motor a specified number of steps
 * @details This function moves the stepper the number of steps, which correlates to the number of degrees equal to degrees/step * steps.
 *          The motor moves at the speed according to StepperDriver::setSpeed()
 * 
 * @param steps The number of steps for the motor to rotate through.
 * */
void StepperDriver::move(int16_t steps)
{
    p_Stepper->step(steps);
    curr_pos += steps;
}


/**
 * @brief Gets the current position of the stepper motor
 * @details The position that is returned is returned in terms of total steps, so it will need to be converted to other units
 * 
 * @return The number of steps that the motor has rotated through.  
 * */
int32_t StepperDriver::getPosition(void)
{
    return curr_pos;
}

/**
 * @brief Sets the current position of the stepper motor
 * @details This method takes in an input argument and changes the position that will be returned when StepperDriver::getPosition()
 *          is called. This is called in the constructor to set the position to 0.
 * 
 * @param new_pos The new position to be set
 * */
void StepperDriver::setPosition(int32_t new_pos)
{
    curr_pos = new_pos;
}

/**
 * @brief Sets the speed of the stepper motor in RPM
 * @details This is a wrapper method for the Stepper.h setSpeed() function
 * 
 * @param new_speed The speed in RPM that the stepper motor will rotate at
 * */
void StepperDriver::setSpeed(float new_speed)
{
    p_Stepper->setSpeed((long) new_speed);
    speed = new_speed;
}


/**
 * @brief Returns the speed of the stepper motor in RPM
 * @details
 * 
 * @return The speed of the motor in RPM
 * */
float StepperDriver::getSpeed(void)
{
    return speed;
}

/**
 * @brief Returns the ID of the StepperDriver object
 * @details
 * 
 * @return The ID of the StepperDriver object
 * */
uint8_t StepperDriver::getID(void)
{
    return id;
}