#include <Arduino.h>
#include <PrintStream.h>
#include <Wire.h>


uint8_t scl_pin = PB8;
uint8_t sda_pin = PB9;

uint8_t addr = 0b0011000;
uint8_t reg = 0x06;

//TwoWire i2c(sda_pin, scl_pin);


void setup() {
  Serial.begin(115200);
  Wire.begin(sda_pin, scl_pin);
}

void loop() {
  Wire.beginTransmission(addr);
  Wire.write(reg);
  Wire.requestFrom(addr, (uint8_t) 2);
  Serial << "Bytes Avaliable: " << Wire.available() << endl;
  Serial << "Byte 1 Read: " << Wire.read() << endl << "Byte 2 Read: "<< Wire.read() << endl;
  Wire.endTransmission();
  delay(1000);
}