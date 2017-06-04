#include "bass_track.h"

namespace bass_track
{
  void setup_buffers(int total_bars, double end_hang_time)
  {
    if (main_buffer_channels == 0)
    {
      main_buffer_channels = 2;
    }

    main_buffer_size = audio_helper::calculate_total_frames(total_bars, end_hang_time);

    main_buffer = new double* [main_buffer_channels];
    bass_track_1 = new double* [main_buffer_channels];
    bass_track_2 = new double* [main_buffer_channels];

    for (int channel=0; channel<main_buffer_channels; channel++)
    {
      main_buffer[channel] = new double [main_buffer_size];
      bass_track_1[channel] = new double [main_buffer_size];
      bass_track_2[channel] = new double [main_buffer_size];

      for (int i=0; i<main_buffer_size; i++)
      {
        main_buffer[channel][i] = 0;
        bass_track_1[channel][i] = 0;
        bass_track_2[channel][i] = 0;
      }
    }
  }

  void test_creation()
  {
    setup_buffers(60, 3.0);
    drum_track::setup_buffers(60, 3.0);
    srand(time(NULL));
    // int** bass_teenth_array = bass_main::generate_test_teenth(0, 35);
    // int** chord_arr = chord_gen::one45_hqq(5, 36);
    // int** chord_arr = chord_gen::solid_three_chords(5, 36);
    //
    // // int** bass_teenth_array = bass_main::generate_bass_bar(0, 35);
    // int** bass_teenth_array1 = music_gen::generate_bar_from_chords(chord_arr, 2);
    // int** bass_teenth_array2 = music_gen::generate_bar_from_chords(chord_arr, 2);
    // int** bass_teenth_arr_mod1 = music_gen::modify_bar_to_new_mode_or_key(
    //   bass_teenth_array1, 5, 36, 0, 39, 2
    // );
    // int** bass_teenth_arr_mod2 = music_gen::modify_bar_to_new_mode_or_key(
    //     bass_teenth_arr_mod1, 0, 39, 5, 36, 2
    // );
    int total_sections = 32;
    int** key_arrangement = new int* [total_sections];
    int* chord_arrangemnt = new int [total_sections];
    int* bass_arrangement = new int [total_sections];
    int* section_length = new int [total_sections];


    // int** drum_arrangement = new int* [5];
    //
    // for (int j=0; j<5; j++)
    // {
    //   drum_arrangement[j] = new int [total_sections];
    // }

    for (int i=0; i<total_sections; i++)
    {
      key_arrangement[i] = new int [2];
      key_arrangement[i][0] = 5;
      key_arrangement[i][1] = 36;
      chord_arrangemnt[i] = 1;
      bass_arrangement[i] = 1 + (i%2);
      if (i%8 > 3) {
        bass_arrangement[i] += 2;
      }
      section_length[i] = 1;

      // drum_arrangement[0][i] = 1 + (i%2);
      // drum_arrangement[1][i] = 1;
      // drum_arrangement[2][i] = 1 + (i%2);
      // drum_arrangement[3][i] = 8;
      // if (i == 0) {
      //   drum_arrangement[4][i] = 0;
      // } else {
      //   drum_arrangement[4][i] = 1 + (i%2);
      // }

    }






    int drum_arrangement_stand [5][32] = {
      // hi hat
      {1,1,1,1,2,2,2,2,1,1,1,1,  2,2,2,2,3,4,3,4,3,4,3,4,  3,4,3,4,1,1,1,1},
      // snare
      {1,1,1,1,2,2,2,2,1,1,1,1,  2,2,2,2,3,4,3,4,3,4,3,4, 1,2,1,2,1,1,1,1},
      // kick
      {1,1,1,1,2,2,2,2,1,1,1,1,  2,2,2,2,3,4,3,4,3,4,3,4, 1,2,1,2,1,1,1,1},
      // tom fills
      {-1,-1,-1,8,-1,-1,-1,8,-1,-1,-1,8, -1,4,8,12,-1,-1,-1,8,-1,-1,8,12, -1,-1,8,12,-1,-1,-1,8},
      // crash
      {0,0,0,0,2,0,0,0,1,0,0,0, 2,0,0,2,1,0,0,0,2,0,0,2, 1,0,0,0,1,0,1,2}
    };




    int** drum_arr = new int* [5];
    for (int i=0; i<5; i++) {
      drum_arr[i] = new int [12];
      for (int j=0; j<12; j++)
      {
        drum_arr[i][j] = drum_arrangement_stand[i][j];
      }
    }
    int** kick_drum_arrangement = drum_arrangement::create_tracks_from_arrangement(
      drum_arr,
      section_length,
      total_sections
    );

    bass_arrangement::create_tracks_from_arrangement_and_chords(
      key_arrangement,
      chord_arrangemnt,
      bass_arrangement,
      section_length,
      total_sections,
      kick_drum_arrangement
    );


    // for (int i=0; i<16; i++)
    // {
    //   std::cout << "\nNote: " << i << std::endl;
    //   for (int j=0; j<2; j++)
    //   {
    //     std::cout << " " << bass_teenth_array1[i][j];
    //     std::cout << " compare: " << bass_teenth_arr_mod1[i][j];
    //   }
    //   std::cout << std::endl;
    // }

    // new int* [16];
    // for (int i=0; i<16; i++)
    // {
    //   bass_teenth_array[i] = new int [2];
    //   bass_teenth_array[i][0] = 35;
    //   bass_teenth_array[i][1] = 1;
    // }
    // for (int i=0; i<8; i++)
    // {
    //   if (i%4 == 0)
    //   {
    //     // bass_writer::write_bass_bar(bass_teenth_array2, i);
    //     bass_writer::write_bass_bar(bass_teenth_arr_mod2, i);
    //   } else if (i%4 == 1) {
    //     bass_writer::write_bass_bar(bass_teenth_array1, i);
    //   } else if (i%4 == 2) {
    //     bass_writer::write_bass_bar(bass_teenth_arr_mod2, i);
    //     // bass_writer::write_bass_bar(bass_teenth_arr_mod1, i);
    //   } else {
    //     bass_writer::write_bass_bar(bass_teenth_array1, i);
    //     // bass_writer::write_bass_bar(bass_teenth_arr_mod2, i);
    //   }
    // }

    // int** arrangement = new int* [5];
    // for (int i=0; i<5; i++) {
    //   arrangement[i] = new int [12];
    //   for (int j=0; j<12; j++)
    //   {
    //     arrangement[i][j] = drum_arrangement::drum_arrangement_standard_2[i][j];
    //   }
    // }
    // bass_arrangement::create_tracks_from_arrangement(
    //   arrangement,
    //   arrangement_main::section_length_standard_2,
    //   12
    // );
    for (int channel=0; channel<main_buffer_channels; channel++)
    {
      for (int i=0; i<main_buffer_size; i++)
      {
        main_buffer[channel][i] += bass_track_1[channel][i];
        main_buffer[channel][i] += bass_track_2[channel][i];


        /////////////////////////////// DRUMS ::::

        main_buffer[channel][i] += drum_track::hi_hat_track[channel][i];
        main_buffer[channel][i] += drum_track::tom_track[channel][i];
        main_buffer[channel][i] += drum_track::kick_track[channel][i];
        main_buffer[channel][i] += drum_track::snare_track[channel][i];
        main_buffer[channel][i] += drum_track::crash_track[channel][i];
      }
    }
  }

  void free_all_track_memory()
  {
    for (int i=0; i<main_buffer_channels; i++)
    {
      delete[] main_buffer[i];
      delete[] bass_track_1[i];
      delete[] bass_track_2[i];
    }
    delete[] main_buffer;
    delete[] bass_track_1;
    delete[] bass_track_2;
  }
}
