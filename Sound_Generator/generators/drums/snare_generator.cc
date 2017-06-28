#include "snare_generator.h"

namespace snare_generator
{
  int* generate_snare_teenth_array ()
  {
    int* teenth_array = new int [16];
    return teenth_array;
  }

  int* get_random_snare_standard()
  {
    int arrnum = rand() % number_of_standards;
    return &snare_standards[arrnum][0];
  }
}
