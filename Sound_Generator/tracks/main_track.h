#ifndef MAIN_TRACK_H
#define MAIN_TRACK_H

#include <array>
#include <math.h>
#include <iostream>
#include <stdlib.h>

namespace audio_helper
{
  extern int calculate_total_frames(int total_bars, double end_hang_time=3);
  extern int calculate_total_frames(int total_bars);
  extern int* silence_hits(int* silence_array, int* teenth_array);
}

namespace audio_setup {
  extern int mode;
  extern int key;
}

namespace drum_track
{
  extern double** main_buffer;
  extern void copy_to_track();
  extern void setup_buffers(int total_bars, double end_hang_time);
}

namespace bass_track
{
  extern double** main_buffer;
  extern void copy_to_track();
  extern void setup_buffers(int total_bars, double end_hang_time);
}

namespace arrangement_all
{
 extern int* get_section_lengths();
 extern void create_tracks(int starting_note, int mode, int* section_lengths_arr);
}

namespace main_track
{
  double** main_buffer;
  int main_buffer_size;
  int main_buffer_channels;
  void setup_buffers(int total_bars, double end_hang_time);
  void test_creation();
  void free_all_track_memory();
}

#endif
