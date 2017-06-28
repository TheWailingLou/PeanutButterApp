#include "drum_track.h"

namespace drum_track
{

  void setup_buffers(int total_bars, double end_hang_time)
  {
    if (main_buffer_channels == 0)
    {
      main_buffer_channels = 2;
    }

    main_buffer_size = audio_helper::calculate_total_frames(total_bars, end_hang_time);

    main_buffer = new double* [main_buffer_channels];
    hi_hat_track = new double* [main_buffer_channels];
    other_drum_tracks = new double* [main_buffer_channels];

    for (int channel=0; channel<main_buffer_channels; channel++)
    {
      main_buffer[channel] = new double [main_buffer_size];
      hi_hat_track[channel] = new double [main_buffer_size];
      other_drum_tracks[channel] = new double [main_buffer_size];

      for (int i=0; i<main_buffer_size; i++)
      {
        main_buffer[channel][i] = 0;
        hi_hat_track[channel][i] = 0;
        other_drum_tracks[channel][i] = 0;
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

  void copy_to_track()
  {
    for (int channel=0; channel<main_buffer_channels; channel++)
    {
      std::cout << "getting to drum buffer" << std::endl;
      for (int i=0; i<main_buffer_size; i++)
      {
        main_buffer[channel][i] += hi_hat_track[channel][i];
        main_buffer[channel][i] += other_drum_tracks[channel][i];
      }
    }
  }

  void free_all_track_memory()
  {
    for (int i=0; i<main_buffer_channels; i++)
    {
      delete[] main_buffer[i];
      delete[] hi_hat_track[i];
      delete[] other_drum_tracks[i];

      main_buffer[i] = NULL;
      hi_hat_track[i] = NULL;
      other_drum_tracks[i] = NULL;
    }
    delete[] main_buffer;
    delete[] hi_hat_track;
    delete[] other_drum_tracks;

    main_buffer = NULL;
    hi_hat_track = NULL;
    other_drum_tracks = NULL;
  }
}
