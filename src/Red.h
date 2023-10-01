#ifndef Red_h
#define Red_h
#include <Arduino.h>
#include "Led.h"

class Red : public Led {
  public:
    Red();

  private:
    const byte PIN_RED = 2;
};

#endif