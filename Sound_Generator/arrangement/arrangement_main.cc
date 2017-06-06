#include "arrangement_main.h"

namespace arrangement_main
{
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

  void generate_arrangements_and_create_tracks(int mode, int starting_note)
  {
    srand(time(NULL));

    bool intro = true;
    int intro_length = 0;
    if (intro)
    {
      intro_length = pow(2, 1+rand()%4);
    }

    int middle_length = pow(2, (rand()%3)+4);
    int end_length = pow(2, rand()%5);

    // if (middle_length == 64)


    // bool breakdown = (rand()%100 < 20);
    // int breakdown_length = 0;
    // if (breakdown)
    // {
    //   breakdown_length = pow(2, 1+ (rand()%4));
    // }

    bool double_intro = false;

    int double_middle_mult = 1;
    int double_intro_mult = 1;

    if (intro_length > 0)
    {
      double_intro = (rand()%100 < 15);
    }

    bool double_middle = (rand()%100 < 15);
    bool breakdown = (rand()%100 < 20);

    int breakdown_length = 0;
    if (breakdown)
    {
      breakdown_length = pow(2, 1+ (rand()%4));
    }

    if (double_intro)
    {
      double_middle = true;
    }

    if (middle_length > 32)
    {
      if (double_middle)
      {
        double_intro = true;
        breakdown = true;
      }
      double_middle = false;
    }




    if (double_middle)
    {
      double_middle_mult = 2;
    }

    if (double_intro)
    {
      double_intro_mult = 2;
    }

    std::cout << "debugging on line 79 " << std::endl;
    bool alternate_sections = (rand()%100 > 50);
    bool alternate_section2 = (rand()%100 > 50);
    bool alternate_section3 = (rand()%100 > 50);

    // bool alternate_sections = true;
    // bool alternate_section2 = true;
    // bool alternate_section3 = true;

    if (intro_length == 1 && alternate_sections)
    {
      intro_length = 2;
    }

    int total_sections = ((intro_length*double_intro_mult)
      + (middle_length * double_middle_mult)
      + breakdown_length
      + end_length
    );

    // set up entire arrangement;
    int** drum_arrangement_all = new int* [5];
    for (int i=0; i<5; i++)
    {
      drum_arrangement_all[i] = new int [total_sections];
    }
    int** key_arrangement_all = new int* [total_sections];
    int* chord_arrangement_all = new int [total_sections];
    int* bass_arrangement_all = new int [total_sections];
    int* section_length_all = new int [total_sections];
    for (int i=0; i<total_sections; i++)
    {
      section_length_all[i] = 1;
    }

    for (int i=0; i<total_sections; i++)
    {
      key_arrangement_all[i] = new int [2];
      key_arrangement_all[i][0] = mode;
      key_arrangement_all[i][1] = starting_note;
      chord_arrangement_all[i] = 1;
      bass_arrangement_all[i] = 0;
      drum_arrangement_all[0][i] = 0;
      drum_arrangement_all[1][i] = 0;
      drum_arrangement_all[2][i] = 0;
      drum_arrangement_all[3][i] = -1;
      drum_arrangement_all[4][i] = 0;
    }

    std::cout << "Made it to line 117. " <<std::endl;

    int highest_snare = 0;
    int highest_kick = 0;
    int highest_hi_hat = 0;
    int highest_bass  = 0;

    int stored_highest_snare = 0;
    int stored_highest_kick = 0;
    int stored_highest_hi_hat = 0;
    int stored_highest_bass  = 0;

    if (intro_length > 0)
    {
      std::cout << "Made it into intro (line 131). " <<std::endl;

      int bass_start_ord = rand()%4;
      int hi_hat_start_ord = rand()%4;
      int kick_start_ord = rand()%4;
      int snare_start_ord = rand()%4;

      bool snare_starts_first = rand()%100 < 10;


      if (snare_starts_first)
      {
        snare_start_ord = 0;
        if (bass_start_ord == 0)
        {
          bass_start_ord = 1;
        }
        if (hi_hat_start_ord == 0)
        {
          hi_hat_start_ord = 1;
        }
        if (kick_start_ord == 0)
        {
          kick_start_ord = 1;
        }
      } else {
        if (snare_start_ord == 0)
        {
          snare_start_ord = 3;
        }
      }

      int* entry_order = new int [4]; // bass, hi_hat, kick, snare;
      entry_order[0] = bass_start_ord;
      entry_order[1] = hi_hat_start_ord;
      entry_order[2] = kick_start_ord;
      entry_order[3] = snare_start_ord;


      int instrument_starts = -1;
      int instrument_left_out = -1;

      for (int i=0; i<4; i++)
      {
        if (entry_order[i] == 0)
        {
          instrument_starts = i;
        } else if (entry_order[i] == 3) {
          instrument_left_out = i;
        }
      }

      while (instrument_starts < 0)
      {
        instrument_starts = rand()%3;
        if (instrument_starts == instrument_left_out) {
          instrument_starts = -1;
        } else {
          entry_order[instrument_starts] = 0;
        }
      }

      while (instrument_left_out < 0)
      {
        instrument_left_out = rand()%4;
        if (instrument_left_out == instrument_starts)
        {
          instrument_left_out = -1;
        } else {
          entry_order[instrument_left_out] = 3;
        }
      }

      // int** intro_key_arrangement = new int* [intro_length];
      // int* intro_chord_arrangement = new int* [intro_length];
      // int* intro_bass_arrangement = new int [intro_length];
      //
      // int** intro_drum_arrangement = new int * [5];
      // for (int i=0; i<5; i++)
      // {
      //   intro_drum_arrangement[i] = new int [intro_length];
      // }

      bool intro_ends_in_tom_fill = (rand()%100) > 40;

      int second_enter_locations [5] = {0,1,2,4,8};
      int second_enter;
      if (intro_length <= 4)
      {
        second_enter = second_enter_locations[rand()%5];
      } else if (intro_length > 4 && intro_length <= 8) {
        second_enter = second_enter_locations[2+rand()%3];
      } else {
        second_enter = second_enter_locations[3+rand()%2];
      }

      int third_enter_locations [4] = {4,8,16,32};
      int third_enter = third_enter_locations[rand()%3];
      if (intro_length == 16)
      {
        third_enter = third_enter_locations[rand()%2];
      }
      int final_enter = third_enter_locations[1+(rand()%3)];

      // for (int i=0; i<intro_length; i++)
      // {
      //
      //   // key_arrangement_all[i] = new int [2];
      //   key_arrangement_all[i][0] = mode;
      //   key_arrangement_all[i][1] = starting_note;
      //   bass_arrangement_all[i] = 0;
      //   drum_arrangement_all[0][i] = 0;
      //   drum_arrangement_all[1][i] = 0;
      //   drum_arrangement_all[2][i] = 0;
      //   drum_arrangement_all[3][i] = -1;
      //   drum_arrangement_all[4][i] = 0;
      // }


      for (int i=0; i<intro_length; i++)
      {
        // std::cout << "iterating intro (line 251). i: " << i << " intro length: " << intro_length << std::endl;
        int section = 1;
        if (alternate_sections)
        {
          section = 1 + i%2;
        }

        if (entry_order[0] == 0)
        {
          bass_arrangement_all[i] = section;

          if (section > highest_bass)
          {
            highest_bass = section;
            stored_highest_bass = section;
          }
        }
        if (entry_order[1] == 0) {
          drum_arrangement_all[0][i] = section;
          if (section > highest_hi_hat)
          {
            highest_hi_hat = section;
            stored_highest_hi_hat = section;
          }
        }
        if (entry_order[2] == 0) {
          drum_arrangement_all[2][i] = section;
          if (section > highest_kick)
          {
            highest_kick = section;
            stored_highest_kick = section;
          }
        }
        if (entry_order[3] == 0) {
          drum_arrangement_all[1][i] = section;
          if (section > highest_snare)
          {
            highest_snare = section;
            stored_highest_snare = section;
          }
        }

        if (i >= second_enter)
        {
          if (entry_order[0] == 1)
          {
            bass_arrangement_all[i] = section;

            if (section > highest_bass)
            {
              highest_bass = section;
              stored_highest_bass = section;
            }
          }
          if (entry_order[1] == 1) {
            drum_arrangement_all[0][i] = section;
            if (section > highest_hi_hat)
            {
              highest_hi_hat = section;
              stored_highest_hi_hat = section;
            }
          }
          if (entry_order[2] == 1) {
            drum_arrangement_all[2][i] = section;
            if (section > highest_kick)
            {
              highest_kick = section;
              stored_highest_kick = section;
            }
          }
          if (entry_order[3] == 1) {
            drum_arrangement_all[1][i] = section;
            if (section > highest_snare)
            {
              highest_snare = section;
              stored_highest_snare = section;
            }
          }
        }

        if (i >= third_enter)
        {
          if (entry_order[0] == 2)
          {
            bass_arrangement_all[i] = section;

            if (section > highest_bass)
            {
              highest_bass = section;
              stored_highest_bass = section;
            }
          }
          if (entry_order[1] == 2) {
            drum_arrangement_all[0][i] = section;
            if (section > highest_hi_hat)
            {
              highest_hi_hat = section;
              stored_highest_hi_hat = section;
            }
          }
          if (entry_order[2] == 2) {
            drum_arrangement_all[2][i] = section;
            if (section > highest_kick)
            {
              highest_kick = section;
              stored_highest_kick = section;
            }
          }
          if (entry_order[3] == 2) {
            drum_arrangement_all[1][i] = section;
            if (section > highest_snare)
            {
              highest_snare = section;
              stored_highest_snare = section;
            }
          }
        }

        if (i >= final_enter)
        {
          if (entry_order[0] == 3)
          {
            bass_arrangement_all[i] = section;
            if (section > highest_bass)
            {
              highest_bass = section;
              stored_highest_bass = section;
            }
          }
          if (entry_order[1] == 3) {
            drum_arrangement_all[0][i] = section;
            if (section > highest_hi_hat)
            {
              highest_hi_hat = section;
              stored_highest_hi_hat = section;
            }
          }
          if (entry_order[2] == 3) {
            drum_arrangement_all[2][i] = section;
            if (section > highest_kick)
            {
              highest_kick = section;
              stored_highest_kick = section;
            }
          }
          if (entry_order[3] == 3) {
            drum_arrangement_all[1][i] = section;
            if (section > highest_snare)
            {
              highest_snare = section;
              stored_highest_snare = section;
            }
          }
        }

        if ((intro_ends_in_tom_fill || intro_length == 16) && i == (intro_length -1))
        {
          drum_arrangement_all[3][i] = 4 + (4*rand()%3);
        }
      }
    }

    bool mid_continues_intro = (rand()%100 > intro_length*5);


    bool four_part_mid = true;
    if (middle_length == 16)
    {
      four_part_mid = (rand()%100 < 40);
    }
    bool eight_part_mid = false;
    bool six_part_mid = false;


    if (middle_length == 32)
    {
      six_part_mid = (rand()%100 < 90);
      eight_part_mid = (rand()%100 < 40);
    }
    if (middle_length == 64)
    {
      six_part_mid = true;
      eight_part_mid = (rand()%100 < 20);
    }

    std::cout <<  "\n\nfour pt: " << four_part_mid << " six_pt: " << six_part_mid << " eight pt: " << eight_part_mid << "\n\n" << std::endl;

    int split = middle_length/2;
    int split2 = split/2 + ((1-(rand()%3))*(split/4));
    if (middle_length == 64)
    {
      split2 = split/2;
    }
    for (int i=0; i<middle_length; i++)
    {
      // std::cout << "iterating middle (line 423). i: " << i << " middle length: " << middle_length << std::endl;
      // drum_arrangement_all[0][i] = 0;
      // drum_arrangement_all[1][i] = 0;
      // drum_arrangement_all[2][i] = 0;
      // drum_arrangement_all[3][i] = -1;
      // drum_arrangement_all[4][i] = 0;
      // bass_arrangement_all[i] = 0;
      if (four_part_mid)
      {

        if (i%split >= split2)
        {
          std::cout << "second half of split. section: " << i << std::endl;
          if (i == split2 || (eight_part_mid && i == split+split2))
          {
            stored_highest_bass = highest_bass;
            stored_highest_kick = highest_kick;
            stored_highest_hi_hat = highest_hi_hat;
            stored_highest_snare = highest_snare;
          }

          int section = 1;
          if (alternate_section3)
          {
            section = 1 + (i%2);
          }
          if (six_part_mid && (i >= split+split2))
          {
            bass_arrangement_all[i+intro_length] = bass_arrangement_all[intro_length+section -1];
            drum_arrangement_all[0][i+intro_length] = drum_arrangement_all[0][intro_length+section-1];
            drum_arrangement_all[1][i+intro_length] = drum_arrangement_all[1][intro_length+section -1];
            drum_arrangement_all[2][i+intro_length] = drum_arrangement_all[2][intro_length+section -1];
          } else {
            bass_arrangement_all[i+intro_length] = stored_highest_bass + section;
            if ((stored_highest_bass + section) > highest_bass)
            {
              highest_bass = stored_highest_bass + section;
            }
            drum_arrangement_all[0][i+intro_length] = stored_highest_hi_hat + section;
            if ((stored_highest_hi_hat + section) > highest_hi_hat)
            {
              highest_hi_hat = stored_highest_hi_hat + section;
            }
            drum_arrangement_all[1][i+intro_length] = stored_highest_snare + section;
            if ((stored_highest_snare + section) > highest_snare)
            {
              highest_snare = stored_highest_snare + section;
            }
            drum_arrangement_all[2][i+intro_length] = stored_highest_kick + section;
            if ((stored_highest_kick + section) > highest_kick)
            {
              highest_kick = stored_highest_kick + section;
            }
          }
          // section2 here.
        } else {
          // section 1.
          if (mid_continues_intro && intro_length > 0 && ((i < split) || (!eight_part_mid && !six_part_mid)))
          {
            if (alternate_sections)
            {
              int section = 1+ (i%2);
              if (drum_arrangement_all[0][intro_length-(2-(i%2))] == 0)
              {
                drum_arrangement_all[0][i+intro_length] = section;
                if (section > highest_hi_hat)
                {
                  highest_hi_hat = section;
                  stored_highest_hi_hat = section;
                }
              } else {
                drum_arrangement_all[0][i+intro_length] = drum_arrangement_all[0][intro_length-(2-(i%2))];
              }
              if (drum_arrangement_all[1][intro_length-(2-(i%2))] == 0)
              {
                drum_arrangement_all[1][i+intro_length] = section;
                if (section > highest_snare)
                {
                  highest_snare = section;
                  stored_highest_snare = section;
                }
              } else {
                drum_arrangement_all[1][i+intro_length] = drum_arrangement_all[1][intro_length-(2-(i%2))];
              }
              if (drum_arrangement_all[2][intro_length-(2-(i%2))] == 0)
              {
                drum_arrangement_all[2][i+intro_length] = section;
                if (section > highest_kick)
                {
                  highest_kick = section;
                  stored_highest_kick = section;
                }
              } else {
                drum_arrangement_all[2][i+intro_length] = drum_arrangement_all[2][intro_length-(2-(i%2))];
              }

              if (bass_arrangement_all[intro_length-(2-(i%2))] == 0)
              {
                bass_arrangement_all[i+intro_length] = section;
                if (section > highest_bass)
                {
                  highest_bass = section;
                  stored_highest_bass = section;
                }
              } else {
                bass_arrangement_all[i+intro_length] = bass_arrangement_all[intro_length-(2-(i%2))];
              }
            } else {
              int section = 1;
              if (drum_arrangement_all[0][intro_length-1] == 0)
              {
                drum_arrangement_all[0][i+intro_length] = section;
                if (section > highest_hi_hat)
                {
                  highest_hi_hat = section;
                  stored_highest_hi_hat = section;
                }
              } else {
                drum_arrangement_all[0][i+intro_length] = drum_arrangement_all[0][intro_length-1];
              }
              if (drum_arrangement_all[1][intro_length-1] == 0)
              {
                drum_arrangement_all[1][i+intro_length] = section;
                if (section > highest_snare)
                {
                  highest_snare = section;
                  stored_highest_snare = section;
                }
              } else {
                drum_arrangement_all[1][i+intro_length] = drum_arrangement_all[1][intro_length-1];
              }
              if (drum_arrangement_all[2][intro_length-1] == 0)
              {
                drum_arrangement_all[2][i+intro_length] = section;
                if (section > highest_kick)
                {
                  highest_kick = section;
                  stored_highest_kick = section;
                }
              } else {
                drum_arrangement_all[2][i+intro_length] = drum_arrangement_all[2][intro_length-1];
              }

              if (bass_arrangement_all[intro_length-1] == 0)
              {
                bass_arrangement_all[i+intro_length] = section;
                if (section > highest_bass)
                {
                  highest_bass = section;
                  stored_highest_bass = section;
                }
              } else {
                bass_arrangement_all[i+intro_length] = bass_arrangement_all[intro_length-1];
              }
            }
          } else {
            if (i==0 || (i == split && (eight_part_mid || six_part_mid)))
            {
              stored_highest_bass = highest_bass;
              stored_highest_kick = highest_kick;
              stored_highest_hi_hat = highest_hi_hat;
              stored_highest_snare = highest_snare;
            }
            int section = 1;
            if (alternate_section2)
            {
              section = 1 + (rand()%2);
            }
            bass_arrangement_all[i+intro_length] = stored_highest_bass + section;
            if ((stored_highest_bass + section) > highest_bass)
            {
              highest_bass = stored_highest_bass + section;
            }
            drum_arrangement_all[0][i+intro_length] = stored_highest_hi_hat + section;
            if ((stored_highest_hi_hat + section) > highest_hi_hat)
            {
              highest_hi_hat = stored_highest_hi_hat + section;
            }
            drum_arrangement_all[1][i+intro_length] = stored_highest_snare + section;
            if ((stored_highest_snare + section) > highest_snare)
            {
              highest_snare = stored_highest_snare + section;
            }
            drum_arrangement_all[2][i+intro_length] = stored_highest_kick + section;
            if ((stored_highest_kick + section) > highest_kick)
            {
              highest_kick = stored_highest_kick + section;
            }
          }
        }
      } else {
        if (i >= split)
        {
          if (i == split)
          {
            stored_highest_bass = highest_bass;
            stored_highest_kick = highest_kick;
            stored_highest_hi_hat = highest_hi_hat;
            stored_highest_snare = highest_snare;
          }

          int section = 1;
          if (alternate_section3)
          {
            section = 1 + (i%2);
          }
          bass_arrangement_all[i+intro_length] = stored_highest_bass + section;
          if ((stored_highest_bass + section) > highest_bass)
          {
            highest_bass = stored_highest_bass + section;
          }
          drum_arrangement_all[0][i+intro_length] = stored_highest_hi_hat + section;
          if ((stored_highest_hi_hat + section) > highest_hi_hat)
          {
            highest_hi_hat = stored_highest_hi_hat + section;
          }
          drum_arrangement_all[1][i+intro_length] = stored_highest_snare + section;
          if ((stored_highest_snare + section) > highest_snare)
          {
            highest_snare = stored_highest_snare + section;
          }
          drum_arrangement_all[2][i+intro_length] = stored_highest_kick + section;
          if ((stored_highest_kick + section) > highest_kick)
          {
            highest_kick = stored_highest_kick + section;
          }
          //section2
        } else {
          //section 1
          if (mid_continues_intro && intro_length > 0)
          {
            if (alternate_sections)
            {
              int section = 1+ (i%2);
              if (drum_arrangement_all[0][intro_length-(2-(i%2))] == 0)
              {
                drum_arrangement_all[0][i+intro_length] = section;
                if (section > highest_hi_hat)
                {
                  highest_hi_hat = section;
                  stored_highest_hi_hat = section;
                }
              } else {
                drum_arrangement_all[0][i+intro_length] = drum_arrangement_all[0][intro_length-(2-(i%2))];
              }
              if (drum_arrangement_all[1][intro_length-(2-(i%2))] == 0)
              {
                drum_arrangement_all[1][i+intro_length] = section;
                if (section > highest_snare)
                {
                  highest_snare = section;
                  stored_highest_snare = section;
                }
              } else {
                drum_arrangement_all[1][i+intro_length] = drum_arrangement_all[1][intro_length-(2-(i%2))];
              }
              if (drum_arrangement_all[2][intro_length-(2-(i%2))] == 0)
              {
                drum_arrangement_all[2][i+intro_length] = section;
                if (section > highest_kick)
                {
                  highest_kick = section;
                  stored_highest_kick = section;
                }
              } else {
                drum_arrangement_all[2][i+intro_length] = drum_arrangement_all[2][intro_length-(2-(i%2))];
              }

              if (bass_arrangement_all[intro_length-(2-(i%2))] == 0)
              {
                bass_arrangement_all[i+intro_length] = section;
                if (section > highest_hi_hat)
                {
                  highest_hi_hat = section;
                  stored_highest_hi_hat = section;
                }
              } else {
                bass_arrangement_all[i+intro_length] = bass_arrangement_all[intro_length-(2-(i%2))];
              }
            } else {
              int section = 1;
              if (drum_arrangement_all[0][intro_length-1] == 0)
              {
                drum_arrangement_all[0][i+intro_length] = section;
                if (section > highest_hi_hat)
                {
                  highest_hi_hat = section;
                  stored_highest_hi_hat = section;
                }
              } else {
                drum_arrangement_all[0][i+intro_length] = drum_arrangement_all[0][intro_length-1];
              }
              if (drum_arrangement_all[1][intro_length-1] == 0)
              {
                drum_arrangement_all[1][i+intro_length] = section;
                if (section > highest_snare)
                {
                  highest_snare = section;
                  stored_highest_snare = section;
                }
              } else {
                drum_arrangement_all[1][i+intro_length] = drum_arrangement_all[1][intro_length-1];
              }
              if (drum_arrangement_all[2][intro_length-1] == 0)
              {
                drum_arrangement_all[2][i+intro_length] = section;
                if (section > highest_kick)
                {
                  highest_kick = section;
                  stored_highest_kick = section;
                }
              } else {
                drum_arrangement_all[2][i+intro_length] = drum_arrangement_all[2][intro_length-1];
              }

              if (bass_arrangement_all[intro_length-1] == 0)
              {
                bass_arrangement_all[i+intro_length] = section;
                if (section > highest_bass)
                {
                  highest_bass = section;
                  stored_highest_bass = section;
                }
              } else {
                bass_arrangement_all[i+intro_length] = bass_arrangement_all[intro_length-1];
              }
            }
          } else {
            if (i==0)
            {
              stored_highest_bass = highest_bass;
              stored_highest_kick = highest_kick;
              stored_highest_hi_hat = highest_hi_hat;
              stored_highest_snare = highest_snare;
            }
            int section = 1;
            if (alternate_section2)
            {
              section = 1 + (i%2);
            }
            bass_arrangement_all[i+intro_length] = stored_highest_bass + section;
            if ((stored_highest_bass + section) > highest_bass)
            {
              highest_bass = stored_highest_bass + section;
            }
            drum_arrangement_all[0][i+intro_length] = stored_highest_hi_hat + section;
            if ((stored_highest_hi_hat + section) > highest_hi_hat)
            {
              highest_hi_hat = stored_highest_hi_hat + section;
            }
            drum_arrangement_all[1][i+intro_length] = stored_highest_snare + section;
            if ((stored_highest_snare + section) > highest_snare)
            {
              highest_snare = stored_highest_snare + section;
            }
            drum_arrangement_all[2][i+intro_length] = stored_highest_kick + section;
            if ((stored_highest_kick + section) > highest_kick)
            {
              highest_kick = stored_highest_kick + section;
            }
          }
        }
      }
    }

    stored_highest_kick = highest_kick;
    stored_highest_snare = highest_snare;
    stored_highest_hi_hat = highest_hi_hat;
    stored_highest_bass = highest_bass;

    if (double_intro)
    {
      std::cout << "made it to double intro part (766)"<< std::endl;
      for (int i=0; i<intro_length; i++)
      {
        drum_arrangement_all[0][i+intro_length+middle_length] =  drum_arrangement_all[0][i];
        drum_arrangement_all[1][i+intro_length+middle_length] =  drum_arrangement_all[1][i];
        drum_arrangement_all[2][i+intro_length+middle_length] =  drum_arrangement_all[2][i];
        drum_arrangement_all[3][i+intro_length+middle_length] =  drum_arrangement_all[3][i];
        drum_arrangement_all[4][i+intro_length+middle_length] =  drum_arrangement_all[4][i];
        bass_arrangement_all[i+intro_length+middle_length] = bass_arrangement_all[i];
      }
      highest_hi_hat = stored_highest_hi_hat;
      highest_snare = stored_highest_snare;
      highest_kick = stored_highest_kick;
      highest_bass = stored_highest_bass;
      bool alternate_section4 = rand()%100 > 70;
      if (breakdown && double_middle)
      {
        bool breakdown_comes_first = rand()%100 > 50;
        if (breakdown_comes_first) {
          for (int i=0; i<breakdown_length; i++)
          {
            int section = 1;
            if (alternate_section4)
            {
              section = 1 + (i%2);
            }
            drum_arrangement_all[0][i+(2*intro_length)+middle_length] = highest_hi_hat + section;
            drum_arrangement_all[1][i+(2*intro_length)+middle_length] = highest_snare + section;
            drum_arrangement_all[2][i+(2*intro_length)+middle_length] = highest_kick + section;
            drum_arrangement_all[3][i+(2*intro_length)+middle_length] = -1;
            drum_arrangement_all[4][i+(2*intro_length)+middle_length] = 0;
            bass_arrangement_all[i+(2*intro_length)+middle_length] = highest_bass + section;
          }
          highest_hi_hat += 1;
          highest_snare += 1;
          highest_kick += 1;
          highest_bass += 1;
          stored_highest_hi_hat += 1;
          stored_highest_snare += 1;
          stored_highest_kick += 1;
          stored_highest_bass += 1;
          if (alternate_section4)
          {
            highest_hi_hat += 1;
            highest_snare += 1;
            highest_kick += 1;
            highest_bass += 1;
            stored_highest_hi_hat += 1;
            stored_highest_snare += 1;
            stored_highest_kick += 1;
            stored_highest_bass += 1;
          }

          for (int i=0; i<middle_length; i++)
          {
            int location = i+(2*intro_length)+middle_length+breakdown_length;
            drum_arrangement_all[0][location] =  drum_arrangement_all[0][i+intro_length];
            drum_arrangement_all[1][location] =  drum_arrangement_all[1][i+intro_length];
            drum_arrangement_all[2][location] =  drum_arrangement_all[2][i+intro_length];
            drum_arrangement_all[3][location] =  drum_arrangement_all[3][i+intro_length];
            drum_arrangement_all[4][location] =  drum_arrangement_all[4][i+intro_length];
            bass_arrangement_all[location] = bass_arrangement_all[i+intro_length];
          }
        } else {
          for (int i=0; i<middle_length; i++)
          {
            int location = i+(2*intro_length)+middle_length;
            drum_arrangement_all[0][location] =  drum_arrangement_all[0][i+intro_length];
            drum_arrangement_all[1][location] =  drum_arrangement_all[1][i+intro_length];
            drum_arrangement_all[2][location] =  drum_arrangement_all[2][i+intro_length];
            drum_arrangement_all[3][location] =  drum_arrangement_all[3][i+intro_length];
            drum_arrangement_all[4][location] =  drum_arrangement_all[4][i+intro_length];
            bass_arrangement_all[location] = bass_arrangement_all[i+intro_length];
          }
          for (int i=0; i<breakdown_length; i++)
          {
            int section = 1;
            if (alternate_section4)
            {
              section = 1 + (i%2);
            }
            int location = i+(2*intro_length)+(2*middle_length);
            drum_arrangement_all[0][location] = highest_hi_hat + section;
            drum_arrangement_all[1][location] = highest_snare + section;
            drum_arrangement_all[2][location] = highest_kick + section;
            drum_arrangement_all[3][location] = -1;
            drum_arrangement_all[4][location] = 0;
            bass_arrangement_all[location] = highest_bass + section;
          }
          highest_hi_hat += 1;
          highest_snare += 1;
          highest_kick += 1;
          highest_bass += 1;
          stored_highest_hi_hat += 1;
          stored_highest_snare += 1;
          stored_highest_kick += 1;
          stored_highest_bass += 1;
          if (alternate_section4)
          {
            highest_hi_hat += 1;
            highest_snare += 1;
            highest_kick += 1;
            highest_bass += 1;
            stored_highest_hi_hat += 1;
            stored_highest_snare += 1;
            stored_highest_kick += 1;
            stored_highest_bass += 1;
          }
        }
      } else if (breakdown && !double_middle) {
        for (int i=0; i<breakdown_length; i++)
        {
          int section = 1;
          if (alternate_section4)
          {
            section = 1 + (i%2);
          }
          drum_arrangement_all[0][i+(2*intro_length)+middle_length] = highest_hi_hat + 1;
          drum_arrangement_all[1][i+(2*intro_length)+middle_length] = highest_snare + 1;
          drum_arrangement_all[2][i+(2*intro_length)+middle_length] = highest_kick + 1;
          drum_arrangement_all[3][i+(2*intro_length)+middle_length] = -1;
          drum_arrangement_all[4][i+(2*intro_length)+middle_length] = 0;
          bass_arrangement_all[i+(2*intro_length)+middle_length] = highest_bass + 1;
        }
        highest_hi_hat += 1;
        highest_snare += 1;
        highest_kick += 1;
        highest_bass += 1;
        stored_highest_hi_hat += 1;
        stored_highest_snare += 1;
        stored_highest_kick += 1;
        stored_highest_bass += 1;
        if (alternate_section4)
        {
          highest_hi_hat += 1;
          highest_snare += 1;
          highest_kick += 1;
          highest_bass += 1;
          stored_highest_hi_hat += 1;
          stored_highest_snare += 1;
          stored_highest_kick += 1;
          stored_highest_bass += 1;
        }
      } else if (double_middle && !breakdown_length){
        for (int i=0; i<middle_length; i++)
        {
          int location = i+(2*intro_length)+middle_length;
          drum_arrangement_all[0][location] =  drum_arrangement_all[0][i+intro_length];
          drum_arrangement_all[1][location] =  drum_arrangement_all[1][i+intro_length];
          drum_arrangement_all[2][location] =  drum_arrangement_all[2][i+intro_length];
          drum_arrangement_all[3][location] =  drum_arrangement_all[3][i+intro_length];
          drum_arrangement_all[4][location] =  drum_arrangement_all[4][i+intro_length];
          bass_arrangement_all[location] = bass_arrangement_all[i+intro_length];
        }
      }
    } else {
      highest_hi_hat = stored_highest_hi_hat;
      highest_snare = stored_highest_snare;
      highest_kick = stored_highest_kick;
      highest_bass = stored_highest_bass;
      // stored_highest_hi_hat += 1;
      // stored_highest_snare += 1;
      // stored_highest_kick += 1;
      // stored_highest_bass += 1;
      bool alternate_section4 = rand()%100 > 70;
      if (breakdown && double_middle)
      {
        bool breakdown_comes_first = rand()%100 > 50;
        if (breakdown_comes_first) {
          for (int i=0; i<breakdown_length; i++)
          {
            drum_arrangement_all[0][i+intro_length+middle_length] = highest_hi_hat + 1;
            drum_arrangement_all[1][i+intro_length+middle_length] = highest_snare + 1;
            drum_arrangement_all[2][i+intro_length+middle_length] = highest_kick + 1;
            drum_arrangement_all[3][i+intro_length+middle_length] = -1;
            drum_arrangement_all[4][i+intro_length+middle_length] = 0;
            bass_arrangement_all[i+intro_length+middle_length] = highest_bass + 1;
          }
          highest_hi_hat += 1;
          highest_snare += 1;
          highest_kick += 1;
          highest_bass += 1;
          for (int i=0; i<middle_length; i++)
          {
            int location = i+intro_length+middle_length+breakdown_length;
            drum_arrangement_all[0][location] =  drum_arrangement_all[0][i+intro_length];
            drum_arrangement_all[1][location] =  drum_arrangement_all[1][i+intro_length];
            drum_arrangement_all[2][location] =  drum_arrangement_all[2][i+intro_length];
            drum_arrangement_all[3][location] =  drum_arrangement_all[3][i+intro_length];
            drum_arrangement_all[4][location] =  drum_arrangement_all[4][i+intro_length];
            bass_arrangement_all[location] = bass_arrangement_all[i+intro_length];
          }
        } else {
          for (int i=0; i<middle_length; i++)
          {
            int location = i+intro_length+middle_length;
            drum_arrangement_all[0][location] =  drum_arrangement_all[0][i+intro_length];
            drum_arrangement_all[1][location] =  drum_arrangement_all[1][i+intro_length];
            drum_arrangement_all[2][location] =  drum_arrangement_all[2][i+intro_length];
            drum_arrangement_all[3][location] =  drum_arrangement_all[3][i+intro_length];
            drum_arrangement_all[4][location] =  drum_arrangement_all[4][i+intro_length];
            bass_arrangement_all[location] = bass_arrangement_all[i+intro_length];
          }
          for (int i=0; i<breakdown_length; i++)
          {
            int location = i+intro_length+(2*middle_length);
            drum_arrangement_all[0][location] = highest_hi_hat + 1;
            drum_arrangement_all[1][location] = highest_snare + 1;
            drum_arrangement_all[2][location] = highest_kick + 1;
            drum_arrangement_all[3][location] = -1;
            drum_arrangement_all[4][location] = 0;
            bass_arrangement_all[location] = highest_bass + 1;
          }
          highest_hi_hat += 1;
          highest_snare += 1;
          highest_kick += 1;
          highest_bass += 1;
        }
      } else if (breakdown && !double_middle) {
        for (int i=0; i<breakdown_length; i++)
        {
          drum_arrangement_all[0][i+intro_length+middle_length] = highest_hi_hat + 1;
          drum_arrangement_all[1][i+intro_length+middle_length] = highest_snare + 1;
          drum_arrangement_all[2][i+intro_length+middle_length] = highest_kick + 1;
          drum_arrangement_all[3][i+intro_length+middle_length] = -1;
          drum_arrangement_all[4][i+intro_length+middle_length] = 0;
          bass_arrangement_all[i+intro_length+middle_length] = highest_bass + 1;
        }
        highest_hi_hat += 1;
        highest_snare += 1;
        highest_kick += 1;
        highest_bass += 1;
      } else if (double_middle && !breakdown_length){
        for (int i=0; i<middle_length; i++)
        {
          int location = i+intro_length+middle_length;
          drum_arrangement_all[0][location] =  drum_arrangement_all[0][i+intro_length];
          drum_arrangement_all[1][location] =  drum_arrangement_all[1][i+intro_length];
          drum_arrangement_all[2][location] =  drum_arrangement_all[2][i+intro_length];
          drum_arrangement_all[3][location] =  drum_arrangement_all[3][i+intro_length];
          drum_arrangement_all[4][location] =  drum_arrangement_all[4][i+intro_length];
          bass_arrangement_all[location] = bass_arrangement_all[i+intro_length];
        }
      }
    }
    std::cout << "made it past double intro part (946)"<< std::endl;
    for (int i=0; i<end_length; i++)
    {
      int location = (total_sections + i) - end_length;
      drum_arrangement_all[0][location] =  drum_arrangement_all[0][i];
      drum_arrangement_all[1][location] =  drum_arrangement_all[1][i];
      drum_arrangement_all[2][location] =  drum_arrangement_all[2][i];
      drum_arrangement_all[3][location] =  drum_arrangement_all[3][i];
      drum_arrangement_all[4][location] =  drum_arrangement_all[4][i];
      bass_arrangement_all[location] = bass_arrangement_all[i];
    }





    // int total_sections = 32;
    // int** key_arrangement = new int* [total_sections];
    // int* chord_arrangemnt = new int [total_sections];
    // int* bass_arrangement = new int [total_sections];
    // int* section_length = new int [total_sections];
    //
    // for (int i=0; i<total_sections; i++)
    // {
    //   key_arrangement[i] = new int [2];
    //   key_arrangement[i][0] = 5;
    //   key_arrangement[i][1] = 36;
    //   if (i >= 8 && i < 16)
    //   {
    //     key_arrangement[i][0] = 5;
    //     key_arrangement[i][1] = 43;
    //   }
    //   chord_arrangemnt[i] = 1;
    //   bass_arrangement[i] = 1 + (i%2);
    //   if (i%16 >= 4 && i%16 < 8) {
    //     bass_arrangement[i] = 3 + (i%2);
    //     chord_arrangemnt[i] = 2;
    //   }
    //   if (i >= 16 && i < 24) {
    //     bass_arrangement[i] = 5 + (i%2);
    //     chord_arrangemnt[i] = 3;
    //   }
    //   section_length[i] = 1;
    // }






    // int drum_arrangement_stand [5][32] = {
    //   // hi hat
    //   {0,0,1,1,2,2,2,2,1,1,1,1,  2,2,2,2,3,4,3,4,3,4,3,4,  3,4,3,4,1,1,1,1},
    //   // snare
    //   {0,0,1,1,2,2,2,2,1,1,1,1,  2,2,2,2,3,4,3,4,3,4,3,4, 1,2,1,2,1,1,1,1},
    //   // kick
    //   {0,0,1,1,2,2,2,2,1,1,1,1,  2,2,2,2,3,4,3,4,3,4,3,4, 1,2,1,2,1,1,1,1},
    //   // tom fills
    //   {-1,-1,-1,8,-1,-1,-1,8,-1,-1,-1,8, -1,4,8,12,-1,-1,-1,8,-1,-1,8,12, -1,-1,8,12,-1,-1,-1,8},
    //   // crash
    //   {0,0,0,0,2,0,0,0,1,0,0,0, 2,0,0,2,1,0,0,0,2,0,0,2, 1,0,0,0,1,0,1,2}
    // };

    // int** drum_arr = new int* [5];
    // for (int i=0; i<5; i++) {
    //   drum_arr[i] = new int [32];
    //   for (int j=0; j<32; j++)
    //   {
    //     drum_arr[i][j] = drum_arrangement_stand[i][j];
    //   }
    // }

    std::cout << "intro_length: " << intro_length << std::endl;
    std::cout << "middle_length: " << middle_length << std::endl;
    std::cout << "end_length: " << end_length << std::endl;
    std::cout << "breakdown_length: " << breakdown_length << std::endl;
    std::cout << "Total Sections: " << total_sections << std::endl;
    std::cout << "highest_bass: " << highest_bass << '\n' << std::endl;
    for (int i=0; i<total_sections; i++)
    {
      std::cout << bass_arrangement_all[i] << " ";
      if (i == intro_length-1)
      {
        std::cout << "   ";
      }
      if (i == (middle_length + intro_length-1)) {
        std::cout << "   ";
      }
    }
    std::cout << "\n\nHi_hat: " << std::endl;

    for (int i=0; i<total_sections; i++)
    {
      std::cout << drum_arrangement_all[0][i] << " ";
      if (i == intro_length-1)
      {
        std::cout << "   ";
      }
      if (i == (middle_length + intro_length-1)) {
        std::cout << "   ";
      }
    }

    std::cout << "\n\nkick: " << std::endl;

    for (int i=0; i<total_sections; i++)
    {
      std::cout << drum_arrangement_all[2][i] << " ";
      if (i == intro_length-1)
      {
        std::cout << "   ";
      }
      if (i == (middle_length + intro_length-1)) {
        std::cout << "   ";
      }
    }

    std::cout << "\n\nSnare: " << std::endl;

    for (int i=0; i<total_sections; i++)
    {
      std::cout << drum_arrangement_all[1][i] << " ";
      if (i == intro_length-1)
      {
        std::cout << "   ";
      }
      if (i == (middle_length + intro_length-1)) {
        std::cout << "   ";
      }
    }
    std::cout << "\n\n" << std::endl;

    std::cout << "alternate1 " << alternate_sections << std::endl;
    std::cout << "alternate2 " << alternate_section2 << std::endl;
    std::cout << "alternate3 " << alternate_section3 << std::endl;
    std::cout << "made it to drum creation (1018)"<< std::endl;


    int*** created_drums = drum_arrangement::create_tracks_from_arrangement(
      drum_arrangement_all,
      section_length_all,
      total_sections
    );

    std::cout << "made it to bass creation (1025)"<< std::endl;
    bass_arrangement::create_tracks_from_arrangement_and_chords(
      key_arrangement_all,
      chord_arrangement_all,
      bass_arrangement_all,
      section_length_all,
      total_sections,
      created_drums
    );

    std::cout << "done!"<< std::endl;
  }
}
