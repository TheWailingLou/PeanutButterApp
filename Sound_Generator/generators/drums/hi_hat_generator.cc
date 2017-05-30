#include "hi_hat_generator.h"

namespace hi_hat_generator
{
  int* generate_hi_hat_teenth_array ()
  {
    int* teenth_array = new int [16];
    for (int i=0; i<16; i++)
    {
      int num = 0;
      int random = rand() % 100;
      if (random > 85)
      {
        num = 1;
      }
      if (i%2 == 0)
      {
        if (random > 43)
        {
          num = 1;
        }
      }
      if (i%4 == 0)
      {
        if (random > 30)
        {
          num = 1;
        }
      }
      if (i%8 == 0)
      {
        if (random > 10)
        {
          num = 1;
        }
      }
      if (i==0)
      {
        if (random > 5)
        {
          num = 1;
        }
      }
      teenth_array[i] = num;
    }
    int random1 = rand() % 100;
    int random2 = rand() % 100;
    if (random1 > 60)
    {
      std::cout << "doubled up end" << std::endl;
      for (int i=4; i<8; i++)
      {
        teenth_array[i+8] = teenth_array[i];
      }
    }
    if (random2 > 80)
    {
      std::cout << "doubled up beginning" << std::endl;
      for (int i=0; i<4; i++)
      {
        teenth_array[i+8] = teenth_array[i];
      }
    }
    return teenth_array;
  }

  int* get_random_hi_hat_standard()
  {
    int arrnum = rand() % number_of_standards;
    return &hi_hat_standards[arrnum][0];
  }
}
