#ifndef HI_HAT_GENERATOR_H
#define HI_HAT_GENERATOR_H

#include <array>
#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <vector>

namespace hi_hat_generator
{
  const int number_of_standards = 10;
  int hi_hat_standards [number_of_standards][16] = {
      {1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0},
      {1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0},
      {1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,0},
      {1,0,1,1,1,0,1,0,1,0,1,0,1,1,1,0},
      {1,0,1,1,1,0,1,0,1,0,1,1,1,1,1,0},
      {1,0,1,0,1,0,1,0,1,0,1,1,1,0,0,0},
      {1,0,1,0,1,0,1,0,1,1,1,0,1,0,0,0},
      {1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0},
      {1,0,0,0,1,0,0,0,1,0,0,0,1,0,1,0},
      {1,0,0,0,1,0,0,0,1,0,0,1,0,0,1,0}
  };
  int* generate_hi_hat_teenth_array();
  int* get_random_hi_hat_standard();
  int* generate_openings(int* teenth_array);
  std::vector<int> random_from_vector(std::vector<int> possibilities);
}

#endif
