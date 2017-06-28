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
    return ((snare_present || kick_present) && hi_hat_present);
  }

  int find_same_section_with_drums(int*** drum_arrangement, int* bass_arrangement, int total_sections, int current_section)
  {
    int desired_section = -1;
    for (int i=0; i<total_sections; i++)
    {
      if (bass_arrangement[i] == bass_arrangement[current_section])
      {
        int* kick = drum_arrangement[0][i];
        int* snare = drum_arrangement[1][i];
        int* hi_hat = drum_arrangement[2][i];
        bool contains_drums = bar_contains_drums(kick, snare, hi_hat);
        if (contains_drums)
        {
          desired_section = i;
          break;
        }
      }
    }
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

    int*** all_riffs = new int** [total_sections];
    int*** all_chords = new int** [total_sections];
    int*** all_riffs_to_write = new int** [total_sections];

    for (int section=0; section<total_sections; section++)
    {


      int start_note = key_arrangement[section][1];
      int mode = key_arrangement[section][0];
      int current_chord = chord_arrangemnt[section];
      int current_riff = bass_arrangement[section];

      int** chord_bar;
      int** riff_bar;

      int* kick = drum_arrangement[0][section];
      int* snare = drum_arrangement[1][section];
      int* hi_hat = drum_arrangement[2][section];
      bool no_drums = !bar_contains_drums(kick, snare, hi_hat);

      if (current_riff == 0)
      {
        riff_bar = empty_riff_bar;
      } else {
        if (used_chords[current_chord-1][0] != -1)
        {
          chord_bar = chord_gen::modify_chords(
            all_chords[current_chord-1],
            used_chords[current_chord-1][1],
            used_chords[current_chord-1][2],
            mode,
            start_note
          );
          if (used_riffs[current_riff-1][0] != -1)
          {
            riff_bar = music_gen::modify_bar_to_new_mode_or_key(
              all_riffs[current_riff-1],
              used_riffs[current_riff-1][1],
              used_riffs[current_riff-1][2],
              mode,
              start_note,
              1
            );
          } else {
            if (no_drums)
            {
              int desired_section = find_same_section_with_drums(
                drum_arrangement,
                bass_arrangement,
                total_sections,
                section
              );
              if (desired_section == -1)
              {
                riff_bar = music_gen::generate_bar_from_chords(chord_bar, 1);

              } else {
                kick = drum_arrangement[0][desired_section];
                snare = drum_arrangement[1][desired_section];
                hi_hat = drum_arrangement[2][desired_section];
                riff_bar = music_gen::generate_bar_from_chords_and_drums(
                  kick, snare, hi_hat,
                  chord_bar, 1
                );
              }
            } else {
              riff_bar = music_gen::generate_bar_from_chords_and_drums(
                kick, snare, hi_hat,
                chord_bar, 1
              );
            }
          }
        } else {
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
            riff_bar = music_gen::modify_bar_to_new_mode_or_key(
              all_riffs[current_riff-1],
              used_riffs[current_riff-1][1],
              used_riffs[current_riff-1][2],
              mode,
              start_note,
              1
            );
          } else {
            if (no_drums)
            {
              int desired_section = find_same_section_with_drums(
                drum_arrangement,
                bass_arrangement,
                total_sections,
                section
              );
              if (desired_section == -1)
              {
                riff_bar = music_gen::generate_bar_from_chords(chord_bar, 1);
              } else {
                kick = drum_arrangement[0][desired_section];
                snare = drum_arrangement[1][desired_section];
                hi_hat = drum_arrangement[2][desired_section];
                riff_bar = music_gen::generate_bar_from_chords_and_drums(
                  kick, snare, hi_hat,
                  chord_bar, 1
                );
              }
            } else {
              riff_bar = music_gen::generate_bar_from_chords_and_drums(
                kick, snare, hi_hat,
                chord_bar, 1
              );
            }
          }
        }

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

      all_riffs_to_write[section] = riff_bar;
    }

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
  }
}
