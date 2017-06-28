#ifndef SNARE_WRITER_H
#define SNARE_WRITER_H

#include <array>
#include <math.h>
#include <iostream>

namespace drum_imports
{
  extern double** snare_buffer;
  extern int snare_buffer_channels;
  extern int snare_buffer_size;
}

namespace audio_helper
{
  extern int teenth_slice_as_frame(int beat);
  extern int bar_duration_in_frames();
  extern int calculate_total_frames(int total_bars, double end_hang_time=3);
  extern int calculate_total_frames(int total_bars);
}

namespace drum_track
{
  extern double** other_drum_tracks;
  extern int main_buffer_size;
  extern int main_buffer_channels;
}

namespace snare_writer
{
  void write_from_array_at_bar(int teenth_array [16], int bar);
}

#endif
