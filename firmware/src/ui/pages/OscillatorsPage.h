#ifndef CLOCKGEN_UI_PAGES_OSCILLATORS_PAGE_H
#define CLOCKGEN_UI_PAGES_OSCILLATORS_PAGE_H

#define OSCPAGE_CHN_1_BTN_A 5
#define OSCPAGE_CHN_1_BTN_B 6

#define OSCPAGE_CHN_2_BTN_A 7
#define OSCPAGE_CHN_2_BTN_B 0

#define OSCPAGE_CHN_3_BTN_A 3
#define OSCPAGE_CHN_3_BTN_B 4

#define OSCPAGE_CHN_4_BTN_A 1
#define OSCPAGE_CHN_4_BTN_B 2

#define CHN_1 0
#define CHN_2 1
#define CHN_3 2
#define CHN_4 3

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

enum ChannelMode
{
  CH_FREQ,
  CH_TEMPO
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
  void moveMultiplier(uint8_t channel);
  void render();
  void moveBackward();
  void moveForward();
  void moveWave(uint8_t channel);
  void buttonClicked(uint8_t btn);
  void encButtonClicked();
  void activate(uint8_t channel);
  void deactivate(uint8_t channel);
  void toggle(uint8_t channel);

  float chFrequency[4] = {0.01, 0.01, 0.01, 0.01};
  float chFreqMultiplier[4] = {0, 0, 0, 0};
  uint8_t chBeats[4][2] = {{1, 4}, {1, 4}, {1, 4}, {1, 4}};
  uint8_t chTempo[4] = {120, 120, 120, 120};
  bool chActive[4] = {false, false, false, false};
  Wave chWave[4] = {Wave::OFF, Wave::OFF, Wave::OFF, Wave::OFF};
  uint8_t chPwm[4] = {50, 50, 50, 50};

private:
  Channel (&channels)[4];

  uint8_t lastChannel;

  // oscllator -> x,y,w,h
  int boxDimensions[4][4] = {
      {0, 0, 160, 120},
      {160, 0, 160, 120},
      {0, 120, 160, 120},
      {160, 120, 160, 120}};
  int buttonChannelMap[8] = {
      CHN_2, // 0
      CHN_4, // 1
      CHN_4, // 2
      CHN_3, // 3
      CHN_3, // 4
      CHN_1, // 5
      CHN_1, // 6
      CHN_2, // 7
  };
};

#endif