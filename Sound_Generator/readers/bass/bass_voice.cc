#include "bass_voice.h"

namespace bass_voice
{
  void write_note_at_location(int note, int teenth_duration, int teenth_location, int bar)
  {
    double frequency = tones::convert_note_to_tone(note);
    int teenth_as_frame = audio_helper::teenth_slice_as_frame(teenth_location);
    int bar_as_frame = audio_helper::bar_duration_in_frames() * bar;
    int frame_location = teenth_as_frame + bar_as_frame;
    int envelope_duration = audio_helper::time_as_frame(0.009);

    int frame_duration = audio_helper::teenth_slice_as_frame(teenth_duration);

    for (int channel=0; channel<bass_track::main_buffer_channels; channel++)
    {
      for (int i=0; i<frame_duration; i++)
      {
        double gain = 0.9;
        if (i<envelope_duration)
        {
          gain *= ((double)i) / ((double)envelope_duration);
        } else if (i > (frame_duration - envelope_duration)) {
          gain *= ((double)frame_duration-(double)i)/((double)envelope_duration);
        } else {
          gain = 0.9;
        }
        if (gain > 1.0)
        {
          std::cout << "gain! " << gain << std::endl;
          gain = 0.9;
        }
        double sin_x = ((M_PI*2)/((double)audio_setup::sample_rate)) * i * frequency;
        double sin_frame = sin(sin_x);
        double sin_x2 = ((M_PI*2)/((double)audio_setup::sample_rate)) * i * (frequency+4);
        double sin_frame2 = sin(sin_x2);

        double sin_x3 = ((M_PI*2)/((double)audio_setup::sample_rate)) * i * (frequency+8);
        double sin_frame3 = sin(sin_x3);

        double sin_x4 = ((M_PI*2)/((double)audio_setup::sample_rate)) * i * (frequency+12);
        double sin_frame4 = sin(sin_x4);

        if (sin_frame > 0) {
          sin_frame = 1;
          sin_frame2 = 1;
          sin_frame3 = 1;
          sin_frame4 = 1;
        } else {
          sin_frame = -1;
          sin_frame2 = -1;
          sin_frame3 = -1;
          sin_frame4 = -1;
        }
        double morpher_square = 0;
        int voices = 12 - (i%5);
        for (int voice=0; voice<voices; voice++)
        {
          double sin_x = ((M_PI*2)/((double)audio_setup::sample_rate)) * i * (frequency + (((double)voice)*(frequency*2/((double)voices)))/(frequency*2));
          double sin_frame = sin(sin_x);
          if (sin_frame > 0) {
            sin_frame = 1.0/((double)voices);
          } else {
            sin_frame = -1.0/((double)voices);
          }
          morpher_square += sin_frame;
        }

        // double super_square = (sin_frame + sin_frame2 + sin_frame3 + sin_frame4)/4.0;
        bass_track::bass_track_1[channel][i+frame_location] += morpher_square * gain;
      }
    }
  }
}
