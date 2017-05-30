#include "drum_track.h"

namespace drum_track
{
  using namespace drum_imports;

  void setup_buffers(int total_bars, double end_hang_time)
  {
    if (main_buffer_channels == 0)
    {
      main_buffer_channels = 2;
    }
    if (main_buffer_size == 0 || total_bars != 0)
    {
      main_buffer_size = audio_helper::calculate_total_frames(total_bars, end_hang_time);
    }

    main_buffer = new double* [main_buffer_channels];
    hi_hat_track = new double* [main_buffer_channels];
    crash_track = new double* [main_buffer_channels];
    kick_track = new double* [main_buffer_channels];
    ride_track = new double* [main_buffer_channels];
    snare_track = new double* [main_buffer_channels];
    tom_track = new double* [main_buffer_channels];

    for (int channel=0; channel<main_buffer_channels; channel++)
    {
      main_buffer[channel] = new double [main_buffer_size];
      hi_hat_track[channel] = new double [main_buffer_size];
      crash_track[channel] = new double [main_buffer_size];
      kick_track[channel] = new double [main_buffer_size];
      ride_track[channel] = new double [main_buffer_size];
      snare_track[channel] = new double [main_buffer_size];
      tom_track[channel] = new double [main_buffer_size];

      for (int i=0; i<main_buffer_size; i++)
      {
        main_buffer[channel][i] = 0;
        hi_hat_track[channel][i] = 0;
        crash_track[channel][i] = 0;
        kick_track[channel][i] = 0;
        ride_track[channel][i] = 0;
        snare_track[channel][i] = 0;
        tom_track[channel][i] = 0;
      }
    }
  }

  // void overlay_drum_at_time(double** drum_buffer, int drum_size, double time_in_seconds)
  // {
  //   int time_as_frame = audio_helper::time_as_frame(time_in_seconds);
  //
  //   for (int channel=0; channel<main_buffer_channels; channel++)
  //   {
  //     for (int i=0; i<drum_size; i++)
  //     {
  //       main_buffer[channel][i+time_as_frame] += drum_buffer[channel][i];
  //     }
  //   }
  // }

  void test_creation()
  {
    setup_buffers(16, 3.0);
    srand(time(NULL));
    int* hi_hat_array = hi_hat_generator::generate_hi_hat_teenth_array();
    hi_hat_writer::write_from_array_at_bar(hi_hat_array);

    for (int channel=0; channel<main_buffer_channels; channel++)
    {
      for (int i=0; i<main_buffer_size; i++)
      {
        main_buffer[channel][i] = hi_hat_track[channel][i];
      }
    }

    // for (int section=0; section<4; section++)
    // {
    //   int* hi_hat_array = hi_hat_generator::generate_hi_hat_teenth_array();
    //   int* kick_array = kick_generator::get_random_kick_standard();
    //   int* snare_array = snare_generator::get_random_snare_standard();
    //   if (section%2 == 0)
    //   {
    //     if (section != 0)
    //     {
    //       add_crash_to_track_at_beat_or_bar(crash1_buffer, crash1_buffer_size, main_buffer, 0, section * 4);
    //     }
    //   } else {
    //     add_crash_to_track_at_beat_or_bar(crash2_buffer, crash2_buffer_size, main_buffer, 0, section * 4);
    //   }
    //   for (int bars=0; bars<4; bars++)
    //   {
    //     if (bars % 4 == 3)
    //     {
    //       int* silence_array = new int [16];
    //       for (int j=0; j<16; j++) {
    //         if (j>8)
    //         {
    //           silence_array[j] = 1;
    //         } else {
    //           silence_array[j] = 0;
    //         }
    //       }
    //       remove_hits_from_teenth_array_via_array(silence_array, hi_hat_array);
    //       remove_hits_from_teenth_array_via_array(silence_array, kick_array);
    //       remove_hits_from_teenth_array_via_array(silence_array, snare_array);
    //     }
    //     int bar = bars + (section*4);
    //     // std::cout << bar << std::endl;
    //     add_drum_to_track_from_teenth_array_at_bar(hi_hat_closed_buffer, hi_hat_closed_buffer_size, main_buffer, hi_hat_array, bar);
    //     add_drum_to_track_from_teenth_array_at_bar(kick_buffer, kick_buffer_size, main_buffer, kick_array, bar);
    //     add_drum_to_track_from_teenth_array_at_bar(snare_buffer, snare_buffer_size, main_buffer, snare_array, bar);
    //   }

      // delete[] hi_hat_array;
      // delete[] kick_array;
      // delete[] snare_array;
    }
  }

  // void add_drum_to_track_from_teenth_array_at_bar(double** drum, int drum_size, double** track, int teenth_array [16], int bar)
  // {
  //   int bar_start_frame = audio_helper::bar_duration_in_frames() * bar;
  //   for (int location=0; location<16; location++)
  //   {
  //     if (teenth_array[location] != 0 && teenth_array[location] == 1)
  //     {
  //       int frame_location = audio_helper::teenth_slice_as_frame(location) + bar_start_frame;
  //       for (int channel=0; channel<main_buffer_channels; channel++)
  //       {
  //         for (int i=0; i<drum_size; i++)
  //         {
  //           track[channel][i+frame_location] += drum[channel][i];
  //         }
  //       }
  //     }
  //   }
  // }

  void add_crash_to_track_at_beat_or_bar(double** crash, int crash_size, double** track, int beat, int bar)
  {
    int bar_frame_length = audio_helper::bar_duration_in_frames() * bar;
    int beat_frame_length = audio_helper::beat_as_frame(beat);
    int frame_location = bar_frame_length + beat_frame_length;
    for (int channel=0; channel<main_buffer_channels; channel++)
    {
      for (int i=0; i<crash_size; i++)
      {
        track[channel][i+frame_location] += crash[channel][i];
      }
    }
  }

  void remove_hits_from_teenth_array_via_array(int silence_array [16], int* teenth_array)
  {
    for (int i=0; i<16; i++)
    {
      if (silence_array[i] == 1)
      {
        teenth_array[i] = 0;
      }
    }
  }



  void free_all_track_memory()
  {
    for (int i=0; i<main_buffer_channels; i++)
    {
      delete[] main_buffer[i];
      delete[] hi_hat_track[i];
      delete[] crash_track[i];
      delete[] kick_track[i];
      delete[] ride_track[i];
      delete[] snare_track[i];
      delete[] tom_track[i];
    }
    delete[] main_buffer;
    delete[] hi_hat_track;
    delete[] crash_track;
    delete[] kick_track;
    delete[] ride_track;
    delete[] snare_track;
    delete[] tom_track;
  }
}
