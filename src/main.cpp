#include <Arduino.h>
#include "Led.h"
#include "TrafficLight.h"

// put function declarations here:

TrafficLight trafficLight;

void setup() {
  Serial.begin(9600);
  trafficLight.parse("R2000Y3000G2000"); // demo mode as default
}

void loop() {
  unsigned long currentTime = millis();

  if (Serial.available() >= 15 ) {
    String command = Serial.readStringUntil('\0');

    if (command.length() >= 15) {
      trafficLight.parse(command);
    }
  }

  trafficLight.update(currentTime);
}

// put function definitions here:
