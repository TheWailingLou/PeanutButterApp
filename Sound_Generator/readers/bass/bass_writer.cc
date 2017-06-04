#include "bass_writer.h"

namespace bass_writer
{
  void write_bass_bar(int** bass_teenth_array, int bar)
  {
    for (int i=0; i<16; i++)
    {
      int note = bass_teenth_array[i][0];
      int teenth_duration = bass_teenth_array[i][1];
      if (note != -1)
      {
        int teenth_as_frame = audio_helper::teenth_slice_as_frame(i);
        int bar_as_frame = audio_helper::bar_duration_in_frames() * bar;
        int frame_location = teenth_as_frame + bar_as_frame;
        int frame_duration = audio_helper::teenth_slice_as_frame(teenth_duration);
        // bass_voice::write_note_at_location(note, teenth_duration, i, bar);
        // bass_voice::super_square_at_location(note, frame_duration, frame_location);
        // bass_voice::triangle_at_location(note, frame_duration, frame_location);
        bass_voice::sine_at_location(note, frame_duration, frame_location);
      }
    }
  }
}
