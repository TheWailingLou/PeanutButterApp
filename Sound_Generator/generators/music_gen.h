#ifndef MUSIC_GEN_H
#define MUSIC_GEN_H

#include <stdlib.h>
#include <array>
#include <iostream>

namespace notes
{
  extern int convert_to_note_value(int note, int mode, int starting_note);
  extern int** get_note_values_from_chords(int** chords, int mode, int starting_note);
  extern int* get_single_octave(int starting_note, int mode, bool harmonic);
  extern int find_lowest_note(int starting_note);
}

namespace chord_gen
{
  extern int** modify_chords(
    int** chord_arr,
    int mode,
    int starting_note,
    int new_mode,
    int new_starting_note
  );
}

namespace music_gen
{
  int** generate_bar_from_chords(int** chords, int octave);
  int** modify_bar_to_new_mode_or_key(int** bar, int mode, int starting_note, int new_mode, int new_starting_note, int octave);
  int** generate_bar_from_chords_and_drums(int* kick, int* snare, int* hi_hat, int** chords, int octave);
}

#endif
