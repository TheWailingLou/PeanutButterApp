#ifndef KICK_GENERATOR_H
#define KICK_GENERATOR_H

#include <array>
#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>

namespace kick_generator
{
  const int number_of_standards = 10;
  int kick_standards [number_of_standards][16] = {
    {1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
    {1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0},
    {1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,0},
    {1,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0},
    {1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0},
    {1,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0},
    {1,1,0,0,0,0,0,0,1,0,1,0,0,0,0,0},
    {1,0,1,0,0,0,0,0,1,1,0,0,0,0,0,0},
    {1,0,0,0,1,0,0,0,0,0,0,1,0,0,1,0},
    {1,0,0,0,1,0,0,0,0,0,0,1,0,0,1,0}
  };
  int* generate_kick_teenth_array ();
  int* get_random_kick_standard();
}

#endif
