#include <Arduino.h>
#include "TrafficLight.h"

TrafficLight::TrafficLight() {
}

TrafficLight::~TrafficLight() {
    delete leds[RED];
    delete leds[YELLOW];
    delete leds[GREEN];
}

void TrafficLight::turnOn(Color c) {
    leds[c]->turnOn();
}

void TrafficLight::turnOff(Color c) {
    leds[c]->turnOff();
}

void TrafficLight::setBlinkRate(Color c, unsigned long blinkRate) {
    leds[c]->setBlinkRate(blinkRate);
}

void TrafficLight::update(unsigned long currentTime) {
    leds[RED]->update(currentTime);
    leds[YELLOW]->update(currentTime);
    leds[GREEN]->update(currentTime);
}

// Command format [R|r]\d{4}[Y|y]\d{4}[G|g]\d{4}
// Length command is 15 characters
// Index for status RED 0, YELLOW 5, GREEN 10
// Index for interval Red [1, 5[, Yellow [6, 10[, Green [10, 15[
// Example r1000y0000G0000, Red is blinking with 1000 ms interval, Yellow is Off, Green is On
void TrafficLight::parse(String command) {
    String redCommand = command.substring(0, 5);
    String yellowCommand = command.substring(5, 10);
    String greenCommand = command.substring(10, 15);

    processLED(redCommand, RED);
    processLED(yellowCommand, YELLOW);
    processLED(greenCommand, GREEN);
}

void TrafficLight::processLED(String command, Color c) {
  char s = command.charAt(0);
  int interval = command.substring(1).toInt();

  if (s == status[c].on || s == status[c].off) {
    s == status[c].on ? turnOn(c) : turnOff(c);
    setBlinkRate(c, interval);
  } 
}
