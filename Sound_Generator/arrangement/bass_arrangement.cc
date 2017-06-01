#include "bass_arrangement.h"

namespace bass_arrangement
{
  int num_of_unique_sections(int* arrangement, int total_sections)
  {
    int unique_sections = 0;
    for (int section=0; section<total_sections; section++)
    {
      int section_num = arrangement[section];
      if (section_num > unique_sections) {
        unique_sections = section_num;
      }
    }
    return unique_sections;
  }

  void create_tracks_from_arrangement_and_chords(int* arrangement, int** chords, int* section_length, int total_sections)
  {
    // int unique_sections = num_of_unique_sections;
  }
}
