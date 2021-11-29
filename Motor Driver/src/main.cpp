#include <Arduino.h>
#include "MotorDriver.h"
#include "StepperDriver.h"

const bool TESTING_SERVO = false;

const uint32_t pin_dc_pos = PA8;
const uint32_t pin_dc_neg = PA9;
const uint32_t pin_dc_enable = PA13;
const uint32_t pin_step_enable = PC15;
const uint32_t pin_step_1 = PB4;
const uint32_t pin_step_2 = PB5;
const uint32_t pin_step_3 = PB0;
const uint32_t pin_step_4 = PB1;
MotorDriver* p_motor;
StepperDriver* p_stepper;

void setup() {
  Serial.begin(115200);
  if (TESTING_SERVO)
  {
    delay(2000);
    p_motor = new MotorDriver(1, pin_dc_pos, pin_dc_neg, pin_dc_enable, 75, 500);
  }
  else
  {
    delay(2000);
    p_stepper = new StepperDriver(1, 200, pin_step_1, pin_step_2, 
                                  pin_step_3, pin_step_4, pin_step_enable, 10);
  }
}

void loop() {
  if (TESTING_SERVO)
  {
    delay(500);
    p_motor->move(50);
    delay(500);
    p_motor->move(-50);
    delay(500);
    p_motor->move(-100);
    delay(500);
    p_motor->move(100);
    delay(500);
    p_motor->move(10);
    Serial.println(p_motor->getDirection());
    delay(2000);
    p_motor->move(-10);
    Serial.println(p_motor->getDirection());
    delay(2000);
    p_motor->move(0);
    Serial.println(p_motor->getDirection());
    delay(2000);
  }
  else
  {
    delay(500);
    p_stepper->move(20);
    Serial.print("Pos: ");
    Serial.println(p_stepper->getPosition());
    delay(500);
    p_stepper->move(25);
    Serial.print("Pos: ");
    Serial.println(p_stepper->getPosition());
    Serial.print("Speed: ");
    Serial.println(p_stepper->getSpeed());
    delay(500);
    p_stepper->setSpeed(20);
    p_stepper->move(-60);
    Serial.print("Pos: ");
    Serial.println(p_stepper->getPosition());
    Serial.print("Speed: ");
    Serial.println(p_stepper->getSpeed());
    p_stepper->setPosition(0);
    p_stepper->setSpeed(10);
  }
}