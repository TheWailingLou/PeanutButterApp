#ifndef CRASH_WRITER_H
#define CRASH_WRITER_H

#include <array>
#include <math.h>
#include <iostream>
// #include <stdlib.h>
// #include <ctime>

namespace drum_imports
{
  extern double** crash1_buffer;
  extern int crash1_buffer_channels;
  extern int crash1_buffer_size;

  extern double** crash2_buffer;
  extern int crash2_buffer_channels;
  extern int crash2_buffer_size;
}

namespace audio_helper
{
  extern int time_as_frame(double time_in_seconds);
  extern int beat_as_frame(int beat);
  extern int teenth_slice_as_frame(int beat);
  extern int bar_duration_in_frames();
  extern int calculate_total_frames(int total_bars, double end_hang_time=3);
  extern int calculate_total_frames(int total_bars);
}

namespace drum_track
{
  extern double** crash_track;
  extern int main_buffer_size;
  extern int main_buffer_channels;
}


namespace crash_writer
{
  void write_from_array_at_bar(int teenth_array [16], int bar);
}

#endif
