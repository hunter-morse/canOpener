#ifndef TASK_LIMIT_SWITCH_H
#define TASK_LIMIT_SWITCH_H

#include "STM32FreeRTOS.h"
#include <Arduino.h>
#include "PrintStream.h"
#include "taskshare.h"
#include "../lib/sensorLib/limitSwitch.h"
#include "../shares.h"

void taskCheckLimitSwitches(void *p_params);

#endif