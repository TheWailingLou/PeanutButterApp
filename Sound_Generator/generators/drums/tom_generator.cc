#include "tom_generator.h"

namespace tom_generator
{
  int* generate_tom_teenth_array(int begin_at_teenth)
  {
    int* tom_array = new int [16];
    int cap;
    bool downward = rand()%10 < 7;
    if (downward)
    {
      cap = 4;
    } else {
      cap = 0;
    }
    int last_tom = 0;
    int streak = 0;
    int hit_streak = 0;
    for (int i=0; i<16; i++)
    {
      if (i <= (16 - begin_at_teenth) || i == 15)
      {
        tom_array[i] = 0;
      } else {
        bool silence = rand()%10 < 3;
        int tom_num;
        if (silence)
        {
          tom_num = 0;
        } else {
          if (downward)
          {
            tom_num = rand()%(cap+1);
          } else {
            tom_num = (rand()%(4-cap)) + cap;
          }
          tom_num += 1;
        }
        if (last_tom == tom_num)
        {
          streak += 1;
        } else {
          streak = 0;
        }

        if (streak > 3)
        {
          tom_num += 2;
          tom_num %= 5;
        }

        if (tom_num != 0)
        {
          hit_streak += 1;
          if (hit_streak >= 4)
          {
            tom_num = 0;
            hit_streak = 0;
          } else {
            cap = tom_num - 1;
          }
        }
        last_tom = tom_num;
        tom_array[i] = tom_num;
      }
    }
    return tom_array;
  }
}
