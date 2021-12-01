/**
 * @file main.cpp
 * 
 */
#include <Arduino.h>
#include <STM32FreeRTOS.h>
#include <PrintStream.h>
#include "shares.h"

Share<float> currentTemp("Current Temperature");
Share<float> currentTemp;
Share<bool> canDetected;
Share<bool> canTopDetected;
Share<bool> canTabDetected;

void setup(){
    //Setup Code
}

void loop(){
    //Will not be used bc of FreeRTOS
}
