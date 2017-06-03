#include "drum_arrangement.h"

namespace drum_arrangement
{
  // int** generate_drum_arrangement(int unique_sections, int total_sections)
  // {
  //   int num_of_tracks = 5;
  //   int sections_included = 0;
  //   int** arrangement_array = new int* [num_of_tracks+1];
  //   arrangement_array[0] = new int [total_sections];
  //   for (int section=0; section<total_sections; section++)
  //   {
  //     // section_length;
  //     arrangement_array[0][section] = pow (2, (rand()%3)+1);
  //   }
  //   for (int track=1; track<num_of_tracks+1; track++)
  //   {
  //     arrangement_array[track] = new int [total_sections];
  //
  //     int section_selection;
  //     if (sections_included == 0) {
  //       sections_included = 1;
  //       section_selection = 1;
  //     } else {
  //       section_selection = (rand()%(sections_included+1))+1;
  //     }
  //     if (section_selection > sections_included) {
  //       sections_included = section_selection
  //     }
  //     for (int section=0; section<total_sections; section++)
  //     {
  //       if (track < 4)
  //       {
  //         arrangement_array[track][section] = section_selection;
  //       } else if (track == 4) {
  //         arrangement_array[track][section] =
  //       }
  //     }
  //   }
  //
  //   // for (int track=0; track<num_of_tracks; track++)
  //   // {
  //   //   arrangement_array[track] = new int* [total_sections];
  //   //   for (int section=0; section<total_sections; section++)
  //   //   {
  //   //     int section_length = ((rand()%2)+1)*4;
  //   //     arrangement[track][section] = new int [2];
  //   //     if (track < 3)
  //   //     {
  //   //       arrangement[track][section][0] = rand()%(unique_sections+1);
  //   //       arrangement[track][section][1] =
  //   //     } else if (track == 3) {
  //   //       if (arrangement[track-1][section][0] == 0) {
  //   //         arrangement[track][section][0] = rand()%unique_sections;
  //   //       }
  //   //
  //   //       arrangement[track][section][1] = ((rand()%2)+1)*4;
  //   //     } else if (track == 4) {
  //   //
  //   //     }
  //   //   }
  //   // }
  // }
  int num_of_unique_sections(int* arrangement, int total_sections)
  {
    int unique_sections = 0;
    for (int section=0; section<total_sections; section++)
    {
      if (arrangement[section] > unique_sections) {
        unique_sections = arrangement[section];
      }
    }
    return unique_sections;
  }

  int*** create_tracks_from_arrangement(int** arrangement, int* section_length, int total_sections)
  {
    int hi_hat_sections = arrangement_main::num_of_unique_sections(arrangement[0], total_sections);
    int kick_sections = arrangement_main::num_of_unique_sections(arrangement[1], total_sections);
    int snare_sections = arrangement_main::num_of_unique_sections(arrangement[2], total_sections);

    int** hi_hat_arrays = new int* [hi_hat_sections];
    for (int unique_bar=0; unique_bar<hi_hat_sections; unique_bar++)
    {
      int* hi_hat_array = hi_hat_generator::generate_hi_hat_teenth_array();
      hi_hat_arrays[unique_bar] = hi_hat_array;
    }

    int** kick_arrays = new int* [kick_sections];
    for (int unique_bar=0; unique_bar<kick_sections; unique_bar++)
    {
      int* kick_array = kick_generator::get_random_kick_standard();
      kick_arrays[unique_bar] = kick_array;
    }

    int** snare_arrays = new int* [snare_sections];
    for (int unique_bar=0; unique_bar<snare_sections; unique_bar++)
    {
      int* snare_array = snare_generator::get_random_snare_standard();
      snare_arrays[unique_bar] = snare_array;
    }

    int* empty_array = new int [16];
    for (int i=0; i<16; i++)
    {
      empty_array[i] = 0;
    }

    int num_of_drums = 4; //kick, snare, hi_hat;
    int*** all_drum_arrangements = new int** [num_of_drums];

    for (int drum=0; drum<num_of_drums; drum++)
    {
      all_drum_arrangements[drum] = new int* [total_sections];
    }

    // int** kick_arrangement = new int* [total_sections];
    // int** snare_arrangement = new int* [total_sections];
    // int** hi_hat_arrangement = new int* [total_sections];

    int current_bar = 0;
    for (int section=0; section<total_sections; section++)
    {

      int hi_hat_index = arrangement[0][section];
      int* hi_hat;
      if (hi_hat_index != 0)
      {
        hi_hat = hi_hat_arrays[hi_hat_index-1];
      } else {
        hi_hat = empty_array;
      }
      int snare_index = arrangement[1][section];
      int* snare;
      if (snare_index != 0)
      {
        snare = snare_arrays[snare_index-1];
      } else {
        snare = empty_array;
      }

      int kick_index = arrangement[2][section];
      int* kick;
      if (snare_index != 0)
      {
        kick = kick_arrays[kick_index-1];
      } else {
        kick = empty_array;
      }

      int fill_length = arrangement[3][section];
      int crash = arrangement[4][section];

      all_drum_arrangements[0][section] = kick;
      all_drum_arrangements[1][section] = snare;
      all_drum_arrangements[2][section] = hi_hat;


      for (int bar=0; bar<section_length[section]; bar++)
      {
        if (crash != 0 && crash != -1 && bar == 0)
        {
          crash_writer::write_crash_at_bar(crash, current_bar);
        }

        // std::cout << "\ncurrent_bar " << current_bar << std::endl;

        if (bar == section_length[section]-1 && fill_length != -1) {
          int* silence_arr = audio_helper::silence_array(16-fill_length,16);
          int* hi_hat_silence = audio_helper::silence_hits(silence_arr, hi_hat);
          int* kick_silence = audio_helper::silence_hits(silence_arr, kick);
          int* snare_silence = audio_helper::silence_hits(silence_arr, snare);
          int* tom_array = tom_generator::generate_tom_teenth_array(fill_length);
          all_drum_arrangements[3][section] = tom_array;
          tom_writer::write_from_array_at_bar(tom_array, current_bar);
          hi_hat_writer::write_from_array_at_bar(hi_hat_silence, current_bar);
          snare_writer::write_from_array_at_bar(snare_silence, current_bar);
          kick_writer::write_from_array_at_bar(kick_silence, current_bar);
        } else {
          hi_hat_writer::write_from_array_at_bar(hi_hat, current_bar);
          snare_writer::write_from_array_at_bar(snare, current_bar);
          kick_writer::write_from_array_at_bar(kick, current_bar);
          all_drum_arrangements[3][section] = empty_array;
        }
        current_bar += 1;
      }
    }
    return all_drum_arrangements;
  }
}
