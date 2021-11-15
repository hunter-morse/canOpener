#include <Arduino.h>
#include <PrintStream.h>
#include <Wire.h>
#include "TempSensor.h"


uint8_t scl_pin = PB8;
uint8_t sda_pin = PB9;

uint8_t addr = 0b0011000;

TempSensor sensor(scl_pin, sda_pin, addr);


void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial << "Device Address: " << sensor.getManuCode() << endl;
  Serial << "Temp in C: " << sensor.getTempC() << endl;
  Serial << "Temp in F: " << sensor.getTempF() << endl << endl;
  delay(1000);
}