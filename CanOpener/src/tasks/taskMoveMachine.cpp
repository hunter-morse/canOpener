#include "taskMoveMachine.h"

void taskMoveMachine(void *p_params){
    // Setup task vars
    uint8_t state = 0;          // State of task specifies which switches are checked
    
    // Instantiate motor drivers

    // Included to increase timing accuracy (https://canvas.calpoly.edu/courses/57860/files/5478349?wrap=1)
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for(;;){
        // Always check canDetect
        if(state = 0){
            if(canDetected.get()){
                Serial.println("taskLimitSwitch-state0: Can detected");
                state = 1;
            }
        } else if(state = 1){
            // always make sure the can is detected
            if(!canDetected.get()){
                Serial.println("taskLimitSwitch-state1: Can not detected");
                state = 0;
            } else if(canTopDetected.get()){
                Serial.println("taskLimitSwitch-state1: Can top detected");
                state = 2;
            } else {
                // do nothing, stay in state 1
            }
        } else if (state = 2){
            // always make sure the can is detected
            if(!canDetected.get()){
                Serial.println("taskLimitSwitch-state2: Can not detected");
                state = 0;
            } 
            // make sure can and top are detected
            else if (canDetected.get() && canTopDetected.get()){
                // check to see if tab has been found
                if (canTabDetected.get()){
                    Serial.println("taskLimitSwitch-state2: Can tab found!");
                    // do not change state -- only change state if either the can/its top aren't detected
                } else {
                    // tell base to rotate and remain in state 2
                }
            } 
            // if the can top is no longer detected
            else if (!canTopDetected.get()){
                // go back to the previous state
                Serial.println("taskLimitSwitch-state2: Can top no longer detected");
                state = 1;                
            }
            // the can is no detected
            else {
                Serial.println("taskLimitSwitch-state2: Can no longer detected");
                state = 0;
            }
        }
    }
}