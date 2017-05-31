#ifndef BASS_WRITER_H
#define BASS_WRITER_H

#include <array>
#include <math.h>
#include <stdlib.h>

namespace tones
{
  extern double convert_note_to_tone(int note);
}

namespace bass_track
{
  extern double** bass_track_1;
  extern double** bass_track_2;

  extern int main_buffer_size;
  extern int main_buffer_channels;
}

namespace bass_voice
{
  void write_note_at_location(
    int note,
    int teenth_duration,
    int teenth_location,
    int bar
  );
}

namespace bass_writer
{
  void write_bass_bar(int** bass_teenth_array, int bar);
}

#endif
