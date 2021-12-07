#ifndef LIMIT_SWITCH_H
#define LIMIT_SWITCH_H

#include <Arduino.h>

class LimitSwitch{
    protected:
        uint8_t switchID;   /// ID of switch
        uint8_t inPin;      /// Input pin on board
        bool triggered;     /// Triggered status

    public:
        LimitSwitch(uint8_t switchID, uint8_t inPin);

        bool readSwitch(void);
};


#endif