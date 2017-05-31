#ifndef AUDIO_HELPER
#define AUDIO_HELPER

#include <array>
#include <math.h>
#include <iostream>

namespace audio_setup
{
  extern int sample_rate;
  extern int tempo;
}

namespace audio_helper
{
  int time_as_frame(double time_in_seconds);
  int beat_as_frame(int beat);
  int teenth_slice_as_frame(int beat);
  int bar_duration_in_frames();
  int calculate_total_frames(int total_bars, double end_hang_time=3);
  int calculate_total_frames(int total_bars);
  int* silence_hits(int silence_array [16], int* teenth_array);
  int* silence_array(int start_teenth, int end_teenth);
}

#endif
