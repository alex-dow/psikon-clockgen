#ifndef CLOCKGEN_MULTIPLEX_BUTTON_H
#define CLOCKGEN_MULTIPLEX_BUTTON_H

#include <Arduino.h>

class MultiplexButton
{
public:
  MultiplexButton(uint8_t s0, uint8_t s1, uint8_t s2, uint8_t com);
  void begin();
  void tick();

  void onClicked(void (*cb)(uint8_t));

private:
  void (*clicked)(uint8_t) = NULL;

  uint8_t s0;
  uint8_t s1;
  uint8_t s2;
  uint8_t com;

  uint8_t lastComState;
  uint32_t lastReadTime = 0;
  bool pressed = false;
  uint8_t counter = 0;
  bool reading = true;
  uint8_t lastPressed;
};

#endif