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
extern Share<bool> canDetected;
extern Share<bool> canTopDetected;
extern Share<bool> canTabDetected;

#endif