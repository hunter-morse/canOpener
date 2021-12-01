/**
 * @file
 * */

#ifndef TASKENCODER_H
#define TASKENCODER_H

#include <Arduino.h>
#include <STM32FreeRTOS.h>
#include <PrintStream.h>
#include "../shares.h"
#include "../pins.h"

void taskEncoder(void* p_params);

#endif