#ifndef KICK_WRITER_H
#define KICK_WRITER_H

#include <array>
#include <math.h>
#include <iostream>
// #include <stdlib.h>
// #include <ctime>

namespace drum_imports
{
  extern double** kick_buffer;
  extern int kick_buffer_channels;
  extern int kick_buffer_size;
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
  extern double** kick_track;
  extern int main_buffer_size;
  extern int main_buffer_channels;
}

// namespace kick_generator
// {
//   extern int* generate_hi_hat_teenth_array();
//   extern int* get_random_hi_hat_standard();
// }

namespace kick_writer
{
  void write_from_array_at_bar(int teenth_array [16], int bar);
}

#endif
