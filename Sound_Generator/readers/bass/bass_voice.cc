#include "bass_voice.h"

namespace bass_voice
{
  void write_note_at_location(int note, int teenth_duration, int teenth_location, int bar)
  {
    double frequency = tones::convert_note_to_tone(note);
    int teenth_as_frame = audio_helper::teenth_slice_as_frame(teenth_location);
    int bar_as_frame = audio_helper::bar_duration_in_frames() * bar;
    int frame_location = teenth_as_frame + bar_as_frame;

    int frame_duration = audio_helper::teenth_slice_as_frame(teenth_duration);

    for (int channel=0; channel<bass_track::main_buffer_channels; channel++)
    {
      for (int i=0; i<frame_duration; i++)
      {
        double sin_x = ((M_PI*2)/((double)audio_setup::sample_rate)) * i * frequency;
        double sin_frame = sin(sin_x);
        bass_track::bass_track_1[channel][i+frame_location] += sin_frame;
      }
    }
  }
}
