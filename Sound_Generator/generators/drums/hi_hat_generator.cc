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
      for (int i=4; i<8; i++)
      {
        teenth_array[i+8] = teenth_array[i];
      }
    }
    if (random2 > 80)
    {
      for (int i=0; i<4; i++)
      {
        teenth_array[i+8] = teenth_array[i];
      }
    }
    return generate_openings(teenth_array);
  }

  int* get_random_hi_hat_standard()
  {
    int arrnum = rand() % number_of_standards;
    return &hi_hat_standards[arrnum][0];
  }

  int* generate_openings(int* teenth_array)
  {
    std::vector<int> possibilities;
    int* array_with_openings = new int [16];
    for (int i=0; i<16; i++)
    {
      array_with_openings[i] = teenth_array[i];
    }

    for (int i=0; i<15; i++) {
      if (teenth_array[i] == 1 && teenth_array[i+1] == 0)
      {
        possibilities.push_back(i);
      }
    }

    if (possibilities.size() == 0 || rand()%10 > 6) {
      int random_number = rand()%16;
      possibilities.push_back(random_number);
    }
    std::vector<int> openings = random_from_vector(possibilities);
    for (int i=0; i<(int)openings.size(); i++)
    {
      array_with_openings[openings[i]] = 2;
    }
    return array_with_openings;
  }

  std::vector<int> random_from_vector(std::vector<int> possibilities)
  {
    int number_of_openings = rand()%((int)possibilities.size());
    if (number_of_openings > 2)
    {
      number_of_openings = 1 + rand()%3;
    }
    std::vector<int> openings;
    for (int i=0; i<number_of_openings; i++)
    {
      int random = rand()%((int)possibilities.size());
      openings.push_back(possibilities[random]);
    }
    while (((int)openings.size()) > 2) {
      openings.pop_back();
    }
    return openings;
  }
}
