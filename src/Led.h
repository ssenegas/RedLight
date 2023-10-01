#ifndef Led_h
#define Led_h
#include <Arduino.h>

class Led {

  protected: 
    Led(byte pin);
    Led(byte pin, unsigned long blinkRate);

  public:
    void turnOn();
    void turnOff();
    void toogle();
    bool isOn();
    unsigned long getBlinkRate();
    void setBlinkRate(unsigned long blinkRate);

    void update(unsigned long currentTime);

  private:
    byte ledPin;
    unsigned long blinkRateInMillis;
    unsigned long previousMillis;
};

#endif