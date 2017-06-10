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



        // int triangle = ((int)i)%((int)frequency);
        // if (sin(sin_x) > 0) {
        //   morpher_square = (4*((double)triangle))/((double)audio_setup::sample_rate * M_PI);
        // } else {
        //   morpher_square = (-4*((double)triangle))/((double)audio_setup::sample_rate * M_PI);
        // }

        ///// TRIANGLE :: // Fuck yeah!!

        int voices = 1;

        double morphed_triangle = 0;

        for (int voice=0; voice<voices; voice++)
        {
          double frequency_detune = (12) - (2*12*(((double)voice+1)/(double)voices));

          int sr_f = (int)((double)audio_setup::sample_rate/(frequency*2 + frequency_detune));

          while (sr_f%4 != 0) {
            sr_f +=1;
          }
          int sr_f2 = sr_f/2;

          int sr_f4 = sr_f/4;
          double i_m_sr_f = (double)(i % sr_f);
          double i_m_sr_f2 = (double)(i % sr_f2);

          double triangle = 1 - (i_m_sr_f - (i_m_sr_f2 * ((i_m_sr_f- i_m_sr_f2)/sr_f4)))/((double)sr_f4);
          morphed_triangle += triangle/(double)voices;
        }

        //
        // if (triangle > 1) {
        //   triangle = 1;
        // } else if (triangle < -1) {
        //   triangle = -1;
        // }





        // double sin_x = ((M_PI*2)/((double)audio_setup::sample_rate)) * i * (frequency * 2);
        // double sine = sin(sin_x);
        // double square = 0;
        // //
        // if (sine > 0) {
        //   square = 1;
        // } else {
        //   square = -1;
        // }

        morpher_square = morphed_triangle;

        // double
        // if (i%3 == 0)
        // {
        //   morpher_square = square;
        // } else if (i%3 == 1) {
        //   morpher_square = (square + sine)/2.0; //+ square
        // } else {
        //   morpher_square = sine;
        // }


        // double super_square = (sin_frame + sin_frame2 + sin_frame3 + sin_frame4)/4.0;
        bass_track::bass_track_1[channel][i+frame_location] += morpher_square * gain * 0.9;
        // bass_track::bass_track_1[channel][i+frame_location] += sin_frame * gain;
      }
    }
  }
  // attack and decay are in frames;
  double envelope_gain(int i, int attack, int decay, int frame_duration)
  {
    double gain = 0.9;
    if (i<attack)
    {
      gain *= ((double)i) / ((double)attack);
    } else if (i > (frame_duration - decay)) {
      gain *= ((double)frame_duration-(double)i)/((double)decay);
    } else {
      gain = 0.9;
    }
    return gain;
  }

  void super_square_at_location(int note, int frame_duration, int frame_location)
  {
    double frequency = tones::convert_note_to_tone(note);
    int attack = audio_helper::time_as_frame(0.009);
    int decay = audio_helper::time_as_frame(0.008);
    for (int channel=0; channel<bass_track::main_buffer_channels; channel++)
    {
      for (int i=0; i<frame_duration; i++)
      {
        double gain = envelope_gain(i, attack, decay, frame_duration);
        double morpher_square = 0;
        int voices = 7;
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
        bass_track::bass_track_1[channel][i+frame_location] += morpher_square * gain * 0.9;
      }
    }
  }

  void triangle_at_location(int note, int frame_duration, int frame_location)
  {
    double frequency = tones::convert_note_to_tone(note);
    int attack = audio_helper::time_as_frame(0.009);
    int decay = audio_helper::time_as_frame(0.008);
    for (int channel=0; channel<bass_track::main_buffer_channels; channel++)
    {
      for (int i=0; i<frame_duration; i++)
      {
        double gain = envelope_gain(i, attack, decay, frame_duration);
        int sr_f = (int)((double)audio_setup::sample_rate/(frequency*2));
        while (sr_f%4 != 0) {
          sr_f +=1;
        }
        int sr_f2 = sr_f/2;
        int sr_f4 = sr_f/4;
        double i_m_sr_f = (double)(i % sr_f);
        double i_m_sr_f2 = (double)(i % sr_f2);
        double triangle = 1 - (i_m_sr_f - (i_m_sr_f2 * ((i_m_sr_f - i_m_sr_f2)/sr_f4)))/((double)sr_f4);
        bass_track::bass_track_1[channel][i+frame_location] += triangle * gain * 0.9;
      }
    }
  }
  void sine_at_location(int note, int frame_duration, int frame_location)
  {
    double frequency = tones::convert_note_to_tone(note);
    int attack = audio_helper::time_as_frame(0.009);
    int decay = audio_helper::time_as_frame(0.008);
    for (int channel=0; channel<bass_track::main_buffer_channels; channel++)
    {
      for (int i=0; i<frame_duration; i++)
      {
        double gain = envelope_gain(i, attack, decay, frame_duration);
        double sin_x = ((M_PI*2)/((double)audio_setup::sample_rate)) * i * (frequency*2);
        double sine = sin(sin_x);
        bass_track::bass_track_1[channel][i+frame_location] += sine * gain * 0.9;
      }
    }
  }

  void half_sine_at_location(int note, int frame_duration, int frame_location)
  {
    double frequency = tones::convert_note_to_tone(note);
    int attack = audio_helper::time_as_frame(0.009);
    int decay = audio_helper::time_as_frame(0.008);
    for (int channel=0; channel<bass_track::main_buffer_channels; channel++)
    {
      for (int i=0; i<frame_duration; i++)
      {
        double gain = envelope_gain(i, attack, decay, frame_duration);
        double sr_f = (double)audio_setup::sample_rate/(frequency*2.0);
        double modulo = i % (int)sr_f;
        double sin_x = M_PI * ((double)modulo/sr_f);
        double half_sine = (2*sin(sin_x))-1;
        bass_track::bass_track_1[channel][i+frame_location] += half_sine * gain * 0.9;
      }
    }
  }

  void half_cos_at_location(int note, int frame_duration, int frame_location)
  {
    double frequency = tones::convert_note_to_tone(note);
    int attack = audio_helper::time_as_frame(0.009);
    int decay = audio_helper::time_as_frame(0.008);
    for (int channel=0; channel<bass_track::main_buffer_channels; channel++)
    {
      for (int i=0; i<frame_duration; i++)
      {
        double gain = envelope_gain(i, attack, decay, frame_duration);
        double sr_f = (double)audio_setup::sample_rate/(frequency*2.0);
        double modulo = i % (int)sr_f;
        double sin_x = M_PI * ((double)modulo/sr_f);
        double half_cos = cos(sin_x);
        bass_track::bass_track_1[channel][i+frame_location] += half_cos * gain * 0.9;
      }
    }
  }

  void fourier_tone(int note, int frame_duration, int frame_location)
  {
    double frequency = tones::convert_note_to_tone(note);
    int attack = audio_helper::time_as_frame(0.009);
    int decay = audio_helper::time_as_frame(0.02);
    for (int channel=0; channel<bass_track::main_buffer_channels; channel++)
    {
      for (int i=0; i<frame_duration; i++)
      {
        double gain = envelope_gain(i, attack, decay, frame_duration);

        double f_sin_x = ((M_PI*2)/((double)audio_setup::sample_rate)) * i * (frequency*2);
        double f_sin_x2 = ((M_PI*2)/((double)audio_setup::sample_rate)) * i * (frequency);
        double sine = sin(f_sin_x);
        double sine2 = sin(f_sin_x2);

        double sr = (double)audio_setup::sample_rate;

        double gain_redux = 1;
        double all_comps = 0.0;
        int n = 20;
        for (int j=1; j<(n+1); j++)
        {

          double fnt = (M_PI*2*i*j*frequency)/sr;
          double an = (n-j)*sin(j/M_PI);
          double bn = 0.1 + (((double)(rand()%500))/1000.0);//sin((j*2*(M_PI*2))/n);
          double sine_part = an*sin(fnt);
          double cos_part = bn*cos(fnt);
          gain_redux += abs(an) + abs(bn);
          double comp = (sine_part + cos_part);
          all_comps += comp;
        }
        if (gain_redux < 1)
        {
          gain_redux = 1;
        }
        double piano_attempt = (all_comps)/gain_redux;
        piano_attempt = (piano_attempt + sine + sine2)/3;

        bass_track::bass_track_1[channel][i+frame_location] += piano_attempt * gain * 1.0;
      }
    }
  }
  void fourier_tone_2(int note, int frame_duration, int frame_location)
  {
    double frequency = tones::convert_note_to_tone(note);
    int attack = audio_helper::time_as_frame(0.009);
    int decay = audio_helper::time_as_frame(0.02);
    for (int channel=0; channel<bass_track::main_buffer_channels; channel++)
    {
      for (int i=0; i<frame_duration; i++)
      {
        double gain = envelope_gain(i, attack, decay, frame_duration);

        double f_sin_x = ((M_PI*2)/((double)audio_setup::sample_rate)) * i * (frequency*2);
        double f_sin_x2 = ((M_PI*2)/((double)audio_setup::sample_rate)) * i * (frequency*1);
        double sine = sin(f_sin_x);
        double sine2 = sin(f_sin_x2);

        double sr = (double)audio_setup::sample_rate;

        double gain_redux = 1;
        double all_comps = 0.0;
        int n = 20;
        for (int j=1; j<(n+1); j++)
        {
          double fnt = (M_PI*2*i*j*frequency)/sr;
          double an = ((j*M_PI)-n)*sin(j/(M_PI*2));
          double bn = 0.1 + (((double)(rand()%500))/1000.0);//sin((j*2*(M_PI*2))/n);
          double sine_part = an*sin(fnt);
          double cos_part = bn*cos(fnt);
          gain_redux += abs(an) + abs(bn);
          double comp = (sine_part + cos_part);
          all_comps += comp;
        }
        if (gain_redux < 1)
        {
          gain_redux = 1;
        }
        double piano_attempt = (all_comps)/gain_redux;
        piano_attempt = (piano_attempt + sine + sine2)/3;

        bass_track::bass_track_1[channel][i+frame_location] += piano_attempt * gain * 0.9;


      }
    }
  }

  void fourier_tone_3(int note, int frame_duration, int frame_location)
  {
    double frequency = tones::convert_note_to_tone(note);
    int attack = audio_helper::time_as_frame(0.009);
    int decay = audio_helper::time_as_frame(0.02);
    for (int channel=0; channel<bass_track::main_buffer_channels; channel++)
    {
      for (int i=0; i<frame_duration; i++)
      {
        double gain = envelope_gain(i, attack, decay, frame_duration);

        double sr_f_sin = (double)audio_setup::sample_rate/(frequency*1.0);
        double modulo = i % (int)sr_f_sin;
        double h_sin_x = M_PI * ((double)modulo/sr_f_sin);
        double half_sin = (2*sin(h_sin_x))-1;

        double f_sin_x = ((M_PI*2)/((double)audio_setup::sample_rate)) * i * (frequency*2);
        double f_sin_x2 = ((M_PI*2)/((double)audio_setup::sample_rate)) * i * (frequency*4);
        double sine = sin(f_sin_x);
        double sine2 = sin(f_sin_x2);

        double sr = (double)audio_setup::sample_rate;

        double gain_redux = 1;
        double all_comps = 0.0;
        int n = 4;
        for (int j=1; j<(n+1); j++)
        {
          double mod = (double)(j % (int)n);
          double half_sine_a = M_PI * ((double)modulo/n);

          double fnt = (M_PI*2*i*j*frequency)/sr;
          double an = 5*((n-j)/n);
          double bn = .1*(cos(j/(M_PI*2)));//sin((j*2*(M_PI*2))/n);
          double sine_part = an*sin(fnt);
          double cos_part = bn*cos(fnt);
          gain_redux += abs(an) + abs(bn);
          double comp = (sine_part + cos_part);
          all_comps += comp;
        }
        if (gain_redux < 1)
        {
          gain_redux = 1;
        }
        double piano_attempt = (all_comps)/gain_redux;
        piano_attempt = ((2*piano_attempt) + half_sin + (sine*2) + sine2)/6.0;

        bass_track::bass_track_1[channel][i+frame_location] += piano_attempt * gain * 0.9;


      }
    }
  }

  void tone_play(int note, int frame_duration, int frame_location)
  {
    double frequency = tones::convert_note_to_tone(note);
    int attack = audio_helper::time_as_frame(0.009);
    int decay = audio_helper::time_as_frame(0.02);
    for (int channel=0; channel<bass_track::main_buffer_channels; channel++)
    {
      for (int i=0; i<frame_duration; i++)
      {
        double gain = envelope_gain(i, attack, decay, frame_duration);

        int sr_f = (int)((double)audio_setup::sample_rate/(frequency*4.0));
        while (sr_f%4 != 0) {
          sr_f +=1;
        }
        int sr_f2 = sr_f/2;
        int sr_f4 = sr_f/4;
        double i_m_sr_f = (double)(i % sr_f);
        double i_m_sr_f2 = (double)(i % sr_f2);
        double triangle = 1 - (i_m_sr_f - (i_m_sr_f2 * ((i_m_sr_f - i_m_sr_f2)/sr_f4)))/((double)sr_f4);



        double sr_f_sin = (double)audio_setup::sample_rate/(frequency*1.0);
        double sr_f_cos = (double)audio_setup::sample_rate/(frequency*1.0);
        double modulo = i % (int)sr_f_sin;
        double h_sin_x = M_PI * ((double)modulo/sr_f_sin);
        double h_cos_x = M_PI * ((double)modulo/sr_f_cos);

        double f_sin_x = ((M_PI*2)/((double)audio_setup::sample_rate)) * i * (frequency*2);
        double f_sin_x2 = ((M_PI*2)/((double)audio_setup::sample_rate)) * i * (frequency*4);
        double sine = sin(f_sin_x);
        double sine2 = sin(f_sin_x2);
        double square_sin = sin(f_sin_x);
        double square = 0;
        if (square_sin > 0)
        {
          square = 1;
        } else {
          square = -1;
        }

        double half_cos = cos(h_cos_x);
        double half_sin = (2*sin(h_sin_x))-1;

        double sr = (double)audio_setup::sample_rate;

        // double fifth = pow(2, (7.0/12.0));
        // double fourth = pow(2, (5.0/12.0));



        // double main = -189*cos((M_PI*2*i*frequency*2)/sr) + 113*sin((M_PI*2*i*frequency*2)/sr);
        // double comp2 = 782*cos((M_PI*2*2*i*frequency*2)/sr) - 1427*sin((M_PI*2*2*i*frequency*2)/sr);
        // double comp3 = -536*cos((M_PI*2*3*i*frequency*2)/sr) + 8*sin((M_PI*2*3*i*frequency*2)/sr);
        // double comp4 = -37*cos((M_PI*2*4*i*frequency*2)/sr) - 76*sin((M_PI*2*4*i*frequency*2)/sr);
        //
        // double amp_redux =189+113+782+1427+536+8+37+76;
        // double comp6 = cos((M_PI*2*5*i*frequency*2)/sr) + sin((M_PI*2*5*i*frequency*2)/sr);
        // double comp7 = cos((M_PI*2*6*i*frequency*2)/sr) + sin((M_PI*2*6*i*frequency*2)/sr);
        // double comp8 = cos((M_PI*2*7*i*frequency*2)/sr) + sin((M_PI*2*7*i*frequency*2)/sr);
        // double comp9 = cos((M_PI*2*8*i*frequency*2)/sr) + sin((M_PI*2*8*i*frequency*2)/sr);

        int harmonics = 12;
        double gain_redux = 1;
        double all_comps = 0.0;
        int n = 4;
        for (int j=1; j<(n+1); j++)
        {
          double mod = (double)(j % (int)n);
          double half_sine_a = M_PI * ((double)modulo/n);

          double fnt = (M_PI*2*i*j*frequency)/sr;
          double an = 5*((n-j)/n);
          double bn = .1*(cos(j/(M_PI*2)));//sin((j*2*(M_PI*2))/n);
          double sine_part = an*sin(fnt);
          double cos_part = bn*cos(fnt);
          gain_redux += abs(an) + abs(bn);
          double comp = (sine_part + cos_part);
          all_comps += comp;
        }
        if (gain_redux < 1)
        {
          gain_redux = 1;
        }
        double piano_attempt = (all_comps)/gain_redux;
        piano_attempt = ((3*piano_attempt) + half_sin + (sine*2) + sine2)/7.0;

        double new_tone = (square + triangle)/2.0;
        bass_track::bass_track_1[channel][i+frame_location] += piano_attempt * gain * 0.9;


      }
    }
  }
}
