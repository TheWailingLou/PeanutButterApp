#include "bass_track.h"

namespace bass_track
{
  void setup_buffers(int total_bars, double end_hang_time)
  {

    main_buffer_channels = 2;


    main_buffer_size = audio_helper::calculate_total_frames(total_bars, end_hang_time);

    main_buffer = new double* [main_buffer_channels];
    bass_track_1 = new double* [main_buffer_channels];
    // bass_track_2 = new double* [main_buffer_channels];

    for (int channel=0; channel<main_buffer_channels; channel++)
    {
      main_buffer[channel] = new double [main_buffer_size];
      bass_track_1[channel] = new double [main_buffer_size];
      // bass_track_2[channel] = new double [main_buffer_size];

      for (int i=0; i<main_buffer_size; i++)
      {
        main_buffer[channel][i] = 0;
        bass_track_1[channel][i] = 0;
        // bass_track_2[channel][i] = 0;
      }
    }
  }

  void copy_to_track()
  {
    for (int channel=0; channel<main_buffer_channels; channel++)
    {
      std::cout << "copying to bass channels.." << std::endl;
      for (int i=0; i<main_buffer_size; i++)
      {
        main_buffer[channel][i] += bass_track_1[channel][i];
        // main_buffer[channel][i] += bass_track_2[channel][i];


        /////////////////////////////// DRUMS ::::
        //
        // main_buffer[channel][i] += drum_track::hi_hat_track[channel][i];
        // main_buffer[channel][i] += drum_track::tom_track[channel][i];
        // main_buffer[channel][i] += drum_track::kick_track[channel][i];
        // main_buffer[channel][i] += drum_track::snare_track[channel][i];
        // main_buffer[channel][i] += drum_track::crash_track[channel][i];
      }
    }
  }

  void free_all_track_memory()
  {
    for (int i=0; i<main_buffer_channels; i++)
    {
      delete[] main_buffer[i];
      delete[] bass_track_1[i];
      // delete[] bass_track_2[i];
      main_buffer[i] = NULL;
      bass_track_1[i] = NULL;
      // bass_track_2[i] = NULL;
    }
    delete[] main_buffer;
    delete[] bass_track_1;
    // delete[] bass_track_2;
    main_buffer = NULL;
    bass_track_1 = NULL;
    // bass_track_2 = NULL;
  }
}
