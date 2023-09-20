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

  if (Serial.available() > 0 ) {
    // read the incoming data from serial buffer and print it to the serial monitor
    String message = Serial.readString();
    
    Serial.print("message read from serial:");
    Serial.println(message);

    trafficLight.parse(message);
  }

  trafficLight.update(currentTime);
}

// put function definitions here:
