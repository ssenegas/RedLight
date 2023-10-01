#ifndef TrafficLight_h
#define TrafficLight_h
#include <Arduino.h>
#include "Red.h"
#include "Yellow.h"
#include "Green.h"
#include "etl/map.h"

class TrafficLight {

  public:
    enum Color { RED = 0, YELLOW, GREEN };

    TrafficLight();
    ~TrafficLight();

    void turnOn(Color c);
    void turnOff(Color c);
    void setBlinkRate(Color c, unsigned long blinkRate);

    void parse(String message);
    void update(unsigned long currentTime);

private:
    void processLED(String command, Color c);

    etl::map<Color, Led*, 3> leds =
      etl::make_map<Color, Led*>( etl::pair<Color, Led*>{RED, new Red()},
                                  etl::pair<Color, Led*>{YELLOW, new Yellow()},
                                  etl::pair<Color, Led*>{GREEN, new Green()} );

    struct Status {
      char on;
      char off;
    };

    etl::map<Color, Status, 3> status =
      etl::make_map<Color, Status>( etl::pair<Color, Status> {RED, {'R', 'r'}},
                                    etl::pair<Color, Status> {YELLOW, {'Y', 'y'}},
                                    etl::pair<Color, Status> {GREEN, {'G', 'g'}} );
};

#endif
