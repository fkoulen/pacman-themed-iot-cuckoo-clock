#include <Arduino.h>
#include "main/Constants.h"

void setup() {
    Serial.begin(SERIAL_BAUD_RATE);
    pinMode(0, INPUT);
}

void loop() {
//    if (digitalRead(0)) {
//        Serial.println("Button pressed");
//        delay(500); // Debounce button press
//    }
    Serial.println(digitalRead(0));
    delay(500);
}

