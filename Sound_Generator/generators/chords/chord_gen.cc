#include "chord_gen.h"

namespace chord_gen
{
  int** modify_chords(int** chord_arr, int mode, int starting_note, int new_mode, int new_starting_note)
  {
    if (mode == new_mode && starting_note == new_starting_note)
    {
      return chord_arr;
    }
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

  int* chord_notes(int chord_root, int mode, int starting_note)
  {
    int lowest_note = notes::find_lowest_note(starting_note);
    int* scale = notes::get_single_octave(lowest_note, mode, false);
    int* chord = new int [6];
    std::cout << "\nChord Notes: ";
    for (int i=0; i<6; i++) {
      int scale_index = (((i*2)%6) + chord_root) % 7;
      std::cout << " " << scale[scale_index];
      chord[i] = scale[scale_index];
    }
    std::cout << "\n\n" << std::endl;
    return chord;
  }

  int** solid_three_chords(int mode, int starting_note)
  {
    int main_structures [4][3] = {
      {1,4,5},
      {1,2,5},
      {1,4,7},
      {1,2,5}
    };
    int secondaries [3][3] = {
      {1,2,7},
      {1,2,3},
      {1,6,7}
    };
    int tertiaries [5][3] = {
      {1,2,6},
      {1,2,4},
      {1,5,6},
      {1,3,4},
      {1,2,4}
    };
    int* three_chords;
    if (rand()%100 < 70) {
      three_chords = main_structures[rand()%4];
    } else {
      if (rand()%100 < 60)
      {
        three_chords = secondaries[rand()%3];
      } else {
        three_chords = tertiaries[rand()%5];
      }
    }
    std::cout << three_chords[0] << three_chords[1] << three_chords[2] << std::endl;

    int* chord_1 = chord_notes(three_chords[0]-1, mode, starting_note);
    int* chord_2 = chord_notes(three_chords[1]-1, mode, starting_note);
    int* chord_3 = chord_notes(three_chords[2]-1, mode, starting_note);

    int** chord_teenth = new int* [16];
    for (int i=0; i<16; i++)
    {
      chord_teenth[i] = new int [7];
      chord_teenth[i][0] = -1;
      for (int j=0; j<6; j++)
      {
        chord_teenth[i][j+1] = 0;
      }
    }

    int chord2_index = rand()%15 + 1;
    int chord3_index = rand()%15 + 1;


    if (chord2_index != chord3_index)
    {
      int chord1_duration;
      int chord2_duration;
      int chord3_duration;

      if (chord2_index < chord3_index) {
        chord1_duration = chord2_index;
        chord2_duration = chord3_index - chord2_index;
        chord3_duration = 16 - chord3_index;
      } else {
        chord1_duration = chord3_index;
        chord3_duration = chord2_index - chord3_index;
        chord2_duration = 16 - chord2_index;
      }
      chord_teenth[0][0] = chord1_duration;
      chord_teenth[chord2_index][0] = chord2_duration;
      chord_teenth[chord3_index][0] = chord3_duration;
      for (int j=0; j<6; j++)
      {
        chord_teenth[0][j+1] = chord_1[j];
        chord_teenth[chord2_index][j+1] = chord_2[j];
        chord_teenth[chord3_index][j+1] = chord_3[j];
      }
      // std::cout << "duration: " << chord1_duration << " " << chord2_duration << " " << chord3_duration << std::endl;
      // std::cout << "index: " << chord2_index << " " << chord3_index <<  std::endl;
    } else {
      if (rand()%2 == 0) {
        chord_teenth[0][0] = chord2_index;
        chord_teenth[chord2_index][0] = 16 - chord2_index;
        for (int j=0; j<6; j++)
        {
          chord_teenth[0][j+1] = chord_1[j];
          chord_teenth[chord2_index][j+1] = chord_2[j];
        }
      } else {
        chord_teenth[0][0] = chord3_index;
        chord_teenth[chord3_index][0] = 16 - chord3_index;
        for (int j=0; j<6; j++)
        {
          chord_teenth[0][j+1] = chord_1[j];
          chord_teenth[chord3_index][j+1] = chord_3[j];
        }
      }
    }
    return chord_teenth;
  }
}
