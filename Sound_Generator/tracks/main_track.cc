#include "main_track.h"

namespace main_track
{
  void setup_buffers(int total_bars, double end_hang_time)
  {
    main_buffer_channels = 2;

    main_buffer_size = audio_helper::calculate_total_frames(total_bars, end_hang_time);

    main_buffer = new double* [main_buffer_channels];

    for (int channel=0; channel<main_buffer_channels; channel++)
    {
      main_buffer[channel] = new double [main_buffer_size];

      for (int i=0; i<main_buffer_size; i++)
      {
        main_buffer[channel][i] = 0;
      }
    }
  }
  void test_creation()
  {
    srand(time(NULL));
    int* section_lengths = arrangement_all::get_section_lengths();
    int total_bars = section_lengths[4];
    bass_track::setup_buffers(total_bars, 5.0);
    drum_track::setup_buffers(total_bars, 5.0);
    setup_buffers(total_bars, 5.0);
    arrangement_all::create_tracks(audio_setup::key, audio_setup::mode, section_lengths);

    bass_track::copy_to_track();
    drum_track::copy_to_track();

    for (int channel=0; channel<main_buffer_channels; channel++)
    {
      for (int i=0; i<main_buffer_size; i++)
      {
        main_buffer[channel][i] += bass_track::main_buffer[channel][i];
        main_buffer[channel][i] += drum_track::main_buffer[channel][i];
      }
    }
  }

  void free_all_track_memory()
  {
    for (int i=0; i<main_buffer_channels; i++)
    {
      delete[] main_buffer[i];
      main_buffer[i] = NULL;
    }
    delete[] main_buffer;
    main_buffer = NULL;
  }
}
