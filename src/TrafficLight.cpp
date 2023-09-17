#include <Arduino.h>
#include "TrafficLight.h"


TrafficLight::TrafficLight() {
}

void TrafficLight::turnOnRed() {
    turnOn(RED);
}

void TrafficLight::turnOnYellow() {
    turnOn(YELLOW);
}

void TrafficLight::turnOnGreen() {
    turnOn(GREEN);
}

void TrafficLight::turnOffRed() {
    turnOff(RED);
}

void TrafficLight::turnOffYellow() {
    turnOff(YELLOW);
}

void TrafficLight::turnOffGreen() {
    turnOff(GREEN);
}

void TrafficLight::setBlinkRate(Color c, unsigned long blinkRate) {
    if (blinkRate > 0) {
    leds[c].setBlinkRate(blinkRate);
    }
}

// Message format [R|r]\d{4}[Y|y]\d{4}[G|g]\d{4}
// Length message is 15 characters
// Index for leds Red 1, Yellow 5, Green 10
// Index for delay Red [1, 5], Yellow [6, 10], Green [11, 15]
// Example r1000y0000G0000, Red is blinking with 1000 ms delay, Yellow is Off, Green is On
void TrafficLight::parse(String message) {
    parseRedOn(message) ? turnOn(RED) : turnOff(RED);
    setBlinkRate(RED, parseRedDelay(message));
    parseYellowOn(message) ? turnOn(YELLOW) : turnOff(YELLOW);
    setBlinkRate(YELLOW, parseYellowDelay(message));
    parseGreenOn(message) ? turnOn(GREEN) : turnOff(GREEN);
    setBlinkRate(GREEN, parseGreenDelay(message));
}

void TrafficLight::update(unsigned long millis) {
    for (int c = RED; c <= GREEN; c++) {
    leds[c].update(millis);
    }
}

void TrafficLight::turnOn(Color c) {
      leds[c].turnOn();
}

void TrafficLight::turnOff(Color c) {
    leds[c].turnOff();
}

bool TrafficLight::parseRedOn(String message) {
    return message.charAt(0) == 'R';
}

bool TrafficLight::parseYellowOn(String message) {
    return message.charAt(5) == 'Y';
}

bool TrafficLight::parseGreenOn(String message) {
    return message.charAt(10) == 'G';
}

int TrafficLight::parseRedDelay(String message) {
    return message.substring(1, 5).toInt();
}

int TrafficLight::parseYellowDelay(String message) {
    return message.substring(6, 10).toInt();
}

int TrafficLight::parseGreenDelay(String message) {
    return message.substring(11, 15).toInt();
}