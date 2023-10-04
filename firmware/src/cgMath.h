#ifndef CLOCKGEN_CG_MATH_H
#define CLOCKGEN_CG_MATH_H

#include <math.h>

bool cmpf(float a, float b, float epsilon = 0.001)
{
  if (fabs(a - b) <= epsilon * fabs(a))
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool gtf(float a, float b, float epsilon = 0.001)
{
  return cmpf(a, b) || a > b;
}

bool ltf(float a, float b, float epsilon = 0.001)
{
  return cmpf(a, b) || a < b;
}

#endif