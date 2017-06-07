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

  bool bar_contains_drums(int* kick, int* snare, int* hi_hat)
  {
    bool kick_present = false;
    bool snare_present = false;
    bool hi_hat_present = false;
    for (int i=0; i<16; i++)
    {
      if (kick[i] != 0)
      {
        kick_present = true;
      }
      if (snare[i] != 0)
      {
        snare_present = true;
      }
      if (hi_hat[i] != 0)
      {
        hi_hat_present = true;
      }
    }
    // std::cout << "Kick is present " << kick_present << std::endl;
    // std::cout << "Snare is present " << snare_present << std::endl;
    // std::cout << "hi_hat is present " << snare_present << std::endl;
    return ((snare_present || kick_present) && hi_hat_present);
  }

  int find_same_section_with_drums(int*** drum_arrangement, int* bass_arrangement, int total_sections, int current_section)
  {
    int desired_section = -1;
    for (int i=0; i<total_sections; i++)
    {
      if (bass_arrangement[i] == bass_arrangement[current_section])
      {
        // std::cout << "Making it to here.." << std::endl;
        int* kick = drum_arrangement[0][i];
        int* snare = drum_arrangement[1][i];
        int* hi_hat = drum_arrangement[2][i];
        bool contains_drums = bar_contains_drums(kick, snare, hi_hat);
        if (contains_drums)
        {
          // std::cout << "desired_section now doesn't equal -1" << std::endl;
          desired_section = i;
          break;
        }
      }
    }
    // std::cout << "The section with drums: " << desired_section << std::endl;
    return desired_section;
  }

  void create_tracks_from_arrangement_and_chords(int** key_arrangement, int* chord_arrangemnt, int* bass_arrangement, int* section_length, int total_sections, int*** drum_arrangement)
  {
    int** used_chords = new int* [total_sections];
    int** used_riffs = new int* [total_sections];
    int** empty_riff_bar = new int* [16];
    for (int i=0; i<16; i++)
    {
      empty_riff_bar[i] = new int [2];
      empty_riff_bar[i][0] = -1;
      empty_riff_bar[i][1] = 1;
    }
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
    // std::cout << "made it past for 1" << std::endl;

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
      bool no_drums = !bar_contains_drums(kick, snare, hi_hat);

      // std::cout << "current bass_riff: " << current_riff << std::endl;
      if (current_riff == 0)
      {
        std::cout << "118 " << std::endl;
        riff_bar = empty_riff_bar;
      } else {
        std::cout << "121 " << std::endl;
        // std::cout << "used_chords[current_chord-1][0] " << current_chord-1 << std::endl;
        if (used_chords[current_chord-1][0] != -1)
        {
          std::cout << "124 " << std::endl;
          chord_bar = chord_gen::modify_chords(
            all_chords[current_chord-1],
            used_chords[current_chord-1][1],
            used_chords[current_chord-1][2],
            mode,
            start_note
          );
          if (used_riffs[current_riff-1][0] != -1)
          {
            std::cout << "134 " << std::endl;
            riff_bar = music_gen::modify_bar_to_new_mode_or_key(
              all_riffs[current_riff-1],
              used_riffs[current_riff-1][1],
              used_riffs[current_riff-1][2],
              mode,
              start_note,
              1
            );
            // all_riffs[current_riff-1] = riff_bar;
            // used_riffs[current_riff-1][0] = current_riff;
            // used_riffs[current_riff-1][1] = mode;
            // used_riffs[current_riff-1][2] = start_note;
          } else {
            // riff_bar = music_gen::generate_bar_from_chords(chord_bar, 1);
            std::cout << "145 " << std::endl;
            if (no_drums)
            {
              std::cout << "148 " << std::endl;
              int desired_section = find_same_section_with_drums(
                drum_arrangement,
                bass_arrangement,
                total_sections,
                section
              );
              if (desired_section == -1)
              {
                std::cout << "157 " << std::endl;
                riff_bar = music_gen::generate_bar_from_chords(chord_bar, 1);
                // all_riffs[current_riff-1] = riff_bar;
                // used_riffs[current_riff-1][0] = current_riff;
                // used_riffs[current_riff-1][1] = mode;
                // used_riffs[current_riff-1][2] = start_note;
              } else {
                std::cout << "164 " << std::endl;
                kick = drum_arrangement[0][desired_section];
                snare = drum_arrangement[1][desired_section];
                hi_hat = drum_arrangement[2][desired_section];
                riff_bar = music_gen::generate_bar_from_chords_and_drums(
                  kick, snare, hi_hat,
                  chord_bar, 1
                );
                // all_riffs[current_riff-1] = riff_bar;
                // used_riffs[current_riff-1][0] = current_riff;
                // used_riffs[current_riff-1][1] = mode;
                // used_riffs[current_riff-1][2] = start_note;
              }
            } else {
              std::cout << "178 " << std::endl;
              riff_bar = music_gen::generate_bar_from_chords_and_drums(
                kick, snare, hi_hat,
                chord_bar, 1
              );
              // all_riffs[current_riff-1] = riff_bar;
              // used_riffs[current_riff-1][0] = current_riff;
              // used_riffs[current_riff-1][1] = mode;
              // used_riffs[current_riff-1][2] = start_note;
            }

            // riff_bar = music_gen::generate_bar_from_chords_and_drums(
            //   kick, snare, hi_hat,
            //   chord_bar, 1
            // );
            std::cout << "193 " << std::endl;
            // all_riffs[current_riff-1] = riff_bar;
            // used_riffs[current_riff-1][0] = current_riff;
            // if (used_riffs[current_riff-1][1] == -1)
            // {
            //   used_riffs[current_riff-1][1] = mode;
            // }
            // if (used_riffs[current_riff-1][2] == -1)
            // {
            //   used_riffs[current_riff-1][2] = start_note;
            // }


          }
          // all_riffs[current_riff-1] = riff_bar;
          // used_riffs[current_riff-1][0] = current_riff;
          // used_riffs[current_riff-1][1] = mode;
          // used_riffs[current_riff-1][2] = start_note;
        } else {
          std::cout << "200 " << std::endl;
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
            std::cout << "213 " << std::endl;
            riff_bar = music_gen::modify_bar_to_new_mode_or_key(
              all_riffs[current_riff-1],
              used_riffs[current_riff-1][1],
              used_riffs[current_riff-1][2],
              mode,
              start_note,
              1
            );
            // all_riffs[current_riff-1] = riff_bar;
            // used_riffs[current_riff-1][0] = current_riff;
            // used_riffs[current_riff-1][1] = mode;
            // used_riffs[current_riff-1][2] = start_note;
          } else {
            std::cout << "223 " << std::endl;
            // riff_bar = music_gen::generate_bar_from_chords(chord_bar, 1);
            // riff_bar = music_gen::stick_to_root(
            //   kick, snare, hi_hat,
            //   chord_bar, 1
            // );

            if (no_drums)
            {
              std::cout << "232 " << std::endl;
              int desired_section = find_same_section_with_drums(
                drum_arrangement,
                bass_arrangement,
                total_sections,
                section
              );
              if (desired_section == -1)
              {
                // std::cout << "241 " << std::endl;
                riff_bar = music_gen::generate_bar_from_chords(chord_bar, 1);
                // all_riffs[current_riff-1] = riff_bar;
                // used_riffs[current_riff-1][0] = current_riff;
                // used_riffs[current_riff-1][1] = mode;
                // used_riffs[current_riff-1][2] = start_note;
              } else {
                // std::cout << "248 " << std::endl;
                kick = drum_arrangement[0][desired_section];
                snare = drum_arrangement[1][desired_section];
                hi_hat = drum_arrangement[2][desired_section];
                riff_bar = music_gen::generate_bar_from_chords_and_drums(
                  kick, snare, hi_hat,
                  chord_bar, 1
                );
                // all_riffs[current_riff-1] = riff_bar;
                // used_riffs[current_riff-1][0] = current_riff;
                // used_riffs[current_riff-1][1] = mode;
                // used_riffs[current_riff-1][2] = start_note;
              }
              // all_riffs[current_riff-1] = riff_bar;
              // used_riffs[current_riff-1][0] = current_riff;
              // used_riffs[current_riff-1][1] = mode;
              // used_riffs[current_riff-1][2] = start_note;
            } else {
              std::cout << "262 " << std::endl;
              riff_bar = music_gen::generate_bar_from_chords_and_drums(
                kick, snare, hi_hat,
                chord_bar, 1
              );
              // all_riffs[current_riff-1] = riff_bar;
              // used_riffs[current_riff-1][0] = current_riff;
              // used_riffs[current_riff-1][1] = mode;
              // used_riffs[current_riff-1][2] = start_note;
            }
            // riff_bar = music_gen::generate_bar_from_chords_and_drums(
            //   kick, snare, hi_hat,
            //   chord_bar, 1
            // );
            std::cout << "275 " << std::endl;

          }
        }
        // if (all_riffs)


        if (used_riffs[current_riff-1][0] == -1)
        {
          all_riffs[current_riff-1] = riff_bar;
          used_riffs[current_riff-1][0] = current_riff;
        }
        if (used_riffs[current_riff-1][1] == -1)
        {
          used_riffs[current_riff-1][1] = mode;
        }
        if (used_riffs[current_riff-1][2] == -1)
        {
          used_riffs[current_riff-1][2] = start_note;
        }



      }
      std::cout << "284 " << std::endl;
      all_riffs_to_write[section] = riff_bar;
      // all_chords_to_write[section] = chord_bar;
    }

    int current_bar = 0;
    for (int section=0; section<total_sections; section++)
    {
      std::cout << "292 " << std::endl;
      int* fill = drum_arrangement[3][section];
      for (int bar=0; bar<section_length[section]; bar++)
      {
        int** bass_bar;
        if (bar < section_length[section]-1)
        {
          std::cout << "299 " << std::endl;
          bass_bar = all_riffs_to_write[section];
        } else {
          std::cout << "302 " << std::endl;
          bass_bar = music_gen::modify_bar_for_fill(all_riffs_to_write[section], fill);
        }
        bass_writer::write_bass_bar(bass_bar, current_bar);
        current_bar += 1;

        std::cout << "writing bar" << std::endl;
      }
      std::cout << "349 section: " << section << " of " << total_sections << std::endl;
    }


    // for (int i=0; i<16; i++)
    // {
    //   delete[] all_riffs[0][i];
    //   delete[] all_chords[0][i];
    // }
  }
}
