/**
 * @file StepperDriver.h
 * @brief Header file for the StepperDriver class
 * @details This file is what is included when the StepperDriver class is included. It includes protections against multiple inclusions
 * 
 * @author Ben Bons
 * @date 18 Nov, 2021
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
        int32_t curr_pos;
        uint8_t id;
        
        uint8_t pin_A;
        uint8_t pin_Abar;
        uint8_t pin_B;
        uint8_t pin_Bbar;
        uint8_t pin_enable;

        float speed;

        Stepper* p_Stepper; 

};

#endif