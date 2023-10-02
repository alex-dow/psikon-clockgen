#ifndef CLOCKGEN_UI_PAGES_OSCILLATORS_PAGE_H
#define CLOCKGEN_UI_PAGES_OSCILLATORS_PAGE_H

#include "../page.h"
#include "../theme.h"
#include "setup.h"
#include "dac/waveUtils.h"
#include <LittleFS.h>
#include "./ui/channel.h"

enum SelectedValue
{
  FREQ = 0,
  MULT,
  WAVE,
  TEMPO,
  RATE,
  NONE
};

class OscillatorsPage : public Page
{
public:
  OscillatorsPage(Channel (&channels)[4], TFT_eSPI &tft, UserTheme &theme);
  void setFrequency(uint8_t osc, float freq);
  void setMultiplier(uint8_t osc, float mult);
  void setWave(uint8_t osc, Wave wave);

  void selectOscillator(uint8_t osc);
  void deselectOscillator(uint8_t osc);
  void renderChannel(uint8_t channel);
  void renderChannelFrequency(uint8_t channel);
  void renderChannelMultiplier(uint8_t channel);
  void renderChannelWave(uint8_t channel);
  void renderActive(uint8_t channel);
  void highlightChannel(uint8_t channel);
  void selectChannel(uint8_t channel);
  void deselectChannel(uint8_t channel);
  void render();
  void moveBackward();
  void moveForward();
  void buttonAClicked();
  void encButtonClicked();
  void activate(uint8_t channel);
  void deactivate(uint8_t channel);
  void toggle(uint8_t channel);
  void buttonChn1Clicked();
  void buttonChn2Clicked();
  void buttonChn3Clicked();
  void buttonChn4Clicked();

  int8_t selectedChannel = -1;
  int8_t highlightedChannel = 0;

  SelectedValue selectedValue = SelectedValue::NONE;

  float frequency[4] = {1, 1, 1, 1};
  float multiplier[4] = {1, 1, 1, 1};
  bool active[4] = {false, false, false, false};
  Wave wave[4] = {Wave::SINE, Wave::SINE, Wave::SINE, Wave::SINE};

private:
  Channel (&channels)[4];
  // oscllator -> x,y,w,h
  int boxDimensions[4][4] = {
      {0, 0, 160, 120},
      {160, 0, 160, 120},
      {0, 120, 160, 120},
      {160, 120, 160, 120}};
};

#endif