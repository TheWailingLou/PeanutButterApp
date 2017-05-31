#ifndef TONES_H
#define TONES_H

#include <array>
#include <iostream>
#include <math.h>

// namespace notes
// {
//   extern int* get_single_octave(int starting_note, int mode, bool harmonic);
//   extern int* get_all_notes(int starting_note, int mode, bool harmonic);
// }

namespace tones
{
  double* convert_notes_to_tones(int* note_array, int array_length);
  double convert_note_to_tone(int note);
  // int* get_all_tones(int starting_note, int mode, bool harmonic);
  // int* get_single_octave()
}

#endif
