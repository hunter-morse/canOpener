#include <Arduino.h>
#include <PrintStream.h>


void setupX(void){
    Serial.begin(115200);
    delay(100);

    // Define pins to communicate with motor
    int DC1a    = PB4;
    int DC1b    = PB5;
    int DCEN1   = PA13;

    int DC2a    = PA10;
    int DC2b    = PA11;
    int DCEN2   = PA14;

    int DC3a    = PA5;
    int DC3b    = PB3;
    int DCEN3   = PC13;

    int DC4a    = PB10;
    int DC4b    = PB11;
    int DCEN4   = PC14;

    // Set pin modes
    pinMode(DC1a, OUTPUT);
    pinMode(DC1b, OUTPUT);
    pinMode(DCEN1, OUTPUT);

}

void loopX(void){
    Serial.println(".");
    delay(100);
}