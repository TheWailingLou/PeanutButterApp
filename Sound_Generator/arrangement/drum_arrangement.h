#ifndef DRUM_ARRANGMENT_H
#define DRUM_ARRANGMENT_H

#include <array>
#include <math.h>
#include <iostream>

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
  extern void write_crash_at_bar(int crash, int bar);
  extern void write_from_array_at_bar(int teenth_array [16], int bar);
}

namespace audio_helper
{
  extern int* silence_hits(int* silence_array, int* teenth_array);
  extern int* silence_array(int start_teenth, int end_teenth);
}

namespace arrangement_main
{
  extern int section_length_standard_1;
}

namespace drum_arrangement
{
  int drum_arrangement_standard_1 [5][7] = {
    // hi hat
    {0,1,2,1,2,3,0},
    // snare
    {0,1,2,1,2,3,0},
    // kick
    {0,1,2,1,2,3,0},
    // tom fills
    {-1,8,8,8,4,8,-1},
    // crash
    {2,0,1,2,1,2,1}
  };

  int drum_arrangement_standard_2 [5][12] = {
    // hi hat
    {1,1,2,2,1,1,2,2,3,3,1,0},
    // snare
    {1,1,1,1,2,2,2,2,3,1,1,0},
    // kick
    {1,1,1,1,2,2,2,2,3,1,1,0},
    // tom fills
    {4,8,4,8,4,8,8,12,-1,8,4,-1},
    // crash
    {0,0,2,0,1,2,1,2,1,0,2,1}
  };

  void create_tracks_from_arrangement(
    int** arrangement,
    int* section_length,
    int total_sections
  );
  int num_of_unique_sections(int* arrangement, int total_sections);
}

#endif
