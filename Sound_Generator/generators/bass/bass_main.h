#ifndef BASS_MAIN_H
#define BASS_MAIN_H

#include <array>
#include <math.h>
#include <iostream>
#include <stdlib.h>

namespace notes
{
  extern int* get_single_octave(int starting_note, int mode, bool harmonic);
  extern int* get_all_notes(int starting_note, int mode, bool harmonic);
  extern int* get_octave_range(
    int octaves_below,
    int octaves_above,
    int starting_note,
    int mode,
    bool harmonic
  );
}

namespace bass_main
{
  int bass_line_test [16][2] = {
    {35, 1}, {37, 1}, {39, 1}, {35, 1},
    {35, 1}, {35, 1}, {35, 1}, {35, 1},
    {35, 1}, {35, 1}, {35, 1}, {35, 1},
    {35, 1}, {35, 1}, {35, 1}, {35, 1},
  };
  int** generate_test_teenth(int mode, int starting_note);
  int** generate_bass_bar(int mode, int starting_note);
}

#endif
