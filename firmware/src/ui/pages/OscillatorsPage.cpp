#include "OscillatorsPage.h"
#include "../page.h"
#include "../theme.h"
#include "./ui/channel.h"
#include <TFT_eSPI.h>

OscillatorsPage::OscillatorsPage(Channel (&chnls)[4], TFT_eSPI &tft, UserTheme &theme) : Page(tft, theme), channels(chnls)
{
}

void OscillatorsPage::render()
{
  tft->fillScreen(theme->bgColor);
  Serial.println("Screen filled");

  renderChannel(0);
  renderChannel(1);
  renderChannel(2);
  renderChannel(3);
  Serial.println("Channels rendered");
  tft->drawFastHLine(0, 120, 320, theme->lightBorderColor);
  tft->drawFastVLine(160, 0, 240, theme->lightBorderColor);
  Serial.println("Screen finished rendering");
}

void OscillatorsPage::setFrequency(uint8_t osc, float freq)
{
  if (frequency[osc] != freq)
  {
    channels[osc].setFrequency(freq);
    frequency[osc] = freq;
    needsRender = true;
  }
}

void OscillatorsPage::setMultiplier(uint8_t osc, float mult)
{
  if (multiplier[osc] != mult)
  {
    multiplier[osc] = mult;
    needsRender = true;
  }
}

void OscillatorsPage::setWave(uint8_t osc, Wave wave)
{
  if (this->wave[osc] != wave)
  {
    this->wave[osc] = wave;
    channels[osc].setWave(wave);
    needsRender = true;
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

  loadFont(MONO_FONT_MED);
  uint16_t fillColor = (selectedValue == SelectedValue::FREQ && selectedChannel == channelNumber) ? theme->selectBgColor : theme->bgColor;
  tft->fillRect(freqX, freqY, freqW, freqH, fillColor);
  tft->setCursor(freqX, freqY);

  tft->setTextColor(theme->fgColor, fillColor);

  tft->setTextSize(1);

  tft->print(" F: ");
  tft->print(frequency[channelNumber]);
  tft->println("hz");
}

void OscillatorsPage::renderChannelMultiplier(uint8_t channelNumber)
{
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
  uint16_t fillColor = (selectedValue == SelectedValue::WAVE && selectedChannel == channelNumber) ? theme->selectBgColor : theme->bgColor;
  tft->fillRect(freqX, freqY, freqW, freqH, fillColor);
  tft->setCursor(freqX, freqY);
  tft->setTextColor(theme->fgColor, fillColor);
  tft->setTextSize(1);

  tft->print(" W: ");
  switch (wave[channelNumber])
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
  default:
    tft->println("? Unknown ?");
  }
}

void OscillatorsPage::deselectChannel(uint8_t channelNumber)
{
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
}

void OscillatorsPage::selectChannel(uint8_t channelNumber)
{
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
}

void OscillatorsPage::highlightChannel(uint8_t channelNumber)
{

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
}

void OscillatorsPage::renderActive(uint8_t channelNumber)
{
  uint16_t channelX = boxDimensions[channelNumber][0];
  uint16_t channelY = boxDimensions[channelNumber][1];

  uint16_t fillColor = (active[channelNumber]) ? theme->successColor : theme->errorColor;

  tft->fillCircle(channelX + 110, channelY + 15, 10, fillColor);
}

void OscillatorsPage::activate(uint8_t channelNumber)
{
  active[channelNumber] = true;
  channels[channelNumber].activate();
  renderActive(channelNumber);
}

void OscillatorsPage::deactivate(uint8_t channelNumber)
{
  active[channelNumber] = false;
  channels[channelNumber].deactivate();
  renderActive(channelNumber);
}

void OscillatorsPage::toggle(uint8_t channelNumber)
{
  if (active[channelNumber] == true)
  {
    active[channelNumber] = false;
    channels[channelNumber].deactivate();
  }
  else
  {
    active[channelNumber] = true;
    channels[channelNumber].activate();
  }
  renderActive(channelNumber);
}

void OscillatorsPage::buttonChn1Clicked()
{
  toggle(0);
}

void OscillatorsPage::buttonChn2Clicked()
{
  toggle(1);
}

void OscillatorsPage::buttonChn3Clicked()
{
  toggle(2);
}

void OscillatorsPage::buttonChn4Clicked()
{
  toggle(3);
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
  tft->setCursor(channelX + 2, channelY + 2);
  tft->setTextColor(TFT_DARKCYAN, theme->bgColor);
  loadFont(AA_FONT_LARGE);
  tft->print("CH: ");
  tft->print(channelNumber + 1);

  tft->setCursor(channelX, channelY + 38);
  // tft->setTextFont(4);

  renderChannelFrequency(channelNumber);
  renderChannelMultiplier(channelNumber);
  renderChannelWave(channelNumber);
}

void OscillatorsPage::moveForward()
{
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
}

void OscillatorsPage::moveBackward()
{
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
}

void OscillatorsPage::encButtonClicked()
{
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
}

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
