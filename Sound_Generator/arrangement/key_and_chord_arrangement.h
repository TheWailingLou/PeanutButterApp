#ifndef KEY_CHORD_ARRANGEMENT_H
#define KEY_CHORD_ARRANGEMENT_H

namespace notes
{
  extern int convert_to_note_value(int note, int mode, int starting_note);
  extern int** get_note_values_from_chords(int** chords, int mode, int starting_note);
}

namespace chord_gen
{
  extern int** one45_hqq(int mode, int starting_note);
  extern int** modify_chords(
    int** chord_arr,
    int mode,
    int starting_note,
    int new_mode,
    int new_starting_note
  );
  extern int** solid_three_chords(int mode, int starting_note);
}

namespace key_and_chord_arrangement
{
  // in key arrangement:
  // the first parameter is the mode, the second parameter is starting note.
  // this way the chord structure and modal structure are independent.
  // essentially the two parameters in key arrangement get passed into
  // the chord generator.
  int key_arrangement_standard_1 [7][2] = {
    {0,36},
    {0,36},
    {0,36},
    {0,36},
    {0,36},
    {0,36},
    {0,36}
  };
  int chord_arrangement_standard_1 [7] = {1,1,1,1,1,1,1};
  int key_arrangement_standard_2 [12][2] = {
    {0,36},
    {0,36},
    {0,36},
    {0,36},
    {0,36},
    {0,36},
    {0,36},
    {0,36},
    {0,36},
    {0,36},
    {0,36},
    {0,36}
  };
  int chord_arrangement_standard_2 [12] = {1,1,1,1,1,1,1,1,1,1,1,1};
  // int*** create_chords_from_arrangement(int* chord_arrangemnt, int** key_arrangement, int* section_lengths, int num_of_sections);
}

#endif
