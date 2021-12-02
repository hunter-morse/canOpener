#include "taskLimitSwitch.h"

// #define pin_canDetect       PC12
// #define pin_canTopDetect    PC4
// #define pin_canTabDetect    PC5 

void taskCheckLimitSwitches(void *p_params){
    // Instantiate limit switches
    LimitSwitch switch_canDetect(0, INLIM1);        // canDetect
    LimitSwitch switch_canTopDetect(1, INLIM2);     // canTopDetect
    LimitSwitch switch_canTabDetect(2, INLIM3);     // canTabDetect

    // Included to increase timing accuracy (https://canvas.calpoly.edu/courses/57860/files/5478349?wrap=1)
    TickType_t xLastWakeTime = xTaskGetTickCount();

    Serial << "Task Limit Switch Begun" << endl;

    for(;;){
        // check the status of each limit switch and put them to the respective shares
        canDetected.put(switch_canDetect.readSwitch());
        canTopDetected.put(switch_canTopDetect.readSwitch());
        canTabDetected.put(switch_canTabDetect.readSwitch());
        //Serial << "Switch 1: "<< switch_canDetect.readSwitch() << endl;
        Serial << "Switch 2: "<< switch_canTopDetect.readSwitch() << endl;
        Serial << "Switch 3: "<< switch_canTabDetect.readSwitch() << endl;

        vTaskDelayUntil(&xLastWakeTime, 100);
    }
}