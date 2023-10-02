#ifndef CLOCKGEN_SETUP_H
#define CLOCKGEN_SETUP_H
#include <SPI.h>
/* #region MCP4822 SEUTP */
#define MCP_SPI_CS1 13
#define MCP_SPI_CS2 11
#define MCP_SPI_MOSI 15
#define MCP_SPI_CLK 14
#define MCP_SPI_LATCH 10
#define MAX_MCP_FREQ 44000
#define MCP_VREF 3.275
/* #endregion */

/* #region ENCODER SETUP */
#define ENCODER_SW_PIN 16
#define ENCODER_CLK_PIN 18
#define ENCODER_DT_PIN 19

/* #endregion */

/* #region SCREEN SETUP */
/**
 * ILI9341_DRIVER + TFT_eSPI library
 * This replaces the User_Setup.h file in the TFT_eSPI library
 */
// #define TFT_WIDTH 320
// #define TFT_HEIGHT 240
//  #define TFT_MISO 19
//  #define TFT_MOSI 23
//  #define TFT_SCLK 18
// #define TFT_CS 33  // Chip select control pin
// #define TFT_DC 22  // Data Command control pin
// #define TFT_RST 32 // Reset pin
// #define ILI9341_DRIVER 1
//  User defined information reported by "Read_User_Setup" test & diagnostics example
// #define USER_SETUP_INFO "Clockgen_Setup"
//  Comment out the #defines below with // to stop that font being loaded
//  The ESP8366 and ESP32 have plenty of memory so commenting out fonts is not
//  normally necessary. If all fonts are loaded the extra FLASH space required is
//  about 17Kbytes. To save FLASH space only enable the fonts you need!

// #define LOAD_GLCD  // Font 1. Original Adafruit 8 pixel font needs ~1820 bytes in FLASH
// #define LOAD_FONT2 // Font 2. Small 16 pixel high font, needs ~3534 bytes in FLASH, 96 characters
// #define LOAD_FONT4 // Font 4. Medium 26 pixel high font, needs ~5848 bytes in FLASH, 96 characters
// #define LOAD_FONT6 // Font 6. Large 48 pixel font, needs ~2666 bytes in FLASH, only characters 1234567890:-.apm
// #define LOAD_FONT7 // Font 7. 7 segment 48 pixel font, needs ~2438 bytes in FLASH, only characters 1234567890:-.
// #define LOAD_FONT8 // Font 8. Large 75 pixel font needs ~3256 bytes in FLASH, only characters 1234567890:-.
//  #define LOAD_FONT8N // Font 8. Alternative to Font 8 above, slightly narrower, so 3 digits fit a 160 pixel TFT
// #define LOAD_GFXFF // FreeFonts. Include access to the 48 Adafruit_GFX free fonts FF1 to FF48 and custom fonts
//  Define the SPI clock frequency, this affects the graphics rendering speed. Too
//  fast and the TFT driver will not keep up and display corruption appears.
//  With an ILI9341 display 40MHz works OK, 80MHz sometimes fails
//  With a ST7735 display more than 27MHz may not work (spurious pixels and lines)
//  With an ILI9163 display 27 MHz works OK.

// #define SPI_FREQUENCY   1000000
// #define SPI_FREQUENCY   5000000
// #define SPI_FREQUENCY  10000000
// #define SPI_FREQUENCY 20000000
// #define SPI_FREQUENCY  27000000
// #define SPI_FREQUENCY  40000000
// #define SPI_FREQUENCY  55000000 // STM32 SPI1 only (SPI2 maximum is 27MHz)
// #define SPI_FREQUENCY  80000000

// Optional reduced SPI frequency for reading TFT
// #define SPI_READ_FREQUENCY 20000000

// The XPT2046 requires a lower SPI clock rate of 2.5MHz so we define that here:
// #define SPI_TOUCH_FREQUENCY 2500000

// The ESP32 has 2 free SPI ports i.e. VSPI and HSPI, the VSPI is the default.
// If the VSPI port is in use and pins are not accessible (e.g. TTGO T-Beam)
// then uncomment the following line:
// #define USE_HSPI_PORT

// Force TFT_eSPI to assume user setup is loaded, since it is!
// #define USER_SETUP_LOADED
/* #endregion */

/* #region BUTTONS SETUP */
#define BTN_A_PIN 17
#define SW_PIN 12
#define BTN_CHN1_PIN 20
#define BTN_CHN2_PIN 21
#define BTN_CHN3_PIN 22
#define BTN_CHN4_PIN 26
#define BTN_ADC_PIN 27

#define BTN_A_MIN 100
#define BTN_A_MAX 200

#define BTN_B_MIN 100
#define BTN_B_MAX 200

#define BTN_CHN1_MIN 100
#define BTN_CHN1_MAX 100
#define BTN_CHN2_MIN 100
#define BTN_CHN2_MAX 100
#define BTN_CHN3_MAX 100
#define BTN_CHN4_MIN 100
#define BTN_CHN4_MAX 100

#define BTN_S0 20
#define BTN_S1 21
#define BTN_S2 22
#define BTN_COM 26

#define ANALOG_BUTTON_DEBUG

/* #endregion */

#endif