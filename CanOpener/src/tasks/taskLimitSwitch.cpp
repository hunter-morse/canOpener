/**
 * @file    taskLimitSwitch.cpp
 *          Task to check the status of each limit switch
 *          The status of each limit switch is put into its respective share
 *          so that the taskMoveMachine can function.
 * @author  Hunter Morse
 * @date    Nov xx, 2021
 */

#include "taskLimitSwitch.h"

/**
 * @brief   Task: Check Limit Switches
 * @details Period: 100ms, Priority: 4/4
 *          Check the status of each limit switch the result into its respective share
 * @param   p_param: task parameters
 */

void taskCheckLimitSwitches(void *p_params){
    // Instantiate limit switches
    LimitSwitch switch_kill(0, INLIM1);        // canDetect
    LimitSwitch switch_canTopDetect(1, INLIM2);     // canTopDetect
    LimitSwitch switch_canTabDetect(2, INLIM3);     // canTabDetect

    // Included to increase timing accuracy (https://canvas.calpoly.edu/courses/57860/files/5478349?wrap=1)
    TickType_t xLastWakeTime = xTaskGetTickCount();

    Serial << "Task Limit Switch Begun" << endl;

    for(;;){
        // check the status of each limit switch and put them to the respective shares
        kill.put(!switch_kill.readSwitch()); //Uncomment to use a limit switch for can detecting
        canTopDetected.put(!switch_canTopDetect.readSwitch());
        canTabDetected.put(!switch_canTabDetect.readSwitch());
        //Serial << "Switch 1: "<< switch_canDetect.readSwitch() << endl;
        //Serial << "Switch 2: "<< switch_canTopDetect.readSwitch() << endl;
        //Serial << "Switch 3: "<< switch_canTabDetect.readSwitch() << endl;

        vTaskDelayUntil(&xLastWakeTime, 100);
    }
}