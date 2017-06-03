#ifndef CHORD_GEN
#define CHORD_GEN

#include <array>
#include <stdlib.h>
#include <iostream>

namespace scales
{
  extern int* get_step_pattern(int mode, bool harmonic);
}


namespace notes
{
  extern int* get_single_octave(int starting_note, int mode, bool harmonic);
  extern int find_lowest_note(int starting_note);
  extern int get_octave(int note);
  // extern int convert_to_note_value(int note, int mode, int starting_note);
  extern int** get_note_values_from_chords(int** chords, int mode, int starting_note);
}

namespace chord_gen
{
  int* chord_notes(int chord_root, int mode, int starting_note);
  int** one45_hqq(int mode, int starting_note);
  int** modify_chords(
    int** chord_arr,
    int mode,
    int starting_note,
    int new_mode,
    int new_starting_note
  );
  int** solid_three_chords(int mode, int starting_note);
  int** chords_from_kick(int* kick_teenth, int mode, int starting_note);
  // int** generate_random_chord_bar(int mode, int starting_note, int num_of_chords);
}

#endif
