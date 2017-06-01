#ifndef BASS_ARRANGEMENT_H
#define BASS_ARRANGEMENT_H

namespace notes
{
  extern int convert_to_note_value(int note, int mode, int starting_note);
  extern int** get_note_values_from_chords(int** chords, int mode, int starting_note);
}

namespace music_gen
{
  extern int** generate_bar_from_chords(int** chords, int octave);
  extern int** modify_bar_to_new_mode_or_key(int** bar, int mode, int starting_note, int new_mode, int new_starting_note, int octave);
}

namespace bass_writer
{
  extern void write_bass_bar(int** bass_teenth_array, int bar);
}

namespace bass_arrangement
{
  // int num_of_unique_sections(int* arrangement, int total_sections);
  void create_tracks_from_arrangement_and_chords(
    int* arrangement,
    int** chords,
    int* section_length,
    int total_sections
  );
}

#endif
