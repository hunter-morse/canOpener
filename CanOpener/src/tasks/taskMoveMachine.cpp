#include "taskMoveMachine.h"

void taskMoveMachine(void *p_params){
    // Setup task vars
    uint8_t state = 0;          // State of task specifies which switches are checked
    
    // Instantiate motor drivers
    uint8_t pwm = 100;
    uint8_t stepsPerRev = 200;
    uint8_t stepSpeed = 0;

    MotorDriver dcMotorBase(0, DC1a, DC1b, DCEN1, pwm);     // base motor
    MotorDriver dcMotorHead(1, DC2a, DC2b, DCEN2, pwm);     // head motor
    StepperDriver stepMotor(0, stepsPerRev, STEP1a, STEP1b, STEP1c, STEP1d, STEP1EN, stepSpeed);    // stepper motor


    // Included to increase timing accuracy (https://canvas.calpoly.edu/courses/57860/files/5478349?wrap=1)
    TickType_t xLastWakeTime = xTaskGetTickCount();

    for(;;){
        // Always check canDetect
        if(state = 0){
            if(canDetected.get()){
                // if can detected then move to next state
                Serial.println("taskLimitSwitch-state0: Can detected");     // should be written to display
                state = 1;
            }
        } else if(state = 1){
            // always make sure the can is detected
            if(!canDetected.get()){
                // if no can detected then go back to state 0
                Serial.println("taskLimitSwitch-state1: Can not detected");
                state = 0;
            } else if(canTopDetected.get()){
                // if can top detected stop moving the head, pring message, and change state
                stepMotor.setSpeed(0);
                Serial.println("taskLimitSwitch-state1: Can top detected");
                state = 2;
            } else {
                // if can top not detected then move the head down and remain in current state
                stepMotor.setSpeed(200);
                stepMotor.setPosition(stepMotor.getPosition() - 50);
                // do nothing, stay in state 1
            }
        } else if (state = 2){
            // always make sure the can is detected
            if(!canDetected.get()){
                // if no can detected then go back to state 0
                Serial.println("taskLimitSwitch-state2: Can not detected");
                state = 0;
            } 
            // make sure can and top are detected
            else if (canDetected.get() && canTopDetected.get()){
                // check to see if tab has been found
                if (canTabDetected.get()){
                    // do not change state -- only change state if either the can/its top aren't detected
                    dcMotorBase.brake();        // stop rotating the base
                    Serial.println("taskLimitSwitch-state2: Can tab found!");                   
                } else {
                    // tell base to rotate and remain in state 2
                    dcMotorBase.move(30);       // rotate the base at 30% speed (pwm)
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