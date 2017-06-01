#include "chord_gen.h"

namespace chord_gen
{
  int** modify_chords(int** chord_arr, int mode, int starting_note, int new_mode, int new_starting_note)
  {
    int** note_values = notes::get_note_values_from_chords(chord_arr, mode, starting_note);
    int new_lowest_note = notes::find_lowest_note(new_starting_note);
    int* new_scale = notes::get_single_octave(new_lowest_note, new_mode, false);
    int** new_chords = new int* [16];
    for (int i=0; i<16; i++)
    {
      new_chords[i] = new int [7];
      new_chords[i][0] = chord_arr[i][0];
      if (new_chords[i][0] == -1)
      {
        for (int j=0; j<6; j++)
        {
          new_chords[i][j+1] = 0;
        }
      } else {
        for (int j=0; j<6; j++)
        {
          int note_val = note_values[i][j];
          if (note_val == -1)
          {
            std::cout << "note was -1 ERROR" << std::endl;
            note_val = 0;
          }
          new_chords[i][j+1] = new_scale[note_val];
        }
      }
    }
    return new_chords;
  }

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
    delete[] scale;
    return chords;
  }
}
