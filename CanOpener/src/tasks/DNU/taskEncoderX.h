#ifndef TASK_ENCODER_H
#define TASK_ENCODER_H

#include <Arduino.h>
#include <STM32FreeRTOS.h>
#include <PrintStream.h>
#include "../shares.h"
#include "../pins.h"
#include "../../lib/sensorLib/encoder_counter.h"

void taskEncoder(void *p_params);

#endif