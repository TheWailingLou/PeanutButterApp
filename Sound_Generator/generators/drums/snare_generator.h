#ifndef SNARE_GENERATOR_H
#define SNARE_GENERATOR_H

#include <array>
#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>

namespace snare_generator
{
  const int number_of_standards = 15;
  int snare_standards [number_of_standards][16] = {
    {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0},
    {0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0},
    {0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0},
    {0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0},
    {0,0,1,0,0,0,1,0,0,0,0,0,1,0,1,0},
    {0,0,1,0,0,0,0,0,0,0,1,0,1,0,0,0},
    {0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0},
    {0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0},
    {0,0,0,1,0,0,1,0,0,0,0,1,1,0,0,0},
    {0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0},
    {0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0}
  };
  int* generate_snare_teenth_array ();
  int* get_random_snare_standard();
}

#endif
