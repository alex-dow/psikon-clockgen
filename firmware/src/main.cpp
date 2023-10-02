#include "setup.h"
#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Button2.h>
#include <hardware/pio.h>
#include <quadrature.pio.h>
#include <TFT_eSPI.h>
#include <LittleFS.h>
#include <FS.h>
#include "./dac/MCP48xx.h"
#include "./dac/waveUtils.h"
#include "./ui/channel.h"
#include "AnalogButton.h"
#include "MultiplexButton.h"
#define FlashFS LittleFS

#include "ui/theme.h"
#include "ui/pages/OscillatorsPage.h"

UserTheme theme;
TFT_eSPI tft = TFT_eSPI();

MCP4822 MCP1(MCP_SPI_CS1);
MCP4822 MCP2(MCP_SPI_CS2);
Channel chn1(MCP1, CHANNEL_A);
Channel chn2(MCP1, CHANNEL_B);
Channel chn3(MCP2, CHANNEL_A);
Channel chn4(MCP2, CHANNEL_B);
// AnalogButton btn(BTN_ADC_PIN, 6);
MultiplexButton btn2(BTN_S0, BTN_S1, BTN_S2, BTN_COM);

Channel channels[4] = {
    chn1, chn2, chn3, chn4};

OscillatorsPage oscPage(channels, tft, theme);

void handle_button(uint8_t btn);

void setup_tft()
{
  Serial.print("Setup TFT ... ");
  theme.setDefault();

  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.fillScreen(TFT_BLUE);
  tft.fillScreen(TFT_RED);
  tft.fillScreen(TFT_GREEN);
  tft.fillScreen(theme.bgColor);
  tft.setCursor(2, 25);
  tft.setTextColor(theme.fgColor);
  tft.setTextFont(4);

  tft.setTextSize(1);
  tft.println("CLOCKGEN v0.0.1");
  Serial.println("OK");
  tft.setTextFont(2);
  tft.println("Screen Initialized");
}

PIO encoderPIO = pio0;
uint smA;
uint smB;
void setup_encoder()
{
  tft.setTextColor(theme.fgColor);
  tft.print("Init Encoder ... ");

  Serial.print("Setup encoder ... ");

  uint offsetA = pio_add_program(encoderPIO, &quadratureA_program);
  smA = pio_claim_unused_sm(encoderPIO, true);

  uint offsetB = pio_add_program(encoderPIO, &quadratureB_program);
  smB = pio_claim_unused_sm(encoderPIO, true);

  quadratureA_program_init(encoderPIO, smA, offsetA, ENCODER_CLK_PIN, ENCODER_DT_PIN);
  quadratureB_program_init(encoderPIO, smB, offsetB, ENCODER_CLK_PIN, ENCODER_DT_PIN);

  tft.setTextColor(theme.successColor);
  Serial.println("OK");
  tft.println("OK");
  delay(1000);
}

void setup_fs()
{
  Serial.print("Setup LittleFS ... ");
  if (!LittleFS.begin())
  {
    Serial.println("FAILED!");
    while (1)
    {
    }
  }
  Serial.println("OK");

  if (LittleFS.exists("/NotoSansBold15.vlw") == false)
  {
    Serial.println("MISSING BOLD15");
    while (1)
    {
    }
  }
  if (LittleFS.exists("/NotoSansBold36.vlw") == false)
  {
    Serial.println("MISSING BOLD36");
    while (1)
    {
    }
  }
  Serial.println("OK");
}

void button_clicked(uint8_t btn)
{
  Serial.print("Button clicked: ");
  Serial.println(btn);
}

void setup_buttons()
{
  btn2.onClicked(button_clicked);
  btn2.begin();

  pinMode(SW_PIN, INPUT);
}

void setup_dac()
{
  Serial.print("Setup DAC ... ");
  SPI1.setTX(MCP_SPI_MOSI);
  SPI1.setSCK(MCP_SPI_CLK);
  SPI1.begin();

  MCP1.init(&SPI1);
  MCP1.setGainA(MCP4822::Low);
  MCP1.setGainB(MCP4822::Low);

  MCP2.init(&SPI1);
  MCP2.setGainA(MCP4822::Low);
  MCP2.setGainB(MCP4822::Low);

  for (int i = 0; i < 4; i++)
  {
    channels[i].setBufferSize(511);
    channels[i].setWave(Wave::SINE);
    channels[i].setFrequency(1);
    channels[i].deactivate();
  }

  Serial.println("OK");

  MCP1.updateDAC();
  MCP2.updateDAC();
}

void setup()
{
  Serial.begin(115200);
  while (!Serial)
    ;
  delay(1000);
  Serial.println("\n/*** SIGNAL GENERATOR ***/");
  setup_fs();
  setup_tft();
  setup_encoder();
  setup_buttons();
  setup_dac();

  oscPage.render();

  Serial.println("Ready!\n");
}

int lastSwitchValue;
uint16_t lastButtonValue = 0;

void tickButtons()
{

  int sw = digitalRead(SW_PIN);
  if (sw != lastSwitchValue)
  {
    Serial.print("Switch: ");
    Serial.println(sw);
    lastSwitchValue = sw;
  }

  btn2.tick();
}

int32_t lastEncoderValue = 0;

void tickEncoder()
{
  pio_sm_exec_wait_blocking(encoderPIO, smA, pio_encode_in(pio_x, 32));
  pio_sm_exec_wait_blocking(encoderPIO, smB, pio_encode_in(pio_x, 32));

  int32_t countA = pio_sm_get_blocking(encoderPIO, smA);
  int32_t countB = pio_sm_get_blocking(encoderPIO, smB);
  int32_t encoderValue = countA + countB;
  int32_t delta = abs(lastEncoderValue - encoderValue);

  if (encoderValue != lastEncoderValue)
  {
    if (delta >= 4)
    {
      // pio_sm_exec(encoderPIO, smA, pio_encode_set(pio_x, 0));
      // pio_sm_exec(encoderPIO, smB, pio_encode_set(pio_x, 0));

      if (encoderValue > lastEncoderValue)
      {
        oscPage.moveForward();
      }
      else if (encoderValue < lastEncoderValue)
      {
        oscPage.moveBackward();
      }

      lastEncoderValue = encoderValue;
    }
  }
}

void handle_button_enc(Button2 &btn)
{
  oscPage.encButtonClicked();
}

void handle_button_a(Button2 &btn)
{
  oscPage.buttonAClicked();
}

void handle_button_chn1(Button2 &btn)
{
  oscPage.buttonChn1Clicked();
  Serial.println("Channel 1 button pressed");
}

void handle_button_chn2(Button2 &btn)
{
  oscPage.buttonChn2Clicked();
  Serial.println("Channel 2 button pressed.");
}

void handle_button_chn3(Button2 &btn)
{
  oscPage.buttonChn3Clicked();
  Serial.println("Channel 3 button pressed");
}

void handle_button_chn4(Button2 &btn)
{
  oscPage.buttonChn4Clicked();
  Serial.println("Channel 4 button pressed");
}

void tickChannels()
{
  bool updateMcp1 = false;
  bool updateMcp2 = false;
  volatile uint8_t i;
  for (i = 0; i < 4; i++)
  {
    if (channels[i].isActive())
    {
      channels[i].tick();
      if (i == 0 || i == 1)
      {
        updateMcp1 = true;
      }
      else if (i == 2 || i == 3)
      {
        updateMcp2 = true;
      }
    }
  }

  if (updateMcp1)
  {
    // Serial.println("Update MCP1");
    MCP1.updateDAC();
  }

  if (updateMcp2)
  {
    // Serial.println("Update MCP2");
    MCP2.updateDAC();
  }
}

void loop()
{
  tickButtons();
  tickEncoder();

  tickChannels();
}