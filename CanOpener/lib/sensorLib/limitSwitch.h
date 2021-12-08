#ifndef LIMIT_SWITCH_H
#define LIMIT_SWITCH_H

#include <Arduino.h>


/**
 * @brief Class which reads from a limit switch
 * @details This class reads a limit switch and determines which state it is in. 
 *          Note that limit switches can be wired pretty differently from switch to
 *          switch, so it is up to the user to determine which boolean value corresponds with
 *          each switch state
 * */
class LimitSwitch{
    protected:
        /// ID of switch
        uint8_t switchID;
        /// Input pin on board   
        uint8_t inPin;
        /// Triggered status
        bool triggered;     

    public:
        LimitSwitch(uint8_t switchID, uint8_t inPin);

        bool readSwitch(void);
};


#endif