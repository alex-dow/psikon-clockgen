#ifndef CLOCKGEN_CHANNEL_H
#define CLOCKGEN_CHANNEL_H

#include "../dac/waveUtils.h"
#include "../dac/MCP48xx.h"
#include "../setup.h"

#define CHANNEL_A 1
#define CHANNEL_B 2

class Channel
{
public:
  Channel(MCP4822 &dac, uint8_t id);
  void setFrequency(float freq);
  float getFrequency();
  void setBufferSize(uint16_t size);
  uint16_t getBufferSize();
  void setWave(Wave);
  Wave getWave();
  void tick();
  void activate();
  void deactivate();
  bool isActive();

private:
  uint8_t id;
  MCP4822 *dac;
  uint16_t bufferSize = WAVE_9_BITS;
  uint32_t period;
  uint16_t curSampleIndex;
  uint16_t lastSampleIndex;
  bool active;
  Wave wave;
  float frequency;
  uint16_t *waveTable;
  unsigned long now;

  void generateWave()
  {
    waveTable = (uint16_t *)malloc(bufferSize * sizeof(uint16_t));
    if (wave == Wave::SINE)
    {
      generateSineWave(waveTable, bufferSize, MCP_VREF);
    }
    else if (wave == Wave::RAMP)
    {
      generateSawWave(waveTable, bufferSize, MCP_VREF);
    }
    else if (wave == Wave::SQUARE)
    {
      generateSquareWave(waveTable, bufferSize, 0.5);
    }
  }
};

#endif