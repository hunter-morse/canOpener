/**
 * @file shares.h
 * @brief A simple file for containing all the shares and queues for the canOpener project
 * */

#ifndef SHARES_H
#define SHARES_H

#include <Arduino.h>
#include <STM32FreeRTOS.h>
#include "taskshare.h"
#include "taskqueue.h"

///The share into which the current temperature from taskTemp is placed
extern Share<float> currentTemp;

///The share which indicates whether or not the can is in the device
extern Share<bool> canDetected;

///The share which indicates whether or not the can top has been detected
extern Share<bool> canTopDetected;

///The share which indicates whether or not the can tab has been detected
extern Share<bool> canTabDetected;

//The share that holds the current encoder 1 position
extern Share<int64_t> enc1;

//The share that holds the current encoder 2 position
extern Share<int64_t> enc2;

#endif