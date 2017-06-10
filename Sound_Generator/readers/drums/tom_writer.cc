#include "tom_writer.h"

namespace tom_writer
{
  void write_from_array_at_bar(int teenth_array [16], int bar)
  {
    int bar_start_frame = audio_helper::bar_duration_in_frames() * bar;
    for (int location=0; location<16; location++)
    {
      int frame_location = audio_helper::teenth_slice_as_frame(location) + bar_start_frame;
      if (teenth_array[location] == 1)
      {
        int frame_location = audio_helper::teenth_slice_as_frame(location) + bar_start_frame;
        for (int channel=0; channel<drum_track::main_buffer_channels; channel++)
        {
          for (int i=0; i<drum_imports::tom_floor1_buffer_size; i++)
          {
            drum_track::other_drum_tracks[channel][i+frame_location] += drum_imports::tom_floor1_buffer[channel][i];
            // drum_track::tom_track[channel][i+frame_location] += drum_imports::tom_floor1_buffer[channel][i];
          }
        }
      } else if (teenth_array[location] == 2) {
        for (int channel=0; channel<drum_track::main_buffer_channels; channel++)
        {
          for (int i=0; i<drum_imports::tom_floor2_buffer_size; i++)
          {
            drum_track::other_drum_tracks[channel][i+frame_location] += drum_imports::tom_floor2_buffer[channel][i];
            // drum_track::tom_track[channel][i+frame_location] += drum_imports::tom_floor2_buffer[channel][i];
          }
        }
      } else if (teenth_array[location] == 3) {
        for (int channel=0; channel<drum_track::main_buffer_channels; channel++)
        {
          for (int i=0; i<drum_imports::tom_mid_buffer_size; i++)
          {
            drum_track::other_drum_tracks[channel][i+frame_location] += drum_imports::tom_mid_buffer[channel][i];
            // drum_track::tom_track[channel][i+frame_location] += drum_imports::tom_mid_buffer[channel][i];
          }
        }
      } else if (teenth_array[location] == 4) {
        for (int channel=0; channel<drum_track::main_buffer_channels; channel++)
        {
          for (int i=0; i<drum_imports::tom_mid_high_buffer_size; i++)
          {
            drum_track::other_drum_tracks[channel][i+frame_location] += drum_imports::tom_mid_high_buffer[channel][i];
            // drum_track::tom_track[channel][i+frame_location] += drum_imports::tom_mid_high_buffer[channel][i];
          }
        }
      } else if (teenth_array[location] == 5) {
        for (int channel=0; channel<drum_track::main_buffer_channels; channel++)
        {
          for (int i=0; i<drum_imports::tom_high_buffer_size; i++)
          {
            drum_track::other_drum_tracks[channel][i+frame_location] += drum_imports::tom_high_buffer[channel][i];
            // drum_track::tom_track[channel][i+frame_location] += drum_imports::tom_high_buffer[channel][i];
          }
        }
      }
    }
  }
}
