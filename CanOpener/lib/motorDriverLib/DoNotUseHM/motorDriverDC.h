#ifndef MOTOR_DRIVER_DC_H
#define MOTOR_DRIVER_DC_H

#include <Arduino.h>
#include <math.h>

class MotorDriverDC{
    protected:
        uint8_t motorID;                    // User defined
        
        uint8_t enablePin;                  // Motor pins
        uint8_t pin1;                       // (+)
        uint8_t pin2;                       // (-)

        uint8_t PWM;                        // Accept PWM value from 0x00 to 0xFF (map to 0-100)
        bool movingForward;                 // Indicate if motor is moving in the positive or negative direction

    public:
        MotorDriverDC(uint8_t motorID, uint8_t enablePin, uint8_t pin1, uint8_t pin2);

        uint8_t getID(void);                // Get motor ID

        uint8_t reverse(void);              // Reverse polarity of motor
        uint8_t move(int8_t pwm);          // Move some number of steps
};



#endif