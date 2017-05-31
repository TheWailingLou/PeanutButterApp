#include "drum_track.h"

namespace drum_track
{

  void setup_buffers(int total_bars, double end_hang_time)
  {
    if (main_buffer_channels == 0)
    {
      main_buffer_channels = 2;
    }
    // if (main_buffer_size == 0 || total_bars != 0)
    // {
    main_buffer_size = audio_helper::calculate_total_frames(total_bars, end_hang_time);
    // }

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

  void create_tracks(int variations, int bars_per_variation)
  {
    int** hi_hat_arrays = new int* [variations];
    for (int variation=0; variation<variations; variation++)
    {
      hi_hat_arrays[variation] = hi_hat_generator::generate_hi_hat_teenth_array ();
    }
    for (int variation=0; variation<variations; variation++)
    {
      for (int bar=0; bar<bars_per_variation; bar++)
      {
        int actual_bar = bar + (variation*bars_per_variation);
        hi_hat_writer::write_from_array_at_bar(hi_hat_arrays[variation], actual_bar);
      }
    }
  }

  void test_creation()
  {
    setup_buffers(60, 3.0);
    srand(time(NULL));
    int** arrangement = new int* [5];
    for (int i=0; i<5; i++) {
      arrangement[i] = new int [12];
      for (int j=0; j<12; j++)
      {
        arrangement[i][j] = drum_arrangement::drum_arrangement_standard_2[i][j];
      }
    }
    drum_arrangement::create_tracks_from_arrangement(
      arrangement,
      arrangement_main::section_length_standard_2,
      12
    );
    for (int channel=0; channel<main_buffer_channels; channel++)
    {
      for (int i=0; i<main_buffer_size; i++)
      {
        main_buffer[channel][i] += hi_hat_track[channel][i];
        main_buffer[channel][i] += tom_track[channel][i];
        main_buffer[channel][i] += kick_track[channel][i];
        main_buffer[channel][i] += snare_track[channel][i];
        main_buffer[channel][i] += crash_track[channel][i];
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
