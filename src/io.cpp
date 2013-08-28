/*
 * io.cpp
 * Functions for working with inputs and outputs from sensors to hardware pins
 * on the Raspberry Pi
 * Author: Daniel Lee, 2013
 */

#include "wiringSerial.h"

/*
 * getDistance:
 *   Get the distance read from a MaxBotix sensor using the given
 *   serial_connection
 */

int getDistance(const int &serial_connection) {
  int distance = 0;
  int counter = 100;
  int output;
  while (1) {
      output = serialGetchar(serial_connection);
      // Output is 'R'
      if (output == 82) {}
      // Output is CR
      else if (output == 13) break;
      else {
          // Subtract 48 to get int from ASCII number
          distance += (output - 48) * counter;
          counter /= 10;
      }
  }
  return distance;
}

/*
 * valueToPercent:
 *   Find the percent of a value's distance between given upper and lower
 *   ranges
 */

double valueToPercent(const double &value, const double &min, const double &max)
{
    double percent;
    if (value < min) percent = 0;
    else if (value > max) percent = 1;
    else percent = (value - min) / max;
    return percent;
}

/*
 * percentToValue:
 *   Find the value at the given percent's distance between given upper and
 *   lower ranges
 */

double percentToValue(const double &percent, const double &min,
        const double &max) {
    double range = max - min;
    return (percent * range) + min;
}