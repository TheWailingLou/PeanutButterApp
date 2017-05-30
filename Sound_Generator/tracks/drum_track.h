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

namespace tom_generator
{
  int* generate_tom_teenth_array(int begin_at_teenth);
}

namespace snare_generator
{
  extern int* get_random_snare_standard();
}

namespace drum_imports
{
  extern double** kick_buffer;
  extern int kick_buffer_channels;
  extern int kick_buffer_size;

  extern double** crash1_buffer;
  extern int crash1_buffer_channels;
  extern int crash1_buffer_size;

  extern double** crash2_buffer;
  extern int crash2_buffer_channels;
  extern int crash2_buffer_size;

  extern double** hi_hat_closed_buffer;
  extern int hi_hat_closed_buffer_channels;
  extern int hi_hat_closed_buffer_size;

  extern double** hi_hat_open_buffer;
  extern int hi_hat_open_buffer_channels;
  extern int hi_hat_open_buffer_size;

  extern double** ride1_buffer;
  extern int ride1_buffer_channels;
  extern int ride1_buffer_size;

  extern double** ride2_buffer;
  extern int ride2_buffer_channels;
  extern int ride2_buffer_size;

  extern double** snare_buffer;
  extern int snare_buffer_channels;
  extern int snare_buffer_size;

  extern double** snare_soft_buffer;
  extern int snare_soft_buffer_channels;
  extern int snare_soft_buffer_size;

  extern double** tom_floor1_buffer;
  extern int tom_floor1_buffer_channels;
  extern int tom_floor1_buffer_size;

  extern double** tom_floor2_buffer;
  extern int tom_floor2_buffer_channels;
  extern int tom_floor2_buffer_size;

  extern double** tom_high_buffer;
  extern int tom_high_buffer_channels;
  extern int tom_high_buffer_size;

  extern double** tom_mid_buffer;
  extern int tom_mid_buffer_channels;
  extern int tom_mid_buffer_size;

  extern double** tom_mid_high_buffer;
  extern int tom_mid_high_buffer_channels;
  extern int tom_mid_high_buffer_size;
}

namespace hi_hat_writer
{
  extern void write_from_array_at_bar(int teenth_array [16], int bar);
}

namespace tom_writer
{
  extern void write_from_array_at_bar(int teenth_array [16], int bar);
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

  // void add_drum_to_track_from_teenth_array_at_bar(
  //   double** drum,
  //   int drum_size,
  //   double** track,
  //   int teenth_array [16],
  //   int bar=0
  // );

  // void add_crash_to_track_at_beat_or_bar(
  //   double** crash,
  //   int crash_size,
  //   double** track,
  //   int beat,
  //   int bar
  // );

  // void remove_hits_from_teenth_array_via_array(
  //   int* silence_array,
  //   int* teenth_array
  // );
  void test_creation();
  void free_all_track_memory();

}

#endif
