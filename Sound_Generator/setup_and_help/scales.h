#ifndef SCALES_H
#define SCALES_H

#include <array>
#include <iostream>
#include <vector>

namespace scales
{
  int* get_step_pattern(int mode, bool harmonic=false);
  int* get_pentatonic_pattern(int mode);
  int* get_blues_pattern(int mode);
}

#endif
