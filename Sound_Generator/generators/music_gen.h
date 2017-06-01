#ifndef MUSIC_GEN_H
#define MUSIC_GEN_H

#include <stdlib.h>
#include <array>
#include <iostream>

namespace music_gen
{
  int** generate_bar_from_chords(int** chords, int octave);
}

#endif
