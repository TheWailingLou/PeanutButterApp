#include "tones.h"

namespace tones
{
  double* convert_notes_to_tones(int* note_array, int array_length)
  {
    double* tone_array = new double [array_length];
    for (int i=0; i<array_length; i++)
    {
      double note_as_double = (double) note_array[i];
      double pow_exponent = ((note_as_double + 12.0) - 69.0) / 12.0;
      double note_as_tone = pow(2.0, pow_exponent) * 440.0;
      tone_array[i] = note_as_tone;
    }
    return tone_array;
  }
  double convert_note_to_tone(int note)
  {
    double note_as_double = (double) note;
    double pow_exponent = ((note_as_double + 12.0) - 69.0) / 12.0;
    double note_as_tone = pow(2.0, pow_exponent) * 440.0;
    return note_as_tone;
  }
}
