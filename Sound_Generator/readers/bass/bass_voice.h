#ifndef BASS_VOICE
#define BASS_VOICE

#include <array>
#include <math.h>
// #include <cmath>
#include <stdlib.h>

namespace audio_setup
{
  extern int sample_rate;
}

namespace audio_helper
{
  extern int teenth_slice_as_frame(int beat);
  extern int bar_duration_in_frames();
  extern int calculate_total_frames(int total_bars, double end_hang_time=3);
  extern int calculate_total_frames(int total_bars);
}

namespace tones
{
  extern double convert_note_to_tone(int note);
}

namespace bass_track
{
  extern double** bass_track_1;
  extern double** bass_track_2;

  extern int main_buffer_size;
  extern int main_buffer_channels;
}

namespace bass_voice
{
  void write_note_at_location(
    int note,
    int teenth_duration,
    int teenth_location,
    int bar
  );
}

#endif
