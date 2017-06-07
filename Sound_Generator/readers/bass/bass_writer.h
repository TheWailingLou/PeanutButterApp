#ifndef BASS_WRITER_H
#define BASS_WRITER_H

#include <array>
#include <math.h>
#include <stdlib.h>
#include <iostream>

namespace tones
{
  extern double convert_note_to_tone(int note);
}

namespace notes
{
  extern int find_lowest_note(int starting_note);
}

namespace audio_helper
{
  extern int time_as_frame(double time_in_seconds);
  extern int teenth_slice_as_frame(int beat);
  extern int bar_duration_in_frames();
  extern int calculate_total_frames(int total_bars, double end_hang_time=3);
  extern int calculate_total_frames(int total_bars);
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
  extern void write_note_at_location(
    int note,
    int teenth_duration,
    int teenth_location,
    int bar
  );
  extern void super_square_at_location(
    int note,
    int frame_duration,
    int frame_location
  );
  extern void triangle_at_location(int note, int frame_duration, int frame_location);
  extern void sine_at_location(int note, int frame_duration, int frame_location);
  extern void half_sine_at_location(int note, int frame_duration, int frame_location);
  extern void half_cos_at_location(int note, int frame_duration, int frame_location);
  extern void fourier_tone(int note, int frame_duration, int frame_location);
  extern void fourier_tone_2(int note, int frame_duration, int frame_location);
  extern void fourier_tone_3(int note, int frame_duration, int frame_location);

  extern void tone_play(int note, int frame_duration, int frame_location);
}

namespace bass_writer
{
  void write_bass_bar(int** bass_teenth_array, int bar);
  void final_note(int note, int duration, int octave, int bar);
}

#endif
