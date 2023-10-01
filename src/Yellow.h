#ifndef Yellow_h
#define Yellow_h
#include <Arduino.h>
#include "Led.h"

class Yellow : public Led {
  public:
    Yellow();

  private:
    const byte PIN_YELLOW = 3;
};

#endif