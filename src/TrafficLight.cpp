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
    leds[c].setBlinkRate(blinkRate);
}

// Message format [R|r]\d{4}[Y|y]\d{4}[G|g]\d{4}
// Length message is 15 characters
// Index for leds Red 1, Yellow 5, Green 10
// Index for delay Red [1, 5], Yellow [6, 10], Green [11, 15]
// Example r1000y0000G0000, Red is blinking with 1000 ms delay, Yellow is Off, Green is On
void TrafficLight::parse(String message) {
    parseRedOn(message) ? turnOn(RED) : turnOff(RED);
    parseYellowOn(message) ? turnOn(YELLOW) : turnOff(YELLOW);
    parseGreenOn(message) ? turnOn(GREEN) : turnOff(GREEN);

    setBlinkRate(RED, parseRedBlinkRate(message));
    setBlinkRate(YELLOW, parseYellowBlinkRate(message));
    setBlinkRate(GREEN, parseGreenBlinkRate(message));
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
    bool isRedOn = message.charAt(0) == 'R';
    
    char strBuf[50];
    sprintf(strBuf, "parse is Red On = %s", isRedOn ? "true" : "false");
    Serial.println(strBuf);
    return isRedOn;
}

bool TrafficLight::parseYellowOn(String message) {
    bool isYellowOn = message.charAt(5) == 'Y';
    
    char strBuf[50];
    sprintf(strBuf, "parse is Yellow On = %s", isYellowOn ? "true" : "false");
    Serial.println(strBuf);
    return isYellowOn;
}

bool TrafficLight::parseGreenOn(String message) {
    bool isGreenOn = message.charAt(10) == 'G';

    char strBuf[50];
    sprintf(strBuf, "parse is Green On = %s", isGreenOn ? "true" : "false");
    Serial.println(strBuf);
    return isGreenOn;
}

int TrafficLight::parseRedBlinkRate(String message) {
    int redBlinkRate = message.substring(1, 5).toInt();

    char strBuf[50];
    sprintf(strBuf, "parse Red blink rate = %d", redBlinkRate);
    Serial.println(strBuf);
    return redBlinkRate;
}

int TrafficLight::parseYellowBlinkRate(String message) {
    int yellowBlinkRate = message.substring(6, 10).toInt();

    char strBuf[50];
    sprintf(strBuf, "parse yellow blink rate = %d", yellowBlinkRate);
    Serial.println(strBuf);
    return yellowBlinkRate;
}

int TrafficLight::parseGreenBlinkRate(String message) {
    int greenBlinkRate = message.substring(11, 15).toInt();

    char strBuf[50];
    sprintf(strBuf, "parse green blink rate = %d", greenBlinkRate);
    Serial.println(strBuf);
    return greenBlinkRate;
}
