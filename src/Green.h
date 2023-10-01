#ifndef Green_h
#define Green_h
#include <Arduino.h>
#include "Led.h"

class Green : public Led {
  public:
    Green();

  private:
    const byte PIN_GREEN = 4;
};

#endif