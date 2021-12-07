/**
 * @file    limitSwitch.cpp
 *          Driver to interface with limit switches
 * @author  Hunter Morse
 * @date    Nov xx, 2021         
 */

#include "limitSwitch.h"

LimitSwitch::LimitSwitch(uint8_t switchID, uint8_t inPin){
    // Set protected variables
    this->switchID = switchID;
    this->inPin = inPin;
    this->triggered = false;

    // Setup pins
    pinMode(inPin, INPUT);
}

bool LimitSwitch::readSwitch(void){
    // Check if pin is triggered and set value appropriately
    if(digitalRead(inPin)){
        triggered = true;
    } else {
        triggered = false;
    }

    return triggered;
}

