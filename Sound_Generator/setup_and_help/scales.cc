#include "scales.h"

namespace scales
{
  int* get_step_pattern(int mode, bool harmonic)
  {
    std::vector<int> untampered_pattern;
    if (!harmonic)
    {
      untampered_pattern.assign({2,2,1,2,2,2,1}); // major
    } else {
      untampered_pattern.assign({2,1,2,2,1,3,1}); // if harmonic is true, mode (0) is minor.
    }


    int* step_pattern = new int [8];
    step_pattern[0] = 0;
    for (int i=0; i<7; i++)
    {
      step_pattern[i+1] = untampered_pattern[(i+mode)%7];
    }
    return step_pattern;
  }

  int* get_pentatonic_pattern(int mode)
  {
    int untampered_pattern [5] = {3,2,2,3,2}; // major

    int* step_pattern = new int [6];
    step_pattern[0] = 0;
    for (int i=0; i<5; i++)
    {
      step_pattern[i+1] = untampered_pattern[(i+mode)%5];
    }
    return step_pattern;
  }

  int* get_blues_pattern(int mode)
  {
    int untampered_pattern [7] = {3,2,1,1,3,1,1}; // major

    int* step_pattern = new int [8];
    step_pattern[0] = 0;
    for (int i=0; i<7; i++)
    {
      step_pattern[i+1] = untampered_pattern[(i+mode)%7];
    }
    return step_pattern;
  }
}
