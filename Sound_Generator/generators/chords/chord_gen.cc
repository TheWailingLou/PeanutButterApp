#include "chord_gen.h"

namespace chord_gen
{
  int** one45_hqq(int mode, int starting_note)
  {


    int lowest_note = notes::find_lowest_note(starting_note);
    int* scale = notes::get_single_octave(lowest_note, mode, false);

    int** chords = new int* [16];
    for (int i=0; i<16; i++)
    {
      chords[i] = new int [7];
      chords[i][0] = -1;
      for (int j=1; j<7; j++)
      {
        chords[i][j] = scale[j-1];
      }
      if (i == 0)
      {
        chords[i][0] = 8;
        for (int j=0; j<6; j++)
        {
          chords[i][j+1] = scale[(j*2)%6];
        }
      } else if (i == 8) {
        chords[i][0] = 4;
        for (int j=0; j<6; j++)
        {
          int scale_index = ((j*2)%6 + 3)%7;
          chords[i][j+1] = scale[scale_index];
        }
      } else if (i == 12){
        chords[i][0] = 4;
        for (int j=0; j<6; j++)
        {
          int scale_index = ((j*2)%6 + 4)%7;
          chords[i][j+1] = scale[scale_index];
        }
      }
    }
    return chords;
  }
}
