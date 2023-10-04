#ifndef CLOCKGEN_UI_THEME_H
#define CLOCKGEN_UI_THEME_H

#include <TFT_eSPI.h>

#define AA_FONT_SMALL "NotoSansBold15"
#define AA_FONT_LARGE "NotoSansBold36"
#define MONO_FONT_SMALL "ShareTechMono-Regular-16"
#define MONO_FONT_MED "ShareTechMono-Regular-24"
#define MONO_FONT_LARGE "ShareTechMono-Regular-32"

#define MONO_FONT_SMALL_WIDTH 8
#define MONO_FONT_SMALL_HEIGHT 8
#define MONO_FONT_MED_WIDTH 11
#define MONO_FONT_MED_HEIGHT 19
#define MONO_FONT_LARGE_WIDTH 15
#define MONO_FONT_LARGE_HEIGHT 15

struct UserTheme
{
  uint16_t bgColor;
  uint16_t fgColor;
  uint16_t successColor;
  uint16_t errorColor;
  uint16_t infoColor;
  uint16_t selectColor;
  uint16_t selectBgColor;
  uint16_t darkBorderColor;
  uint16_t lightBorderColor;
  uint16_t disabledColor;
  void setDefault()
  {
    /*
    bgColor = TFT_WHITE;
    fgColor = TFT_BLACK;
    successColor = TFT_GREEN;
    errorColor = TFT_RED;
    infoColor = TFT_BLUE;
    selectColor = TFT_DARKCYAN;
    selectBgColor = TFT_LIGHTGREY;
    darkBorderColor = TFT_BLACK;
    lightBorderColor = TFT_LIGHTGREY;
    */
    bgColor = TFT_BLACK;
    fgColor = TFT_WHITE;
    darkBorderColor = 0x1012;
    lightBorderColor = 0x4444;
    successColor = TFT_GREEN;
    errorColor = TFT_RED;
    infoColor = TFT_BLUE;
    selectColor = TFT_DARKCYAN;
    selectBgColor = TFT_DARKGREY;
    disabledColor = 0x3986;
  }
};

#endif