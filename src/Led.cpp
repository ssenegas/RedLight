#include <Arduino.h>
#include "Led.h"

Led::Led(byte pin) : Led(pin, 0) {
}

Led::Led(byte pin, unsigned long blinkRate) {
    ledPin = pin;
    blinkRateInMillis = blinkRate;
    previousMillis = 0;
    pinMode(ledPin, OUTPUT);
}

void Led::turnOn() {
    digitalWrite(ledPin, HIGH);
}

void Led::turnOff() {
    digitalWrite(ledPin, LOW);
}

void Led::toogle() {
    digitalWrite(ledPin, ! digitalRead(ledPin));
}

bool Led::isOn() {
    return digitalRead(ledPin) == HIGH;
}

unsigned long Led::getBlinkRate() {
    return blinkRateInMillis;
}

void Led::setBlinkRate(unsigned long blinkRate) {
    blinkRateInMillis = blinkRate;
}

void Led::update(unsigned long millis) {
    if (blinkRateInMillis > 0) {
        unsigned long currentTime = millis;
        if (currentTime - previousMillis >= blinkRateInMillis) {
            previousMillis = currentTime;
            toogle();
        }
    }
}
