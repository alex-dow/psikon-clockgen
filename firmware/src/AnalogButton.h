#ifndef CLOCKGEN_ANALOGBUTTON_H
#define CLOCKGEN_ANALOGBUTTON_H
// chn1 btn 0-15
// chn2 btn 250-260
// chn3 btn 330-340
// chn4 btn 375-385
// btnA btn 400-410
// btnB btn 415-425

#include <Arduino.h>

class AnalogButton
{
public:
  AnalogButton(uint8_t pin, uint16_t nbrOfButtons);
  void setResolution(uint8_t bits);
  void setDebounceTime(uint16_t ms);
  void addButton(uint16_t min, uint16_t max);
  void tick();
  void begin();

private:
  uint8_t pin;
  uint16_t lastMinimum = 1024;
  uint16_t lastMaximum = 0;
  uint16_t *minimums;
  uint16_t *maximums;
  uint16_t debounceTime = 25;
  uint16_t addedButtons = 0;
  unsigned long lastReadTime = 0;
  uint16_t lastButton;
  bool pressed = false;
};
#endif