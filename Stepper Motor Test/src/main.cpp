#include <Arduino.h>
#include <Stepper.h>


Stepper myStepper(200, PB4, PB5, PB0, PB1);
uint32_t en1 = PA13;
uint32_t en2 = PC15;
/*uint32_t p1 = PB4;
uint32_t p2 = PB5;
uint32_t p1 = PB4;*/



void setup() {
  Serial.begin(115200);
  pinMode(en1, OUTPUT);
  pinMode(en2, OUTPUT);

  //pinMode(, OUTPUT);

  digitalWrite(en1, HIGH);
  digitalWrite(en2, HIGH);
  myStepper.setSpeed(75);
  Serial.println("Started");
}

void loop() {
  myStepper.step(200);
  Serial.println("200 Steps");
  delay(1000);
}