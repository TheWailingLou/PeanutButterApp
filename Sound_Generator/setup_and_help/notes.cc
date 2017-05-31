#include "notes.h"

namespace notes
{
  int* get_single_octave(int starting_note, int mode, bool harmonic)
  {
    int* spectrum = new int [7];
    int* step_pattern = scales::get_step_pattern(mode, harmonic);
    spectrum[0] = starting_note;
    for (int i=1; i<7; i++)
    {
      int note = spectrum[i-1] + step_pattern[i%7];
      spectrum[i] = note;
    }
    return spectrum;
  }

  int* get_all_notes(int starting_note, int mode, bool harmonic)
  {
    int* spectrum = new int [84];
    int* step_pattern = scales::get_step_pattern(mode, harmonic);
    // int highest_note = find_highest_note(starting_note);
    int lowest_note = find_lowest_note(starting_note);

    spectrum[0] = lowest_note;
    for (int i=1; i<84; i++)
    {
      int note = spectrum[i-1] + step_pattern[i%7];
      spectrum[i] = note;
    }
    return spectrum;
  }

  int find_lowest_note(int starting_note)
  {
    int i = starting_note;
    while (i > 11)
    {
      i -= 12;
    }
    return i;
  }

  int find_highest_note(int starting_note)
  {
    int i = starting_note;
    while (i < 133)
    {
      i += 12;
    }
    return i;
  }
}
