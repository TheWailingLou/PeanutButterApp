#include "bass_writer.h"

namespace bass_writer
{
  void write_bass_bar(int** bass_teenth_array, int bar)
  {
    for (int i=0; i<16; i++)
    {
      int note = bass_teenth_array[i][0];
      int teenth_duration = bass_teenth_array[i][1];
      if (note != -1)
      {
        bass_voice::write_note_at_location(note, teenth_duration, i, bar);
      }
    }
  }
}
