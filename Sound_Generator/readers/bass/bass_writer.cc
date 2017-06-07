#include "bass_writer.h"

namespace bass_writer
{
  void write_bass_bar(int** bass_teenth_array, int bar)
  {
    std::cout << "in the bass bar";
    for (int i=0; i<16; i++)
    {
      int note = bass_teenth_array[i][0];
      int teenth_duration = bass_teenth_array[i][1];
      if (note != -1)
      {
        int teenth_as_frame = audio_helper::teenth_slice_as_frame(i);
        int bar_as_frame = audio_helper::bar_duration_in_frames() * bar;
        int frame_location = teenth_as_frame + bar_as_frame;
        int frame_duration = audio_helper::teenth_slice_as_frame(teenth_duration);
        // bass_voice::write_note_at_location(note, teenth_duration, i, bar);
        // bass_voice::super_square_at_location(note, frame_duration, frame_location);
        // bass_voice::triangle_at_location(note, frame_duration, frame_location);
        // bass_voice::sine_at_location(note, frame_duration, frame_location);
        // bass_voice::half_sine_at_location(note, frame_duration, frame_location);
        // bass_voice::half_cos_at_location(note, frame_duration, frame_location);
        bass_voice::fourier_tone(note, frame_duration, frame_location);
        // bass_voice::fourier_tone_2(note, frame_duration, frame_location);
        // bass_voice::fourier_tone_3(note, frame_duration, frame_location);

        // bass_voice::tone_play(note, frame_duration, frame_location);
      }
    }
    std::cout << "past the bass_bar" << std::endl;
  }

  void final_note(int note, int duration, int octave, int bar)
  {
    std::cout << "\nmaking into the final note" << std::endl;
    int lowest_of_note = notes::find_lowest_note(note);
    int actual_note = lowest_of_note + (octave*12);
    int frame_duration = audio_helper::teenth_slice_as_frame(duration);
    int frame_location = audio_helper::bar_duration_in_frames() * bar;

    std::cout << "\n\nGETTING ALL DATA. SENDING TO fourier_tone " << std::endl;


    // bass_voice::write_note_at_location(note, teenth_duration, i, bar);
    // bass_voice::super_square_at_location(note, frame_duration, frame_location);
    // bass_voice::triangle_at_location(note, frame_duration, frame_location);
    // bass_voice::sine_at_location(note, frame_duration, frame_location);
    // bass_voice::half_sine_at_location(note, frame_duration, frame_location);
    // bass_voice::half_cos_at_location(note, frame_duration, frame_location);
    bass_voice::fourier_tone(actual_note, frame_duration, frame_location);
    // bass_voice::fourier_tone_2(note, frame_duration, frame_location);
    // bass_voice::fourier_tone_3(note, frame_duration, frame_location);

    // bass_voice::tone_play(note, frame_duration, frame_location);
  }
}
