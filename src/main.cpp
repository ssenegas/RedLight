#include <Arduino.h>

#define PIN_RED 2
#define PIN_YELLOW 3
#define PIN_GREEN 4

class Led {
  int ledPin;
  long waitTimeInMs;
  unsigned long previousMillis;
  bool pinOnOff;

public:
  Led(int pin) : Led(pin, 0) {
  }

  Led(int pin, long wait) {
    ledPin = pin;
    waitTimeInMs = wait;
    pinOnOff = false;

    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, pinOnOff);
  }

  void setOn(bool on) {
    if (on == pinOnOff)
      return;

    pinOnOff = on;
    waitTimeInMs = 0;
    previousMillis = millis();
  }

  void setBlinking(long wait) {
    waitTimeInMs = wait;
  }

  void update() {
    if (waitTimeInMs > 0)
    {
      if ((millis() - previousMillis) >= waitTimeInMs)
      {
        previousMillis = millis();
        pinOnOff = !pinOnOff;
      }
    }
    digitalWrite(ledPin, pinOnOff);
  }
};

class TrafficLight {
private:
  Led leds[3] = {Led(PIN_RED), Led(PIN_YELLOW), Led(PIN_GREEN)};

public:
  enum Color { RED = 0, YELLOW, GREEN };

  TrafficLight() {
  }

  void setOn(Color c, bool on) {
    leds[c].setOn(on);
  }

  void setBlinking(Color c, long wait) {
    leds[c].setBlinking(wait);
  }

  void update() {
    for (int c = RED; c <= GREEN; c++) {
      leds[c].update();
    }
  }
};

// put function declarations here:
int myFunction(int, int);

TrafficLight trafficLight;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);

  // int result = myFunction(2, 3);
}

const unsigned int MAX_MESSAGE_LENGTH = 4;

void loop() {

  static char message[MAX_MESSAGE_LENGTH];
  static unsigned int message_pos = 0;

  // put your main code here, to run repeatedly:
  if (Serial.available() >= 3) {
    Serial.readBytes(message, 3);

    trafficLight.setOn(TrafficLight::Color::RED, (message[0] == 'R'));
    trafficLight.setOn(TrafficLight::Color::YELLOW, (message[1] == 'A'));
    trafficLight.setOn(TrafficLight::Color::GREEN, (message[2] == 'G'));
  }
  trafficLight.update();
  delay(99);

  /*
  static u32 i = 0;
  Serial.println(i);
  delay(500);
  i++;*/
}

// put function definitions here:
int myFunction(int x, int y)
{
  return x + y;
}