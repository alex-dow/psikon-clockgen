#include "channel.h"
#include <MCP48xx.h>
#include "../dac/waveUtils.h"

Channel::Channel(MCP4822 &mcp, uint8_t channelId)
{
  dac = &mcp;
  id = channelId;
  bufferSize = WAVE_9_BITS;
  wave = Wave::SINE;
  generateWave();
}

void Channel::setBufferSize(uint16_t size)
{
  bufferSize = size;
  generateWave();
}

uint16_t Channel::getBufferSize()
{
  return bufferSize;
}

float Channel::getFrequency()
{
  return frequency;
}

Wave Channel::getWave()
{
  return wave;
}

void Channel::setFrequency(float freq)
{
  frequency = freq;
  period = 1e6 / freq;
  /*
  halvePeriod = period / 2;
  volatile float rate = period / bufferSize;
  sampleInterval = rate;
  */
}

void Channel::setWave(Wave w)
{
  wave = w;
  generateWave();
};

void Channel::activate()
{
  if (id == CHANNEL_A)
  {
    dac->turnOnChannelA();
  }
  else if (id == CHANNEL_B)
  {
    dac->turnOnChannelB();
  }
  active = true;
}

void Channel::deactivate()
{
  if (id == CHANNEL_A)
  {
    dac->setVoltageA(0);
    dac->updateDAC();
    dac->shutdownChannelA();
  }
  else if (id == CHANNEL_B)
  {
    dac->setVoltageA(0);
    dac->updateDAC();
    dac->shutdownChannelB();
  }
  active = false;
}

bool Channel::isActive()
{
  return active;
}

void Channel::tick()
{
  now = micros();
  uint32_t t = now % period;
  curSampleIndex = (uint16_t)round(((float)(bufferSize - 1) * (float)t) / (float)period);
  if (curSampleIndex != lastSampleIndex)
  {
    {
      if (id == CHANNEL_A)
      {
        dac->setVoltageA(waveTable[curSampleIndex]);
      }
      else if (id == CHANNEL_B)
      {
        dac->setVoltageB(waveTable[curSampleIndex]);
      }
      lastSampleIndex = curSampleIndex;
    }
  }
}