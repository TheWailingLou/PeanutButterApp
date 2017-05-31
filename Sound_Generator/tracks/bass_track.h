#ifndef DRUM_TRACK_H
#define DRUM_TRACK_H

#include <array>
#include <math.h>
#include <iostream>
#include <stdlib.h>

namespace bass_main
{
  extern int bass_line_test [16][2];
}

namespace bass_writer
{
  extern void write_bass_bar(int** bass_teenth_array, int bar);
}

namespace audio_helper
{
  extern int calculate_total_frames(int total_bars, double end_hang_time=3);
  extern int calculate_total_frames(int total_bars);
  extern int* silence_hits(int* silence_array, int* teenth_array);
}

namespace bass_arrangement
{
  // extern int bass_arrangement_standard_1 [5][7];
  // extern int bass_arrangement_standard_2 [5][12];
  extern void create_tracks_from_arrangement(
    int** arrangement,
    int* section_length,
    int total_sections
  );
}

namespace arrangement_main
{
  extern int section_length_standard_1 [7];
  extern int section_length_standard_2 [12];
}

namespace bass_track
{
  double** main_buffer;
  int main_buffer_size;
  int main_buffer_channels;

  double** bass_track_1;
  double** bass_track_2;

  void setup_buffers(int total_bars, double end_hang_time);
  void test_creation();
  void free_all_track_memory();
}

#endif