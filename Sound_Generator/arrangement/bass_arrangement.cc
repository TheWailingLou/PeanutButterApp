#include "bass_arrangement.h"

namespace bass_arrangement
{
  int num_of_unique_sections(int* arrangement, int total_sections)
  {
    int unique_sections = 0;
    for (int section=0; section<total_sections; section++)
    {
      int section_num = arrangement[section];
      if (section_num > unique_sections) {
        unique_sections = section_num;
      }
    }
    return unique_sections;
  }

  void create_tracks_from_arrangement_and_chords(int** key_arrangement, int* chord_arrangemnt, int* bass_arrangement, int* section_length, int total_sections, int*** drum_arrangement)
  {
    int** used_chords = new int* [total_sections];
    int** used_riffs = new int* [total_sections];
    for (int i=0; i<total_sections; i++)
    {
      used_chords[i] = new int [3];
      used_riffs[i] = new int [3];
      used_chords[i][0] = -1;
      used_riffs[i][0] = -1;
      used_chords[i][1] = -1;
      used_riffs[i][1] = -1;
      used_chords[i][2] = -1;
      used_riffs[i][2] = -1;
    }
    std::cout << "made it past for 1" << std::endl;

    int*** all_riffs = new int** [total_sections];
    int*** all_chords = new int** [total_sections];
    int*** all_riffs_to_write = new int** [total_sections];
    // int*** all_chords_to_write = new int** [total_sections];

    for (int section=0; section<total_sections; section++)
    {
      int start_note = key_arrangement[section][1];
      int mode = key_arrangement[section][0];
      // int* scale = notes::get_single_octave()
      int current_chord = chord_arrangemnt[section];
      int current_riff = bass_arrangement[section];
      int** chord_bar;
      int** riff_bar;

      int* kick = drum_arrangement[0][section];
      int* snare = drum_arrangement[1][section];
      int* hi_hat = drum_arrangement[2][section];

      std::cout << "iterating through sections.." << current_chord << std::endl;

      if (used_chords[current_chord-1][0] != -1)
      {
        std::cout << "1" << std::endl;
        chord_bar = chord_gen::modify_chords(
          all_chords[current_chord-1],
          used_chords[current_chord-1][1],
          used_chords[current_chord-1][2],
          mode,
          start_note
        );
        if (used_riffs[current_riff-1][0] != -1)
        {
          std::cout << "2" << std::endl;
          // riff_bar = all_riffs[current_riff-1];
          riff_bar = music_gen::modify_bar_to_new_mode_or_key(
            all_riffs[current_riff-1],
            used_riffs[current_riff-1][1],
            used_riffs[current_riff-1][2],
            mode,
            start_note,
            1
          );
        } else {
          std::cout << "3" << std::endl;
          // riff_bar = music_gen::generate_bar_from_chords(chord_bar, 1);
          riff_bar = music_gen::generate_bar_from_chords_and_drums(
            kick, snare, hi_hat,
            chord_bar, 1
          );
          all_riffs[current_riff-1] = riff_bar;
          used_riffs[current_riff-1][0] = current_riff;
          used_riffs[current_riff-1][1] = mode;
          used_riffs[current_riff-1][2] = start_note;
        }
      } else {
        std::cout << "4" << std::endl;
        // chord_bar = chord_gen::solid_three_chords(mode, start_note);
        chord_bar = chord_gen::chords_from_kick(
          drum_arrangement[0][section],
          mode,
          start_note
        );
        all_chords[current_chord-1] = chord_bar;
        used_chords[current_chord-1][0] = current_chord;
        used_chords[current_chord-1][1] = mode;
        used_chords[current_chord-1][2] = start_note;
        if (used_riffs[current_riff-1][0] != -1)
        {
          std::cout << "5" << std::endl;
          // riff_bar = all_riffs[current_riff-1];
          riff_bar = music_gen::modify_bar_to_new_mode_or_key(
            all_riffs[current_riff-1],
            used_riffs[current_riff-1][1],
            used_riffs[current_riff-1][2],
            mode,
            start_note,
            1
          );
        } else {
          std::cout << "6" << std::endl;
          // riff_bar = music_gen::generate_bar_from_chords(chord_bar, 1);
          riff_bar = music_gen::generate_bar_from_chords_and_drums(
            kick, snare, hi_hat,
            chord_bar, 1
          );
          all_riffs[current_riff-1] = riff_bar;
          used_riffs[current_riff-1][0] = current_riff;
          used_riffs[current_riff-1][1] = mode;
          used_riffs[current_riff-1][2] = start_note;
        }
      }

      std::cout << "7" << std::endl;
      // if (current_mode == -1 && current_starting_note == -1)
      // {

      // there is a bad conversion happening somewhere.
      // It's giving it the wrong scale, and so it's getting very confused.
      // I'm guessing it has to do with this vvvv;

      all_riffs_to_write[section] = riff_bar;
      // all_chords_to_write[section] = chord_bar;




      std::cout << "Mode " << mode << " current_riff-1 :" << current_riff-1;
      std::cout << "\nshouldEqualMode: " << used_riffs[current_riff-1][1] << std::endl;
    }

    std::cout << "\n\nmade it through loop 2.." << std::endl;

    int current_bar = 0;
    for (int section=0; section<total_sections; section++)
    {
      int* fill = drum_arrangement[3][section];
      for (int bar=0; bar<section_length[section]; bar++)
      {
        int** bass_bar;
        if (bar < section_length[section]-1)
        {
          bass_bar = all_riffs_to_write[section];
        } else {
          bass_bar = music_gen::modify_bar_for_fill(all_riffs_to_write[section], fill);
        }
        bass_writer::write_bass_bar(bass_bar, current_bar);
        current_bar += 1;
      }
    }


    for (int i=0; i<16; i++)
    {
      delete[] all_riffs[0][i];
      delete[] all_chords[0][i];
    }

    // delete[] all_riffs[0];
    // delete[] all_chords[0];
    // delete[] used_riffs[0];
    // delete[] used_chords[0];
    //
    // delete[] all_riffs;
    // delete[] all_chords;
    // delete[] used_chords;
    // delete[] used_riffs;
  }
}
