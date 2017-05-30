#ifndef TOM_WRITER_H
#define TOM_WRITER_H

#include <array>
#include <math.h>
#include <iostream>

namespace drum_imports
{
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

namespace audio_helper
{
  extern int teenth_slice_as_frame(int beat);
  extern int bar_duration_in_frames();
  extern int calculate_total_frames(int total_bars, double end_hang_time=3);
  extern int calculate_total_frames(int total_bars);
}

namespace drum_track
{
  extern double** tom_track;
  extern int main_buffer_size;
  extern int main_buffer_channels;
}

namespace tom_writer
{
  void write_from_array_at_bar(int teenth_array [16], int bar);
}

#endif
