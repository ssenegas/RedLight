#ifndef TrafficLight_h
#define TrafficLight_h
#include <Arduino.h>
#include "Led.h"
#include "etl/map.h"

class TrafficLight {

  public:
    enum Color { RED = 0, YELLOW, GREEN };

    TrafficLight();

    void turnOn(Color c);
    void turnOff(Color c);
    void setBlinkRate(Color c, unsigned long blinkRate);

    void parse(String message);
    void update(unsigned long currentTime);

private:
    void turnOnOff(Color c, bool value);
    void processLED(String command, Color c);
    
private:
    const byte PIN_RED = 2;
    const byte PIN_YELLOW = 3;
    const byte PIN_GREEN = 4;

    Led leds[3] = { Led(PIN_RED), Led(PIN_YELLOW), Led(PIN_GREEN) };
    etl::map<Color, char, 3> statusOn;
    etl::map<Color, char, 3> statusOff;
};

#endif
