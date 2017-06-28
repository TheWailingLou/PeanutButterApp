#include "bass_track.h"

namespace bass_track
{
  void setup_buffers(int total_bars, double end_hang_time)
  {
    main_buffer_channels = 2;

    main_buffer_size = audio_helper::calculate_total_frames(total_bars, end_hang_time);

    main_buffer = new double* [main_buffer_channels];
    bass_track_1 = new double* [main_buffer_channels];

    for (int channel=0; channel<main_buffer_channels; channel++)
    {
      main_buffer[channel] = new double [main_buffer_size];
      bass_track_1[channel] = new double [main_buffer_size];

      for (int i=0; i<main_buffer_size; i++)
      {
        main_buffer[channel][i] = 0;
        bass_track_1[channel][i] = 0;
      }
    }
  }

  void copy_to_track()
  {
    for (int channel=0; channel<main_buffer_channels; channel++)
    {
      for (int i=0; i<main_buffer_size; i++)
      {
        main_buffer[channel][i] += bass_track_1[channel][i];
      }
    }
  }

  void free_all_track_memory()
  {
    for (int i=0; i<main_buffer_channels; i++)
    {
      delete[] main_buffer[i];
      delete[] bass_track_1[i];
      main_buffer[i] = NULL;
      bass_track_1[i] = NULL;
    }

    delete[] main_buffer;
    delete[] bass_track_1;
    main_buffer = NULL;
    bass_track_1 = NULL;
  }
}
