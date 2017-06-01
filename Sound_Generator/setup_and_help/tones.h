#ifndef TONES_H
#define TONES_H

#include <array>
#include <iostream>
#include <math.h>

namespace tones
{
  double* convert_notes_to_tones(int* note_array, int array_length);
  double convert_note_to_tone(int note);
}

#endif
