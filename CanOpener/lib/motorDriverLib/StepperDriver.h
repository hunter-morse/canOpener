/**
 * @file StepperDriver.h
 * @brief Header file for the StepperDriver class
 * @details This file is what is included when the StepperDriver class is included. It includes protections against multiple inclusions
 * 
 * @author Ben Bons
 * @date Nov 18, 2021
 * */

#ifndef Stepper_Driver_h
#define Stepper_Driver_h

#include <Arduino.h>
#include <Stepper.h>


/**
 * @brief Class for driving a stepper motor
 * @details This class uses the Arduino Stepper module and adds some functionality on top of that class. 
 *          The driver also has the ability to track the position of the stepper motor. 
 **/
class StepperDriver
{
    public:
        StepperDriver(uint8_t new_id, uint8_t stepsPerRev, uint8_t pin1, uint8_t pin2, 
                    uint8_t pin3, uint8_t pin4, uint8_t enable, uint8_t new_speed);

        void move(int16_t steps);

        int32_t getPosition(void);

        void setPosition(int32_t new_pos);

        void setSpeed(float new_speed);

        float getSpeed(void);

        uint8_t getID(void);

    protected:
        /// The current position of the motor
        int32_t curr_pos;
        /// The ID of the StepperDriver object
        uint8_t id;
        /// The pin connected to the positive side of the A coil
        uint8_t pin_A;
        /// The pin connected to the negative side of the A coil
        uint8_t pin_Abar;
        /// The pin connected to the positive side of the B coil
        uint8_t pin_B;
        /// The pin connected to the negative side of the A coil
        uint8_t pin_Bbar;
        /// The enable pin
        uint8_t pin_enable;
        /// The speed in RPM the motor rotates at
        float speed;
        /// A pointer to a Stepper object 
        Stepper* p_Stepper; 

};

#endif