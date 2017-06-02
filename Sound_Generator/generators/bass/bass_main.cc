#include "bass_main.h"


namespace bass_main
{
  int** generate_test_teenth(int mode, int starting_note)
  {
    int** teenth_arr = new int* [16];
    int* notes_in_scale = notes::get_octave_range(1, 1, starting_note, mode, false);
    // int note_length = 21;
    for (int i=0; i<16; i++) {
      teenth_arr[i] = new int [2];
      if (i%2 == 0)
      {
        teenth_arr[i][0] = notes_in_scale[i/2];
        teenth_arr[i][1] = 2;
      }
    }
    return teenth_arr;
  }

  int** generate_bass_bar(int mode, int starting_note)
  {
    int** teenth_arr = new int* [16];
    int* notes_in_scale = notes::get_octave_range(1, 1, starting_note, mode, false);
    // int note_length = 21;
    int note_end = 0;
    // notes_in_scale[(i/2)+4]; // 5th
    for (int i=0; i<16; i++)
    {
      teenth_arr[i] = new int [2];
      int note = -1;
      int arrnote = -1;
      // int random = rand()%100;
      if (i == 0)
      {
        if (rand()%100 < 60) {
          arrnote = 7;
          // note = notes_in_scale[7];
        } else {
          if (rand()%100 < 50)
          {
            arrnote = 11;
            // note = notes_in_scale[]
          } else {
            if (rand()%100 < 80)
            {
              arrnote = 10;
            } else {
              arrnote = 7 + rand()%7;
            }
          }
        }
      } else {
        int random = rand()%100;
        if (random < 20)
        {
          arrnote = 7;
        } else if (random >= 20 && random < 40) {
          arrnote = 11;
        } else if (random >= 40 && random < 55) {
          arrnote = 10;
        } else if (random >= 55 && random < 80) {
          arrnote = 7+ rand()%7;
        }
      }
      if (arrnote != -1)
      {
        int random = rand()%100;
        if (random < 20)
        {
          arrnote -= 7;
        } else if  (random > 80) {
          arrnote += 7;
        }
        note = notes_in_scale[arrnote];
      }

      if (note_end > i) {
        note = -1;
      }

      teenth_arr[i][0] = note;


      int duration = 1;
      if (note != -1)
      {
        int duration_random = rand()%100;
        if (duration_random < 40)
        {
          duration = 2;
        } else if (duration_random >= 40 && duration_random < 60) {
          duration = 4;
        } else if (duration_random >= 60 && duration_random < 70) {
          duration = 8;
        } else if (duration_random >= 70 && duration_random < 78) {
          duration = 6;
        } else if (duration_random >= 78 && duration_random < 83) {
          duration = 3;
        } else if (duration_random >= 83 && duration_random < 86) {
          duration = 5;
        } else if (duration_random >= 86 && duration_random < 88) {
          duration = 7;
        } else if (duration_random >= 88 && duration_random < 92) {
          duration = 16;
        }
      }



      if (duration > 16-i)
      {
        duration = 16-i;
      }
      if (note_end <= i) {
        note_end = i +duration;
      }


      // std::cout << "arrnote " << arrnote << "note " << note << "duration " << duration << std::endl;
      teenth_arr[i][1] = duration;
    }
    return teenth_arr;
  }
}
