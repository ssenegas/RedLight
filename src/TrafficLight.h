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

    etl::map<Color, Led, 3> leds = etl::make_map<Color, Led>( etl::pair<Color, Led>{RED, Led(PIN_RED)},
                                                              etl::pair<Color, Led>{YELLOW, Led(PIN_YELLOW)},
                                                              etl::pair<Color, Led>{GREEN, Led(PIN_GREEN)} );

    struct Status {
      char on;
      char off;
    };

    etl::map<Color, Status, 3> status = etl::make_map<Color, Status>( etl::pair<Color, Status> {RED, {'R', 'r'}},
                                                                      etl::pair<Color, Status> {YELLOW, {'Y', 'y'}},
                                                                      etl::pair<Color, Status> {GREEN, {'G', 'g'}} );
};

#endif
