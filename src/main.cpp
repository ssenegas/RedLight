#include <Arduino.h>

class Led {

  private:
    byte ledPin;
    unsigned long eventTime;
    unsigned long previousMillis;
    bool pinOnOff;

  public:
    Led(byte pin) : Led(pin, 0) {
    }

    Led(byte pin, unsigned long interval) {
      ledPin = pin;
      eventTime = interval;
      previousMillis = 0;
      pinOnOff = false;

      pinMode(ledPin, OUTPUT);
      digitalWrite(ledPin, pinOnOff);
    }

    void turnOn() {
      pinOnOff = true;
    }

    void turnOff() {
      pinOnOff = false;
    }

    void setBlinking(unsigned long interval) {
      eventTime = interval;
    }

    void update(unsigned long millis) {
      if (eventTime > 0) {
        unsigned long currentTime = millis;
        if (currentTime - previousMillis >= eventTime) {
          previousMillis = currentTime;
          pinOnOff = ! pinOnOff;
        }
      }
      digitalWrite(ledPin, pinOnOff);
    }
};

class TrafficLight {

  private:
    const byte PIN_RED = 2;
    const byte PIN_YELLOW = 3;
    const byte PIN_GREEN = 4;

    Led leds[3] = { Led(PIN_RED), Led(PIN_YELLOW), Led(PIN_GREEN) };

  public:
    enum Color { RED = 0, YELLOW, GREEN };

    TrafficLight() {
    }

    void turnOn(Color c) {
      leds[c].turnOn();
    }

    void turnOff(Color c) {
      leds[c].turnOff();
    }

    void setBlinking(Color c, unsigned long interval) {
      leds[c].setBlinking(interval);
    }

    // Message format [R|r]\d{4}[Y|y]\d{4}[G|g]\d{4}
    // Length message is 15 characters
    // Index for leds Red 1, Yellow 5, Green 10
    // Index for delay Red [1, 5], Yellow [6, 10], Green [11, 15]
    // Example r1000y0000G0000, Red is blinking with 1000 ms delay, Yellow is Off, Green is On
    void parse(String message) {
      isRedOn(message) ? turnOn(TrafficLight::RED) : turnOff(TrafficLight::RED);
      setBlinking(TrafficLight::RED, getRedDelay(message));

      isYellowOn(message) ? turnOn(TrafficLight::YELLOW) : turnOff(TrafficLight::YELLOW);
      setBlinking(TrafficLight::YELLOW, getYellowDelay(message));

      isGreenOn(message) ? turnOn(TrafficLight::GREEN) : turnOff(TrafficLight::GREEN);
      setBlinking(TrafficLight::GREEN, getGreenDelay(message));
    }

    void update(unsigned long millis) {
      for (int c = RED; c <= GREEN; c++) {
        leds[c].update(millis);
      }
    }

  private:
    bool isRedOn(String incomingData) {
      return incomingData.charAt(0) == 'R';
    }

    bool isYellowOn(String incomingData) {
      return incomingData.charAt(5) == 'Y';
    }

    bool isGreenOn(String incomingData) {
      return incomingData.charAt(10) == 'G';
    }

    int getRedDelay(String incomingData)
    {
      return incomingData.substring(1, 5).toInt();
    }

    int getYellowDelay(String incomingData) {
      return incomingData.substring(6, 10).toInt();
    }

    int getGreenDelay(String incomingData) {
      return incomingData.substring(11, 15).toInt();
    }
};

// put function declarations here:

TrafficLight trafficLight;

void setup() {
  Serial.begin(9600);
}

void loop() {
  unsigned long currentTime = millis();

  if (Serial.available() > 0 ) {
    // read the incoming data and print it to the serial monitor
    String message = Serial.readString();
    
    Serial.print("Incoming message :");
    Serial.println(message);

    trafficLight.parse(message);
  }

  trafficLight.update(currentTime);
}

// put function definitions here:
