#ifndef BASS_MAIN_H
#define BASS_MAIN_H

#include <array>
#include <iostream>
#include <stdlib.h>

namespace notes
{
  int* get_single_octave(int starting_note, int mode, bool harmonic);
  int* get_all_notes(int starting_note, int mode, bool harmonic);
}

namespace bass_main
{
  int bass_line_test [16][2] = {
    {35, 1}, {35, 1}, {35, 1}, {35, 1},
    {35, 1}, {35, 1}, {35, 1}, {35, 1},
    {35, 1}, {35, 1}, {35, 1}, {35, 1},
    {35, 1}, {35, 1}, {35, 1}, {35, 1},
  };

}

#endif
