/**
 * 
 * 
 */

#ifndef MOTOR_DRIVER_STEP_H
#define MOTOR_DRIVER_STEP_H

#include <Arduino.h>
#include <math.h>

class MotorDriverStepper{
    protected:
        uint8_t motorID;                // User defined
        uint8_t stepsPerRev;            // Specified by motor

        int32_t curr_pos;               // Init at 0
        uint8_t rpm;                    // Desired RPM
        
        uint8_t enablePin;              // Motor pins
        uint8_t pin1;                   // 1(+)
        uint8_t pin2;                   // 1(-)
        uint8_t pin3;                   // 2(+)
        uint8_t pin4;                   // 2(-)
        


    public:
        MotorDriverStepper(uint8_t motorID, uint8_t enablePin, uint8_t stepsPerRev, uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4, uint8_t rpm);

        uint8_t getID(void);                // Get motor ID

        uint8_t reverse(void);              // Reverse polarity of motor
        uint8_t move(uint8_t numSteps);     // Move some number of steps

        uint8_t setPosition();              // Set curr_pos
        uint8_t getPosition();              // Retrieve curr_pos

        uint8_t getSpeed();                 // 


}



#endif
