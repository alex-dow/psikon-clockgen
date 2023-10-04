#include "OscillatorsPage.h"
#include "../page.h"
#include "../theme.h"
#include "./ui/channel.h"
#include <TFT_eSPI.h>
#include <math.h>
#include "./cgMath.h"

OscillatorsPage::OscillatorsPage(Channel (&chnls)[4], TFT_eSPI &tft, UserTheme &theme) : Page(tft, theme), channels(chnls)
{
}

void OscillatorsPage::render()
{
  tft->fillScreen(theme->bgColor);

  renderChannel(0);
  renderChannel(1);
  renderChannel(2);
  renderChannel(3);
  tft->drawFastHLine(0, 120, 320, theme->lightBorderColor);
  tft->drawFastVLine(160, 0, 240, theme->lightBorderColor);
}

void OscillatorsPage::setFrequency(uint8_t osc, float freq)
{
  if (chFrequency[osc] != freq)
  {
    channels[osc].setFrequency(freq);
    chFrequency[osc] = freq;
  }
}

void OscillatorsPage::setMultiplier(uint8_t osc, float mult)
{
  if (chFreqMultiplier[osc] != mult)
  {
    chFreqMultiplier[osc] = mult;
  }
  renderChannelFrequency(osc);
}

void OscillatorsPage::setWave(uint8_t osc, Wave wave)
{
  if (this->chWave[osc] != wave)
  {
    this->chWave[osc] = wave;
    channels[osc].setWave(wave);
  }
}

void OscillatorsPage::renderChannelFrequency(uint8_t channelNumber)
{
  int channelX = boxDimensions[channelNumber][0];
  int channelY = boxDimensions[channelNumber][1];
  int channelW = boxDimensions[channelNumber][2];
  int channelH = boxDimensions[channelNumber][3];

  int freqX = channelX + 4;
  int freqY = channelY + 38 + 2;
  int freqH = 18;
  int freqW = channelW - 5;

  tft->fillRect(freqX - 2, freqY - 2, freqW + 2, freqH + 4, theme->bgColor);
  loadFont(MONO_FONT_MED);

  tft->setCursor(freqX, freqY);
  // tft->unloadFont();
  // tft->setTextFont(2);

  tft->setTextSize(1);
  tft->setTextPadding(20);

  if (gtf(chFrequency[channelNumber], 10000))
  {

    tft->setTextColor(theme->fgColor, theme->bgColor);
    tft->print(chFrequency[channelNumber]);
    tft->print("hz");
  }
  else if (gtf(chFrequency[channelNumber], 1000))
  {
    tft->setTextColor(theme->disabledColor, theme->bgColor);
    tft->print("0");
    tft->setTextColor(theme->fgColor, theme->bgColor);
    tft->print(chFrequency[channelNumber]);
    tft->print("hz");
  }
  else if (gtf(chFrequency[channelNumber], 100))
  {
    tft->setTextColor(theme->disabledColor, theme->bgColor);
    tft->print("00");
    tft->setTextColor(theme->fgColor, theme->bgColor);
    tft->print(chFrequency[channelNumber]);
    tft->print("hz");
  }
  else if (gtf(chFrequency[channelNumber], 10))
  {
    tft->setTextColor(theme->disabledColor, theme->bgColor);
    tft->print("000");
    tft->setTextColor(theme->fgColor, theme->bgColor);
    tft->print(chFrequency[channelNumber]);
    tft->print("hz");
  }
  else if (gtf(chFrequency[channelNumber], 0.01))
  {
    tft->setTextColor(theme->disabledColor, theme->bgColor);
    tft->print("0000");
    tft->setTextColor(theme->fgColor, theme->bgColor);
    tft->print(chFrequency[channelNumber]);
    tft->print("hz");
  }
  else
  {
    tft->setTextColor(theme->disabledColor, theme->bgColor);
    tft->print("00000.00");
    tft->setTextColor(theme->fgColor, theme->bgColor);
    tft->print("hz");
  }

  if (chFreqMultiplier[channelNumber] > 0)
  {
    if (cmpf(chFreqMultiplier[channelNumber], 10000))
    {
      tft->drawRect(freqX, freqY - 1, MONO_FONT_MED_WIDTH + 2, MONO_FONT_MED_HEIGHT, theme->selectColor);
    }
    else if (cmpf(chFreqMultiplier[channelNumber], 1000))
    {
      tft->drawRect(freqX + (MONO_FONT_MED_WIDTH * 1) + 2, freqY - 1, MONO_FONT_MED_WIDTH + 2, MONO_FONT_MED_HEIGHT, theme->selectColor);
    }
    else if (cmpf(chFreqMultiplier[channelNumber], 100))
    {
      tft->drawRect(freqX + (MONO_FONT_MED_WIDTH * 2) + 4, freqY - 1, MONO_FONT_MED_WIDTH + 2, MONO_FONT_MED_HEIGHT, theme->selectColor);
    }
    else if (cmpf(chFreqMultiplier[channelNumber], 10))
    {
      tft->drawRect(freqX + (MONO_FONT_MED_WIDTH * 3) + 6, freqY - 1, MONO_FONT_MED_WIDTH + 2, MONO_FONT_MED_HEIGHT, theme->selectColor);
    }
    else if (cmpf(chFreqMultiplier[channelNumber], 1))
    {
      tft->drawRect(freqX + (MONO_FONT_MED_WIDTH * 4) + 8, freqY - 1, MONO_FONT_MED_WIDTH + 2, MONO_FONT_MED_HEIGHT, theme->selectColor);
    }
    else if (cmpf(chFreqMultiplier[channelNumber], 0.1))
    {
      tft->drawRect(freqX + (MONO_FONT_MED_WIDTH * 6) + 12, freqY - 1, MONO_FONT_MED_WIDTH + 2, MONO_FONT_MED_HEIGHT, theme->selectColor);
    }
    else if (cmpf(chFreqMultiplier[channelNumber], 0.01))
    {
      tft->drawRect((freqX) + (MONO_FONT_MED_WIDTH * 7) + 14, freqY - 1, MONO_FONT_MED_WIDTH + 2, MONO_FONT_MED_HEIGHT, theme->selectColor);
    }
  }
}

void OscillatorsPage::renderChannelMultiplier(uint8_t channelNumber)
{
  /*
  int channelX = boxDimensions[channelNumber][0];
  int channelY = boxDimensions[channelNumber][1];
  int channelW = boxDimensions[channelNumber][2];
  int channelH = boxDimensions[channelNumber][3];

  int freqX = channelX + 4;
  int freqY = channelY + 38 + 18 + 4;
  int freqH = 18;
  int freqW = channelW - 5;

  loadFont(MONO_FONT_MED);
  uint16_t fillColor = (selectedValue == SelectedValue::MULT && selectedChannel == channelNumber) ? theme->selectBgColor : theme->bgColor;
  tft->fillRect(freqX, freqY, freqW, freqH, fillColor);
  tft->setCursor(freqX, freqY);
  tft->setTextColor(theme->fgColor, fillColor);
  tft->print(" M: x");
  tft->print(multiplier[channelNumber]);
  */
}

void OscillatorsPage::renderChannelWave(uint8_t channelNumber)
{
  int channelX = boxDimensions[channelNumber][0];
  int channelY = boxDimensions[channelNumber][1];
  int channelW = boxDimensions[channelNumber][2];
  int channelH = boxDimensions[channelNumber][3];

  int freqX = channelX + 4;
  int freqY = channelY + 38 + 18 + 18 + 6;
  int freqH = 18;
  int freqW = channelW - 5;

  loadFont(MONO_FONT_MED);
  tft->fillRect(freqX, freqY, freqW, freqH, theme->bgColor);
  tft->setCursor(freqX, freqY);
  tft->setTextColor(theme->fgColor, theme->bgColor);
  tft->setTextSize(1);

  switch (chWave[channelNumber])
  {
  case Wave::SINE:
    tft->println("Sine");
    break;
  case Wave::RAMP:
    tft->println("Ramp");
    break;
  case Wave::SQUARE:
    tft->println("Square");
    break;
  case Wave::OFF:
    tft->println("Off");
    break;
  default:
    tft->println("? Unknown ?");
  }
}

void OscillatorsPage::deselectChannel(uint8_t channelNumber)
{
  /*
  if (channelNumber > 3 || channelNumber < 0)
  {
    return;
  }
  int channelX;
  int channelY;
  int channelW;
  int channelH;

  channelX = boxDimensions[selectedChannel][0];
  channelY = boxDimensions[selectedChannel][1];
  channelW = boxDimensions[selectedChannel][2];
  channelH = boxDimensions[selectedChannel][3];
  tft->drawRect(channelX + 2, channelY + 2, channelW - 2, channelH - 2, theme->bgColor);

  selectedChannel = -1;
  renderChannel(channelNumber);
  */
}

void OscillatorsPage::selectChannel(uint8_t channelNumber)
{
  /*
  if (selectedChannel != channelNumber)
  {
    if (selectedChannel != -1)
    {
      deselectChannel(selectedChannel);
    }
    int channelX;
    int channelY;
    int channelW;
    int channelH;

    channelX = boxDimensions[channelNumber][0];
    channelY = boxDimensions[channelNumber][1];
    channelW = boxDimensions[channelNumber][2];
    channelH = boxDimensions[channelNumber][3];
    tft->drawRect(channelX + 2, channelY + 2, channelW - 2, channelH - 2, theme->selectBgColor);
    selectedChannel = channelNumber;
  }
  */
}

void OscillatorsPage::highlightChannel(uint8_t channelNumber)
{

  /*
    if (highlightedChannel != channelNumber)
    {

      int channelX;
      int channelY;
      int channelW;
      int channelH;

      channelX = boxDimensions[highlightedChannel][0];
      channelY = boxDimensions[highlightedChannel][1];
      channelW = boxDimensions[highlightedChannel][2];
      channelH = boxDimensions[highlightedChannel][3];
      tft->drawRect(channelX + 2, channelY + 2, channelW - 2, channelH - 2, theme->bgColor);

      channelX = boxDimensions[channelNumber][0];
      channelY = boxDimensions[channelNumber][1];
      channelW = boxDimensions[channelNumber][2];
      channelH = boxDimensions[channelNumber][3];
      tft->drawRect(channelX + 2, channelY + 2, channelW - 2, channelH - 2, theme->infoColor);
      highlightedChannel = channelNumber;
    }
    */
}

void OscillatorsPage::renderActive(uint8_t channelNumber)
{
  uint16_t channelX = boxDimensions[channelNumber][0];
  uint16_t channelY = boxDimensions[channelNumber][1];

  uint16_t fillColor = (chActive[channelNumber]) ? theme->successColor : theme->errorColor;

  tft->fillCircle(channelX + 110, channelY + 15, 10, fillColor);
}

void OscillatorsPage::activate(uint8_t channelNumber)
{
  chActive[channelNumber] = true;
  channels[channelNumber].activate();
  renderActive(channelNumber);
}

void OscillatorsPage::deactivate(uint8_t channelNumber)
{
  chActive[channelNumber] = false;
  channels[channelNumber].deactivate();
  renderActive(channelNumber);
}

void OscillatorsPage::toggle(uint8_t channelNumber)
{
  if (chActive[channelNumber] == true)
  {
    deactivate(channelNumber);
  }
  else
  {
    activate(channelNumber);
  }
  renderActive(channelNumber);
}

void OscillatorsPage::moveMultiplier(uint8_t channel)
{
  if (channel != lastChannel)
  {
    setMultiplier(lastChannel, 0);
    lastChannel = channel;
  }

  if (cmpf(chFreqMultiplier[channel], 10000.0))
  {
    setMultiplier(channel, 0.01);
  }
  else if (cmpf(chFreqMultiplier[channel], 0))
  {
    setMultiplier(channel, 10000);
  }
  else
  {
    setMultiplier(channel, chFreqMultiplier[channel] * 10);
  }
}

void OscillatorsPage::moveWave(uint8_t channel)
{
  if (chWave[channel] == Wave::SINE)
  {
    setWave(channel, Wave::RAMP);
    renderChannelWave(channel);
  }
  else if (chWave[channel] == Wave::RAMP)
  {
    setWave(channel, Wave::SQUARE);
    renderChannelWave(channel);
  }
  else if (chWave[channel] == Wave::SQUARE)
  {
    setWave(channel, Wave::OFF);
    renderChannelWave(channel);
  }
  else if (chWave[channel] == Wave::OFF)
  {
    setWave(channel, Wave::SINE);
    renderChannelWave(channel);
  }
}

void OscillatorsPage::buttonClicked(uint8_t btn)
{
  switch (btn)
  {
  case OSCPAGE_CHN_1_BTN_B:
  case OSCPAGE_CHN_2_BTN_B:
  case OSCPAGE_CHN_3_BTN_B:
  case OSCPAGE_CHN_4_BTN_B:
    moveMultiplier(buttonChannelMap[btn]);
    break;
  case OSCPAGE_CHN_1_BTN_A:
  case OSCPAGE_CHN_2_BTN_A:
  case OSCPAGE_CHN_3_BTN_A:
  case OSCPAGE_CHN_4_BTN_A:
    moveWave(buttonChannelMap[btn]);
    break;
  }
}

void OscillatorsPage::renderChannel(uint8_t channelNumber)
{
  if (channelNumber > 3)
  {
    Serial.print("[w] renderChannel() - Channel number bigger than 3: ");
    Serial.println(channelNumber);
    return;
  }
  else if (channelNumber < 0)
  {
    Serial.print("[w] renderChannel() - Channel number less than 0: ");
    Serial.println(channelNumber);
    return;
  }
  int channelX = boxDimensions[channelNumber][0];
  int channelY = boxDimensions[channelNumber][1];
  int channelW = boxDimensions[channelNumber][2];
  int channelH = boxDimensions[channelNumber][3];

  tft->fillRect(
      channelX,
      channelY,
      channelW,
      channelH,
      theme->bgColor);
  tft->setCursor(channelX + 2, channelY + 7);
  tft->setTextColor(TFT_CYAN, theme->bgColor);
  loadFont(MONO_FONT_LARGE);
  tft->print("CH: ");
  tft->print(channelNumber + 1);

  renderChannelFrequency(channelNumber);
  renderChannelWave(channelNumber);

  /*
    loadFont(MONO_FONT_MED);
    tft->setCursor(channelX + 2, channelY + 38);
    tft->setTextColor(0x3986, theme->bgColor);
    tft->print("0000");
    tft->setTextColor(theme->fgColor, theme->bgColor);
    tft->print("0.19hz");
    tft->drawRect(channelX + 1, channelY + 36, 14, 22, TFT_ORANGE);

    loadFont(MONO_FONT_MED);
    tft->setCursor(channelX + 2, channelY + 65);
    tft->setTextColor(theme->fgColor, theme->bgColor);
    tft->print("Sine");
  */

  // tft->setTextFont(4);

  // renderChannelFrequency(channelNumber);
  // renderChannelMultiplier(channelNumber);
  // renderChannelWave(channelNumber);
}

void OscillatorsPage::moveForward()
{
  setFrequency(lastChannel, chFrequency[lastChannel] + chFreqMultiplier[lastChannel]);
  renderChannelFrequency(lastChannel);
  /*
  if (selectedChannel == -1)
  {
    int nextChannel = highlightedChannel + 1;
    if (nextChannel == 4)
    {
      nextChannel = 0;
    }
    else if (nextChannel < 0)
    {
      nextChannel = 0;
    }

    Serial.print("Highlight channel #");
    Serial.println(nextChannel + 1);

    highlightChannel(nextChannel);
  }
  else
  {
    if (selectedValue == SelectedValue::FREQ)
    {
      frequency[selectedChannel] = frequency[selectedChannel] + multiplier[selectedChannel];
      channels[selectedChannel].setFrequency(frequency[selectedChannel]);
      renderChannelFrequency(selectedChannel);
    }
    else if (selectedValue == SelectedValue::MULT)
    {
      multiplier[selectedChannel] = multiplier[selectedChannel] * 10;
      if (multiplier[selectedChannel] > 10000)
      {
        multiplier[selectedChannel] = 10000;
      }

      renderChannelMultiplier(selectedChannel);
    }
    else if (selectedValue == SelectedValue::WAVE)
    {
      if (wave[selectedChannel] == Wave::SINE)
      {
        wave[selectedChannel] = Wave::RAMP;
      }
      else if (wave[selectedChannel] == Wave::RAMP)
      {
        wave[selectedChannel] = Wave::SQUARE;
      }
      else if (wave[selectedChannel] == Wave::SQUARE)
      {
        wave[selectedChannel] = Wave::SINE;
      }
      channels[selectedChannel].setWave(wave[selectedChannel]);
      renderChannelWave(selectedChannel);
    }
  }
  */
}

void OscillatorsPage::moveBackward()
{
  float newFreq = chFrequency[lastChannel] - chFreqMultiplier[lastChannel];
  if (ltf(newFreq, 0.01))
  {
    newFreq = 0.01;
  }
  setFrequency(lastChannel, newFreq);
  renderChannelFrequency(lastChannel);
  /*
  if (selectedChannel == -1)
  {
    int nextChannel = highlightedChannel;
    if (nextChannel == 0)
    {
      nextChannel = 3;
    }
    else
    {
      nextChannel--;
    }

    Serial.print("Highlight channel #");
    Serial.println(nextChannel + 1);

    highlightChannel(nextChannel);
  }
  else
  {
    if (selectedValue == SelectedValue::FREQ)
    {
      frequency[selectedChannel] = frequency[selectedChannel] - multiplier[selectedChannel];
      if (frequency[selectedChannel] < 0)
      {
        frequency[selectedChannel] = 0;
      }
      channels[selectedChannel].setFrequency(frequency[selectedChannel]);
      renderChannelFrequency(selectedChannel);
    }
    else if (selectedValue == SelectedValue::MULT)
    {
      multiplier[selectedChannel] = multiplier[selectedChannel] / 10;
      if (multiplier[selectedChannel] < 0.01)
      {
        multiplier[selectedChannel] = 0.01;
      }
      renderChannelMultiplier(selectedChannel);
    }
    else if (selectedValue == SelectedValue::WAVE)
    {
      if (wave[selectedChannel] == Wave::SQUARE)
      {
        wave[selectedChannel] = Wave::RAMP;
      }
      else if (wave[selectedChannel] == Wave::RAMP)
      {
        wave[selectedChannel] = Wave::SINE;
      }
      else if (wave[selectedChannel] == Wave::SINE)
      {
        wave[selectedChannel] = Wave::SQUARE;
      }
      channels[selectedChannel].setWave(wave[selectedChannel]);
      renderChannelWave(selectedChannel);
    }

  }
  */
}

void OscillatorsPage::encButtonClicked()
{
  /*
  if (selectedChannel != -1)
  {
    Serial.print("Deselecting channel #");
    Serial.println(selectedChannel + 1);
    deselectChannel(selectedChannel);
  }
  else
  {
    Serial.print("Selecting channel #");
    Serial.println(highlightedChannel + 1);
    selectChannel(highlightedChannel);
  }
  selectedValue = SelectedValue::NONE;
  */
}

/*
void OscillatorsPage::buttonAClicked()
{
  if (selectedValue == SelectedValue::FREQ)
  {
    selectedValue = SelectedValue::MULT;
    renderChannelFrequency(selectedChannel);
    renderChannelMultiplier(selectedChannel);
  }
  else if (selectedValue == SelectedValue::MULT)
  {
    selectedValue = SelectedValue::WAVE;
    renderChannelMultiplier(selectedChannel);
    renderChannelWave(selectedChannel);
  }
  else if (selectedValue == SelectedValue::WAVE)
  {
    selectedValue = SelectedValue::FREQ;
    renderChannelWave(selectedChannel);
    renderChannelFrequency(selectedChannel);
  }
  else
  {
    selectedValue = SelectedValue::FREQ;
    renderChannel(selectedChannel);
  }
}
*/