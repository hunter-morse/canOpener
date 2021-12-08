/**
 * @file    limitSwitch.cpp
 *          Driver to interface with limit switches
 * @author  Hunter Morse
 * @date    Nov 30, 2021         
 */

#include "limitSwitch.h"
/**
 * @brief Constructor for the LimitSwitch class
 * @details This constructor sets an ID for the switch and sets which pin the limit
 *          switch is connected to.
 * 
 * @param switchID The ID of this object
 * @param inPin The pin the limit switch is connected to.
 * */
LimitSwitch::LimitSwitch(uint8_t switchID, uint8_t inPin){
    // Set protected variables
    this->switchID = switchID;
    this->inPin = inPin;
    this->triggered = false;

    // Setup pins
    pinMode(inPin, INPUT);
}

/**
 * @brief Reads the condition of the limit switch
 * @details Returns true if the inPin is set high. This doesn't necessarily mean depressed or not,
 *          because it relies on how the limit switch is wired
 * 
 * @return The state of the switch: Changes from false->true or true->false when the switch is pressed depending on wiring.
 * */
bool LimitSwitch::readSwitch(void){
    // Check if pin is triggered and set value appropriately
    if(digitalRead(inPin)){
        triggered = true;
    } else {
        triggered = false;
    }

    return triggered;
}

