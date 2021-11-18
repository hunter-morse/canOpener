#include <Arduino.h>
#include <PrintStream.h>

uint32_t pin_enable = PC13;
uint32_t pin_A = PA5;
uint32_t pin_B = PB3;

void setup() {
  Serial.begin(115200);
  pinMode(pin_enable, OUTPUT);
  pinMode(pin_A, OUTPUT);
  pinMode(pin_B, OUTPUT);
  digitalWrite(pin_enable, HIGH);

}

void loop() {
  digitalWrite(pin_A, HIGH);
  Serial.println("Pin A high");
  delay(1000);
  digitalWrite(pin_A, LOW);
  delay(500);
  digitalWrite(pin_B, HIGH);
  Serial.println("Pin B high");
  delay(1000);
  digitalWrite(pin_B, LOW);
}