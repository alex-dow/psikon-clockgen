#include "waveUtils.h"
#include "setup.h"

void generateSawWave(uint16_t *array, uint16_t maxSamples, float vref)
{
  volatile uint16_t i;
  int32_t sample = 0;
  float tempSample;
  float sampleLevel = (float)1 / maxSamples;
  float vConst = (4096 / vref) * vref / 2;

  for (i = 0; i < maxSamples; i++)
  {
    tempSample = (i * sampleLevel);
    tempSample = (tempSample * vConst) + (float)(4096 / vref) * (vref / 2) / 2;
    sample = (int32_t)tempSample;
    // sample = ((i * sampleLevel) * vConst) + (float)(4096 / vref) * (vref / 2);
    //(temp_float * v_const) + (float)(4096 / MCP_VREF) * offset;

    // sample = ((maxSamples - i) / maxSamples) * 4095;
    // sampleLevel = i
    if (sample > 4095)
    {
      sample = 4095;
    }
    else if (sample < 0)
    {
      sample = 0;
    }
    array[i] = sample;
  }
}

void generateSquareWave(uint16_t *array, uint16_t maxSamples, float width)
{

  volatile uint16_t i;
  int32_t sample = 0;

  for (i = 0; i < maxSamples; i++)
  {
    if (i < (maxSamples * width))
    {
      array[i] = 4095;
    }
    else
    {
      array[i] = 0;
    }
  }
}

void generateSineWave(uint16_t *array, uint16_t maxSamples, float vref)
{
  volatile uint16_t i;
  float tempSample;
  int32_t sample = 0;

  float vConst = (4096 / vref) * (vref / 2) / 1;
  float offset = vref / 2;
  float sinSize = (float)(2 * PI) / (maxSamples);

  for (i = 0; i < maxSamples; i++)
  {
    tempSample = (sin(sinSize * i * 1));
    tempSample = (tempSample * vConst) + (float)(4096 / vref) * offset;
    sample = (int32_t)tempSample;

    if (sample > 4095)
    {
      array[i] = 4095;
    }
    else if (sample < 0)
    {
      array[i] = 0;
    }
    else
    {
      array[i] = sample;
    }
  }
}

void createWaveTable(uint16_t *array, uint16_t points, float amplitude, float offset, uint16_t wave)
{
  volatile uint16_t i;
  float temp_float;
  int32_t temp = 0;

  float v_const = 0;
  float const_sin_rad = 0;
  float level_variation = 0;

  if (wave == Wave::SINE)
  {
    v_const = (4096 / MCP_VREF) * amplitude / 2;
    const_sin_rad = (float)(2 * PI) / (points);
  }
  else if (wave == Wave::RAMP)
  {
    v_const = (4096 / MCP_VREF) * amplitude / 1;
    level_variation = (float)1 / points;
  }
  else if (wave == Wave::SQUARE)
  {
    v_const = (4096 / MCP_VREF) * amplitude / 1;
  }
  else
    ;

  /*
   * calcula o valor de cada amostra
   * - cada forma de onda exite um cálculo diferente
   * - todos os cálculos retornam o valor pela variável "temp"
   */
  for (i = 0; i < points; i++)
  {
    if (wave == Wave::SINE)
    {
      temp_float = (sin(const_sin_rad * i * 1));
      temp_float = (temp_float * v_const) + (float)(4096 / MCP_VREF) * offset;
      temp = (int32_t)temp_float;
    }
    else if (wave == Wave::RAMP)
    {
      temp_float = i * level_variation;
      temp_float = (temp_float * v_const) + (float)(4096 / MCP_VREF) * offset;
      temp = (int32_t)temp_float;
    }
    else if (wave == Wave::SQUARE)
    {
      if (i < points / 2)
      {
        temp_float = v_const + (float)(4096 / MCP_VREF) * offset;
        temp = (int32_t)temp_float;
      }
      else
      {
        temp_float = (float)(4096 / MCP_VREF) * offset;
        temp = (int32_t)temp_float;
      }
    }

    else
      ;

    if (temp > 4095)
    {
      array[i] = 4095;
    }
    else if (temp < 0)
    {
      array[i] = 0;
    }
    else
    {
      array[i] = temp;
    }

    // imprime o valor calculado
    // Serial.println(array[i]);
  }
}
