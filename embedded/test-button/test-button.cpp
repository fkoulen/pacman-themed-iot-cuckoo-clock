#include <Arduino.h>
#include "main/Constants.h"

void setup() {
    Serial.begin(SERIAL_BAUD_RATE);
    pinMode(NEXT_BUTTON_PIN, INPUT);
}

void loop() {
    Serial.println(digitalRead(NEXT_BUTTON_PIN));
    delay(500);
}

