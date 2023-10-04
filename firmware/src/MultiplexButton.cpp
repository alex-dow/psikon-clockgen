#include "MultiplexButton.h"
#include <Arduino.h>

int bits[8] = {
    0x00,
    0x01,
    0x02,
    0x03,
    0x04,
    0x05,
    0x06,
    0x07};
MultiplexButton::MultiplexButton(uint8_t s0, uint8_t s1, uint8_t s2, uint8_t com)
{
  this->s0 = s0;
  this->s1 = s1;
  this->s2 = s2;
  this->com = com;
}

void MultiplexButton::onClicked(void (*cb)(uint8_t))
{
  clicked = cb;
}

void MultiplexButton::begin()
{
  for (int gpio = s0; gpio < s2 + 1; gpio++)
  {
    pinMode(gpio, OUTPUT);
  }

  pinMode(this->com, INPUT_PULLDOWN);
}

void MultiplexButton::tick()
{

  unsigned long currentTime = millis();

  if (reading)
  {
    uint32_t mask = bits[counter];
    uint8_t a = bitRead(mask, 2);
    uint8_t b = bitRead(mask, 1);
    uint8_t c = bitRead(mask, 0);

    digitalWrite(s0, a);
    digitalWrite(s1, b);
    digitalWrite(s2, c);

    setTime = millis();
    reading = false;
  }
  else if (reading == false && currentTime - setTime > 10)
  {
    int value = digitalRead(this->com);
    if (value == 0)
    {
      if (pressed && counter == lastComState)
      {
        pressed = false;
        if (clicked != NULL)
        {
          clicked(counter);
        }
      }
    }
    else if (value == 1)
    {
      if (pressed == false)
      {
        lastComState = counter;
        pressed = true;
      }
    }

    reading = true;
    counter++;
    if (counter == 8)
    {
      counter = 0;
    }
  }
}