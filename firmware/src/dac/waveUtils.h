#ifndef CLOCKGEN_DAC_WAVEUTILS_H
#define CLOCKGEN_DAC_WAVEUTILS_H

#include <Arduino.h>

#define WAVE_8_BITS 255
#define WAVE_9_BITS 511
#define WAVE_12 BITS 4095

enum Wave
{
  SINE = 0,
  RAMP,
  SQUARE,
  DC
};

void generateSawWave(uint16_t *array, uint16_t maxSamples, float vref);
void generateSquareWave(uint16_t *array, uint16_t maxSamples, float width);
void generateSineWave(uint16_t *array, uint16_t maxSamples, float vref);

void createWaveTable(uint16_t *array, uint16_t points, float amplitude, float offset, uint16_t wave);

#endif