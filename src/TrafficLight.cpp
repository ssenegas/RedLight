#include <Arduino.h>
#include "TrafficLight.h"

TrafficLight::TrafficLight() {
    statusOn[RED] = 'R';
    statusOn[YELLOW] = 'Y';
    statusOn[GREEN] = 'G';

    statusOff[RED] = 'r';
    statusOff[YELLOW] = 'y';
    statusOff[GREEN] = 'g';
}

void TrafficLight::setBlinkRate(Color c, unsigned long blinkRate) {
    leds[c].setBlinkRate(blinkRate);
}

void TrafficLight::update(unsigned long currentTime) {
    for (int c = RED; c <= GREEN; c++) {
        leds[c].update(currentTime);
    }
}

void TrafficLight::turnOn(Color c) {
    leds[c].turnOn();
}

void TrafficLight::turnOff(Color c) {
    leds[c].turnOff();
}

void TrafficLight::turnOnOff(Color c, bool value) {
    value ? leds[c].turnOn() : leds[c].turnOff();
}

// Message format [R|r]\d{4}[Y|y]\d{4}[G|g]\d{4}
// Length message is 15 characters
// Index for leds Red 1, Yellow 5, Green 10
// Index for delay Red [1, 5[, Yellow [6, 10[, Green [10, 15[
// Example r1000y0000G0000, Red is blinking with 1000 ms delay, Yellow is Off, Green is On
void TrafficLight::parse(String command) {
    String redCommand = command.substring(0, 5);
    String yellowCommand = command.substring(5, 10);
    String greenCommand = command.substring(10, 15);

    processLED(redCommand, RED);
    processLED(yellowCommand, YELLOW);
    processLED(greenCommand, GREEN);
}

void TrafficLight::processLED(String command, Color c) {
  Serial.print("command:");
  Serial.println(command);
  Serial.print("command length:");
  Serial.println(command.length());

  char status = command.charAt(0);
  int interval = command.substring(1).toInt();

  Serial.print("status:");
  Serial.println(status);
  Serial.print("interval:");
  Serial.println(interval);

  if (status == statusOn[c] || status == statusOff[c]) {
    turnOnOff(c, status == statusOn[c]);
    setBlinkRate(c, interval);
  } 
}
