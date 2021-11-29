#include <Arduino.h>
#include "MotorDriver.h"
#include "StepperDriver.h"

const bool TESTING_SERVO = true;
const uint32_t pin_dc_pos = PA8;
const uint32_t pin_dc_neg = PA9;
const uint32_t pin_dc_enable = PA13;
MotorDriver* p_motor;

void setup() {
  Serial.begin(115200);
  if (TESTING_SERVO)
  {
    delay(2000);
    p_motor = new MotorDriver(1, pin_dc_pos, pin_dc_neg, pin_dc_enable, 75, 500);
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
}