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
        // double sin_x = ((M_PI*2)/((double)audio_setup::sample_rate)) * i * frequency;
        // double sin_frame = sin(sin_x);
        // double sin_x2 = ((M_PI*2)/((double)audio_setup::sample_rate)) * i * (frequency+4);
        // double sin_frame2 = sin(sin_x2);
        //
        // double sin_x3 = ((M_PI*2)/((double)audio_setup::sample_rate)) * i * (frequency+8);
        // double sin_frame3 = sin(sin_x3);
        //
        // double sin_x4 = ((M_PI*2)/((double)audio_setup::sample_rate)) * i * (frequency+12);
        // double sin_frame4 = sin(sin_x4);

        // if (cos(sin_x) > 0) {
        //   // sin_frame = (4*i*frequency)/((double)audio_setup::sample_rate * M_PI);
        //   sin_frame = 1;
        //   sin_frame2 = 1;
        //   sin_frame3 = 1;
        //   sin_frame4 = 1;
        // } else {
        //   // sin_frame = (-4*i*frequency)/((double)audio_setup::sample_rate * M_PI);
        //   sin_frame = -1;
        //   sin_frame2 = -1;
        //   sin_frame3 = -1;
        //   sin_frame4 = -1;
        // }
        double morpher_square = 0;

        // int voices = 7;
        // for (int voice=0; voice<voices; voice++)
        // {
        //   double sin_x = ((M_PI*2)/((double)audio_setup::sample_rate)) * i * (frequency + (((double)voice)*(frequency*2/((double)voices)))/(frequency*2));
        //   double sin_frame = sin(sin_x);
        //   if (sin_frame > 0) {
        //     sin_frame = 1.0/((double)voices);
        //   } else {
        //     sin_frame = -1.0/((double)voices);
        //   }
        //   morpher_square += sin_frame;
        // }
        //

        double sin_x = ((M_PI*2)/((double)audio_setup::sample_rate)) * i * (frequency * 2);

        // int triangle = ((int)i)%((int)frequency);
        // if (sin(sin_x) > 0) {
        //   morpher_square = (4*((double)triangle))/((double)audio_setup::sample_rate * M_PI);
        // } else {
        //   morpher_square = (-4*((double)triangle))/((double)audio_setup::sample_rate * M_PI);
        // }

        ///// TRIANGLE :: // Fuck yeah!!
        int sr_f = (int)((double)audio_setup::sample_rate/(frequency*2));
        while (sr_f%4 != 0) {
          sr_f +=1;
        }
        int sr_f2 = sr_f/2;

        int sr_f4 = sr_f/4;
        double i_m_sr_f = (double)(i % sr_f);
        double i_m_sr_f2 = (double)(i % sr_f2);
        double i_m_sr_f4 = (double)(i % sr_f4);

        double triangle = 1 - (i_m_sr_f - (i_m_sr_f2 * ((i_m_sr_f- i_m_sr_f2)/sr_f4)))/((double)sr_f4);

        if (triangle > 1) {
          triangle = 1;
        } else if (triangle < -1) {
          triangle = -1;
        }



        morpher_square = triangle;




        // morpher_square = sin(sin_x);
        //
        // if (morpher_square > 0) {
        //   morpher_square = 1;
        // } else {
        //   morpher_square = -1;
        // }

        // double super_square = (sin_frame + sin_frame2 + sin_frame3 + sin_frame4)/4.0;
        bass_track::bass_track_1[channel][i+frame_location] += morpher_square * gain * 0.9;
        // bass_track::bass_track_1[channel][i+frame_location] += sin_frame * gain;
      }
    }
  }
}
