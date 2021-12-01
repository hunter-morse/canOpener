#ifndef TASK_MOVE_MACHINE_H
#define TASK_MOVE_MACHINE_H

#include "STM32FreeRTOS.h"
#include <Arduino.h>
#include "PrintStream.h"
#include "taskshare.h"
#include "../lib/sensorLib/limitSwitch.h"
#include "../shares.h"
#include "../pins.h"

void taskMoveMachine(void *p_params);

#endif