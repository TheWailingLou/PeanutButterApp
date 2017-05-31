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

  int* get_octave_range(int octaves_below, int octaves_above, int starting_note, int mode, bool harmonic)
  {
    int num_of_notes = 7 + 7*octaves_above + 7*octaves_below;

    int lowest_note = starting_note;
    for (int i=0; i<octaves_below; i++)
    {
      lowest_note -= 12;
    }
    int invalid_notes = 0;
    while (lowest_note < 0)
    {
      lowest_note += 12;
      invalid_notes += 7;
    }
    num_of_notes -= invalid_notes;
    if (num_of_notes < 0)
    {
      num_of_notes = 7;
    }
    int* spectrum = new int [num_of_notes];
    int* step_pattern = scales::get_step_pattern(mode, harmonic);
    spectrum[0] = lowest_note;
    for (int i=1; i<num_of_notes; i++)
    {
      int note = spectrum[i-1] + step_pattern[(i-1)%7];
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
