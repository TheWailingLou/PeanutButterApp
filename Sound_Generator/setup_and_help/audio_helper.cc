#include "audio_helper.h"

namespace audio_helper
{
  int time_as_frame(double time_in_seconds)
  {
    double sr = (double) audio_setup::sample_rate;
    return (int) floor(sr * time_in_seconds);
  }

  int beat_as_frame(int beat)
  {
    double fraction_of_frame = ((double)audio_setup::sample_rate * (60.0/ (double) audio_setup::tempo));
    int beat_duration_in_frames = (int) fraction_of_frame;
    return beat_duration_in_frames * beat;
  }

  int teenth_slice_as_frame(int beat)
  {
    double fraction_of_frame = ((double)audio_setup::sample_rate * (60.0/ ((double)audio_setup::tempo * 4.0)));
    int teenth_duration_in_frames = (int) fraction_of_frame;
    return teenth_duration_in_frames * beat;
  }

  int bar_duration_in_frames()
  {
    return beat_as_frame(4);
  }

  int calculate_total_frames(int total_bars, double end_hang_time)
  {
    int bar_duration = total_bars * bar_duration_in_frames();
    int end_hang_in_frames = time_as_frame(end_hang_time);
    return bar_duration + end_hang_in_frames;
  }
  int calculate_total_frames(int total_bars)
  {
    double end_hang_time = 3.0;
    int bar_duration = total_bars * bar_duration_in_frames();
    int end_hang_in_frames = time_as_frame(end_hang_time);
    return bar_duration + end_hang_in_frames;
  }
}
