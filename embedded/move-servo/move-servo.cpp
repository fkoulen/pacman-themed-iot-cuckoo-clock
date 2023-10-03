/*
 * Move a servo motor from 0 to 180 degrees and back.
 *
 * @author F.S. Koulen
 * @date 2023-09-30
 */

#include <Arduino.h>
#include <Servo.h>

#define SERVO_PIN 16

Servo motor;

void setup() {
    motor.attach(SERVO_PIN);
}

void loop() {
    for (int angle = 0; angle <= 180; angle++) {
        motor.write(angle);
        delay(15);
    }

    for (int angle = 180; angle >= 0; angle--) {
        motor.write(angle);
        delay(15);
    }
}