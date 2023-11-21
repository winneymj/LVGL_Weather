#ifndef UTILITIES_H_
#define UTILITIES_H_

float mm_to_inches(float value_mm)
{
  return 0.0393701 * value_mm;
}

float hPa_to_inHg(float value_hPa)
{
  return 0.02953 * value_hPa;
}

#endif /* ifndef UTILITIES_H_ */
