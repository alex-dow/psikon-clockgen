#include "AnalogButton.h"

AnalogButton::AnalogButton(uint8_t pin, uint16_t buttons)
{
  minimums = new uint16_t[buttons];
  maximums = new uint16_t[buttons];
  this->pin = pin;
};

void AnalogButton::begin()
{
  analogReadResolution(8);
}

void AnalogButton::addButton(uint16_t min, uint16_t max)
{
  minimums[addedButtons] = min;
  maximums[addedButtons] = max;
  addedButtons++;
}

void AnalogButton::setDebounceTime(uint16_t ms)
{
  debounceTime = ms;
}

void AnalogButton::setResolution(uint8_t bits)
{
  analogReadResolution(bits);
}

void AnalogButton::tick()
{
  unsigned long currentTime = millis();

  if ((currentTime - lastReadTime) > debounceTime)
  {
    uint16_t btnValue = analogRead(pin);
    if (btnValue < lastMinimum)
    {
      lastMinimum = btnValue;
      Serial.print("Min: ");
      Serial.print(lastMinimum);
      Serial.print(" Max: ");
      Serial.println(lastMaximum);
    }

    if (btnValue > lastMaximum)
    {
      lastMaximum = btnValue;
      Serial.print("Min: ");
      Serial.print(lastMinimum);
      Serial.print(" Max: ");
      Serial.println(lastMaximum);
    }
    // Serial.print("btn: ");
    // Serial.println(btnValue);

    for (u16_t i = 0; i < addedButtons; i++)
    {
      if (btnValue >= minimums[i] && btnValue <= maximums[i])
      {
        if (i != lastButton || pressed == false)
        {
          pressed = true;
          Serial.print("Button pressed down: ");
          Serial.println(i);
          lastButton = i;
        }
        return;
      }
    }

    // no button is pressed

    if (pressed == true)
    {
      pressed = false;
      Serial.print("Button pressed up: ");
      Serial.println(lastButton);
    }

    lastReadTime = currentTime;
  }
}