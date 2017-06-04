#ifndef BASS_ARRANGEMENT_H
#define BASS_ARRANGEMENT_H

#include <iostream>

namespace notes
{
  extern int convert_to_note_value(int note, int mode, int starting_note);
  extern int** get_note_values_from_chords(int** chords, int mode, int starting_note);
}

namespace music_gen
{
  extern int** generate_bar_from_chords(int** chords, int octave);
  extern int** modify_bar_to_new_mode_or_key(int** bar, int mode, int starting_note, int new_mode, int new_starting_note, int octave);
  extern int** generate_bar_from_chords_and_drums(int* kick, int* snare, int* hi_hat, int** chords, int octave);
  extern int** modify_bar_for_fill(int** bar, int* fill);
  extern int** stick_to_root(int* kick, int* snare, int* hi_hat, int** chords, int octave);
}

namespace chord_gen
{
  // extern int* chord_notes(int chord_root, int mode, int starting_note);
  extern int** one45_hqq(int mode, int starting_note);
  extern int** modify_chords(
    int** chord_arr,
    int mode,
    int starting_note,
    int new_mode,
    int new_starting_note
  );
  extern int** solid_three_chords(int mode, int starting_note);
  extern int** chords_from_kick(int* kick_teenth, int mode, int starting_note);
}

namespace bass_writer
{
  extern void write_bass_bar(int** bass_teenth_array, int bar);
}

namespace bass_arrangement
{
  // int num_of_unique_sections(int* arrangement, int total_sections);
  void create_tracks_from_arrangement_and_chords(
    int** key_arrangement,
    int* chord_arrangemnt,
    int* bass_arrangement,
    int* section_length,
    int total_sections,
    int*** drum_arrangement
  );
}

#endif
