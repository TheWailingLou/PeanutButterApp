#include "snare_writer.h"

namespace snare_writer
{
  void write_from_array_at_bar(int teenth_array [16], int bar)
  {
    int bar_start_frame = audio_helper::bar_duration_in_frames() * bar;
    for (int location=0; location<16; location++)
    {
      if (teenth_array[location] == 1)
      {
        int frame_location = audio_helper::teenth_slice_as_frame(location) + bar_start_frame;
        for (int channel=0; channel<drum_track::main_buffer_channels; channel++)
        {
          for (int i=0; i<drum_imports::snare_buffer_size; i++)
          {
            drum_track::snare_track[channel][i+frame_location] += drum_imports::snare_buffer[channel][i];
          }
        }
      }
    }
  }

}
