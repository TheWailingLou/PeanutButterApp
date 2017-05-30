#ifndef DRUM_TRACK
#define DRUM_TRACK

#include <array>
#include <math.h>
#include <iostream>
#include <stdlib.h>

namespace hi_hat_generator
{
  extern int* generate_hi_hat_teenth_array();
  extern int* get_random_hi_hat_standard();
}

namespace kick_generator
{
  extern int* get_random_kick_standard();
}

namespace snare_generator
{
  extern int* get_random_snare_standard();
}

namespace tom_generator
{
  int* generate_tom_teenth_array(int begin_at_teenth);
}

namespace snare_generator
{
  extern int* get_random_snare_standard();
}

namespace hi_hat_writer
{
  extern void write_from_array_at_bar(int teenth_array [16], int bar);
}

namespace kick_writer
{
  extern void write_from_array_at_bar(int teenth_array [16], int bar);
}

namespace tom_writer
{
  extern void write_from_array_at_bar(int teenth_array [16], int bar);
}

namespace snare_writer
{
  extern void write_from_array_at_bar(int teenth_array [16], int bar);
}

namespace crash_writer
{
  extern void write_from_array_at_bar(int teenth_array [16], int bar);
}

namespace audio_helper
{
  extern int calculate_total_frames(int total_bars, double end_hang_time=3);
  extern int calculate_total_frames(int total_bars);
  extern int* silence_hits(int* silence_array, int* teenth_array);
}

namespace drum_track
{
  double** main_buffer;
  int main_buffer_size;
  int main_buffer_channels;

  double** crash_track;
  double** hi_hat_track;
  double** kick_track;
  double** ride_track;
  double** snare_track;
  double** tom_track;

  void setup_buffers(int total_bars, double end_hang_time);
  void test_creation();
  void free_all_track_memory();

}

#endif
