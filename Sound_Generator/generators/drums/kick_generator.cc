#include "kick_generator.h"

namespace kick_generator
{
  int* generate_kick_teenth_array ()
  {
    int* teenth_array = new int [16];
    return teenth_array;
  }

  int* get_random_kick_standard()
  {
    // srand(time(NULL));
    int arrnum = rand() % number_of_standards;
    return &kick_standards[arrnum][0];
  }
}
