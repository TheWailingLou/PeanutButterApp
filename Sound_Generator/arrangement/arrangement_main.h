#ifndef ARRANGEMENT_MAIN_H
#define ARRANGEMENT_MAIN_H

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

namespace arrangement_main
{
  int section_length_standard_1 [7]  = {1,4,4,4,2,4,1};
  int section_length_standard_2 [12] = {4,4,4,4,4,4,4,4,4,4,8,1};

  int num_of_unique_sections(int* arrangement, int total_sections);

  void generate_arrangements_and_create_tracks(int mode, int starting_note);

}

#endif
