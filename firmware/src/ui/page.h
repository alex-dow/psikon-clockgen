#ifndef CLOCKGEN_UI_PAGE_H
#define CLOCKGEN_UI_PAGE_H

#include <TFT_eSPI.h>
#include "theme.h"
#include <LittleFS.h>

class Page
{
public:
  Page(TFT_eSPI &tft, UserTheme &theme)
  {
    this->tft = &tft;

    this->lastEncoderValue = 0;
    this->needsRender = false;
    this->theme = &theme;
  };

  void forceRender()
  {
    needsRender = true;
  };

  void loadFont(String fontName)
  {
    if (lastFont.equals(fontName))
    {
      return;
    }
    tft->loadFont(fontName, LittleFS);
    lastFont = fontName;
  };

  virtual void render() {}
  virtual void moveForward() {}
  virtual void moveBackward() {}
  virtual void encButtonClicked() {}
  virtual void buttonAClicked() {}
  virtual void buttonChn1Clicked() {}
  virtual void buttonChn2Clicked() {}
  virtual void buttonChn3Clicked() {}
  virtual void buttonChn4Clicked() {}

  TFT_eSPI *tft;
  bool needsRender;

  int lastEncoderValue;
  UserTheme *theme;

private:
  String lastFont;
};

#endif