#include <Arduino.h>
#include "Led.h"
#include "TrafficLight.h"

// put function declarations here:

TrafficLight trafficLight;

void setup() {
  Serial.begin(9600);
}

void loop() {
  unsigned long currentTime = millis();

  if (Serial.available() >= 15 ) {
    // read the incoming data from serial buffer and print it to the serial monitor
    String command = Serial.readStringUntil('\0');

    if (command.length() >= 15) {
      Serial.print("command read from serial:");
      Serial.println(command);
      Serial.print("length:");
      Serial.println(command.length());

      trafficLight.parse(command);
    }
  }

  trafficLight.update(currentTime);
}

// put function definitions here:
