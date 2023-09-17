#ifndef TrafficLight_h
#define TrafficLight_h
#include <Arduino.h> 
#include "Led.h"

class TrafficLight {

  private:
const byte PIN_RED = 2;
    const byte PIN_YELLOW = 3;
    const byte PIN_GREEN = 4;

    Led leds[3] = { Led(PIN_RED), Led(PIN_YELLOW), Led(PIN_GREEN) };
    
  public:
    enum Color { RED = 0, YELLOW, GREEN };

    TrafficLight();

    void turnOnRed();
    void turnOnYellow();
    void turnOnGreen();

    void turnOffRed();
    void turnOffYellow();
    void turnOffGreen();

    void setBlinkRate(Color c, unsigned long blinkRate);

    void parse(String message);
    void update(unsigned long millis);

private:
    void turnOn(Color c);
    void turnOff(Color c);
    bool parseRedOn(String message);
    bool parseYellowOn(String message);
    bool parseGreenOn(String message);
    int parseRedDelay(String message);
    int parseYellowDelay(String message);
    int parseGreenDelay(String message);
};

#endif