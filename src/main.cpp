#include <Arduino.h>

class Led {
private:
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
    if (waitTimeInMs > 0) {
      if ((millis() - previousMillis) >= waitTimeInMs) {
        previousMillis = millis();
        pinOnOff = !pinOnOff;
      }
    }
    digitalWrite(ledPin, pinOnOff);
  }
};

class TrafficLight {
private:
  const int PIN_RED = 2;
  const int PIN_YELLOW = 3;
  const int PIN_GREEN = 4;

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

bool isRedOn(String incomingData);
bool isYellowOn(String incomingData);
bool isGreenOn(String incomingData);
int getRedDelay(String incomingData);
int getYellowDelay(String incomingData);
int getGreenDelay(String incomingData);

TrafficLight trafficLight;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.setTimeout(10);
  // int result = myFunction(2, 3);
}

const unsigned int MESSAGE_LENGTH = 15;

// Message format [R|r]\d{4}[Y|y]\d{4}[G|g]\d{4}
// Length message is 15 characters
// Index for leds Red 1, Yellow 5, Green 10
// Index for delay Red [1, 5], Yellow [6, 10], Green [11, 15]
// Example r1000y0000G0000, Red is blinking with 1000 ms delay, Yellow is Off, Green is On

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0 ) {
    // Read the incoming data and print it to the serial monitor
    String incomingData = Serial.readString();
    
    Serial.print("Incoming data :");
    Serial.println(incomingData);

    trafficLight.setOn(TrafficLight::Color::RED, isRedOn(incomingData));
    trafficLight.setBlinking(TrafficLight::Color::RED, getRedDelay(incomingData));

    trafficLight.setOn(TrafficLight::Color::YELLOW, isYellowOn(incomingData));
    trafficLight.setBlinking(TrafficLight::Color::YELLOW, getYellowDelay(incomingData));

    trafficLight.setOn(TrafficLight::Color::GREEN, isGreenOn(incomingData));
    trafficLight.setBlinking(TrafficLight::Color::GREEN, getGreenDelay(incomingData));
  }
  trafficLight.update();

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

bool isRedOn(String incomingData) {
  return incomingData.charAt(0) == 'R';
}

bool isYellowOn(String incomingData) {
  return incomingData.charAt(5) == 'Y';
}

bool isGreenOn(String incomingData) {
  return incomingData.charAt(10) == 'G';
}

int getRedDelay(String incomingData) {
  return incomingData.substring(1, 5).toInt();
}

int getYellowDelay(String incomingData) {
  return incomingData.substring(6, 10).toInt();
}

int getGreenDelay(String incomingData) {
  return incomingData.substring(11, 15).toInt();
}
