#include "music_gen.h"

namespace music_gen
{
  int** generate_bar_from_chords(int** chords, int octave)
  {
    int* current_chord = chords[0];
    int current_chord_duration = current_chord[0];
    int note_remaining_duration = 0;
    bool teenth_lock = false;
    bool eighth_lock = false;

    int** teenth_array = new int* [16];
    for (int i=0; i<16; i++)
    {

      if (chords[i][0] != -1) {
        current_chord = chords[i];
        current_chord_duration = current_chord[0];
        teenth_lock = false;
        eighth_lock = false;
      }
      teenth_array[i] = new int [2];
      // std::cout << "\n\nremaining duration: " << note_remaining_duration << std::endl;
      // std::cout << "current_chord_duration: " << current_chord_duration << std::endl;
      if (note_remaining_duration > 0) {
        teenth_array[i][0] = -1;
        teenth_array[i][1] = 1;
      } else {
        int note_index = 1+(rand()%6);
        int note = current_chord[note_index] + (octave * 12);
        int duration;

        int lock_prob = rand()%100;

        if (lock_prob > 80)
        {
          eighth_lock = true;
          teenth_lock = false;
        } else if (lock_prob < 20) {
          teenth_lock = true;
          eighth_lock = false;
        }

        if (eighth_lock)
        {
          duration = 2;
        } else if (teenth_lock) {
          duration = 1;
        } else {
          int duration_prob = rand()%100;
          if (duration_prob < 50) {
            duration = 2;
          } else if (duration_prob >= 50 && duration_prob < 70) {
            duration = 4;
          } else if (duration_prob >= 70 && duration_prob < 85) {
            duration = 1;
          } else {
            duration = rand()%current_chord_duration + 1;
          }
        }

        if (duration > current_chord_duration) {
          duration = current_chord_duration;
        }

        if (rand()%100 < 10 && !eighth_lock && !teenth_lock) {
          note = -1;
          duration = 1;
        }

        teenth_array[i][0] = note;
        teenth_array[i][1] = duration;

        note_remaining_duration = duration;
      }
      current_chord_duration -= 1;
      note_remaining_duration -= 1;
    }
    return teenth_array;
  }
}
