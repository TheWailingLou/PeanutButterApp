#include "key_and_chord_arrangement.h"

namespace key_and_chord_arrangement
{
  int*** create_chords_from_arrangement(int* chord_arrangemnt, int** key_arrangement, int* section_lengths, int num_of_sections) {
    int*** chord_arr = new int** [num_of_sections];
    for (int section=0; section<num_of_sections; section++)
    {
      int mode = key_arrangement[section][0];
      int starting_note = key_arrangement[section][1];
      // TODO after an actual chord generator is set up, this will be quite a bit more complex;
      chord_arr[section] = chord_gen::one45_hqq(mode, starting_note);
    }
  }
}
