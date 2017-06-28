#ifndef ARRANGEMENT_ALL_H
#define ARRANGEMENT_ALL_H

#include <array>
#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <vector>

namespace bass_arrangement
{
  extern void create_tracks_from_arrangement_and_chords(
    int** key_arrangement,
    int* chord_arrangemnt,
    int* bass_arrangement,
    int* section_length,
    int total_sections,
    int*** kick_drum_arrangement
  );

}

namespace drum_arrangement
{
  extern int drum_arrangement_standard_1 [5][7];
  extern int drum_arrangement_standard_2 [5][12];
  extern int*** create_tracks_from_arrangement(
    int** arrangement,
    int* section_length,
    int total_sections
  );
}

namespace bass_writer
{
  extern void final_note(int note, int duration, int octave, int bar);
}

namespace snare_writer
{
  extern void write_from_array_at_bar(int teenth_array [16], int bar);
}

namespace arrangement_all
{
  int mod_four_bars_bass (int** key_arrangement, int* chord_arrangement, int* bass_arrangement, int current_section, int main_start);
  void mod_four_bars_drums (int** drum_arrangement, int current_section, int main_start, int root_section);
  void intro_bars (int* bass_arrangement, int** drum_arrangement, int main_start);
  void end_bars (int* bass_arrangement, int** key_arrangement, int** drum_arrangement, int end_length, int total_length, int main_start);

  int* get_section_lengths();
  void create_tracks(int starting_note, int mode, int* section_lengths_arr);
}



#endif
