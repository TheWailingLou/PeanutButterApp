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

    bool alternate_sections = (rand()%100 > 50);
    bool alternate_section2 = (rand()%100 > 50);
    bool alternate_section3 = (rand()%100 > 50);

    if (intro_length == 1 && alternate_sections)
    {
      intro_length = 2;
    }

    int total_sections = ((intro_length*double_intro_mult)
      + (middle_length * double_middle_mult)
      + breakdown_length
      + end_length
    );

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


      for (int i=0; i<intro_length; i++)
      {
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

    int split = middle_length/2;
    int split2 = split/2 + ((1-(rand()%3))*(split/4));

    if (middle_length == 64)
    {
      split2 = split/2;
    }

    int current_note = starting_note;
    int current_mode = mode;

    for (int i=0; i<middle_length; i++)
    {
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
          if (i==split2 || i==split+split2)
          {
            current_mode = mode;
            current_note = starting_note;
          } else if ((i%split)%split2 >= 4) {
            current_mode = mode;
            current_note = starting_note + 7;
          }
          key_arrangement_all[i][0] = current_mode;
          key_arrangement_all[i][1] = current_note;

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
        } else {
          if (i==split || i==0)
          {
            current_mode = mode;
            current_note = starting_note;
          } else if (i%split >= 4) {
            current_mode = mode;
            current_note = starting_note + 7;
          }
          key_arrangement_all[i][0] = current_mode;
          key_arrangement_all[i][1] = current_note;

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
          //2
          if (i==split)
          {
            current_mode = mode;
            current_note = starting_note;
          } else if (i%split >= 4) {
            current_mode = mode;
            current_note = starting_note + 5;
          }
          key_arrangement_all[i][0] = current_mode;
          key_arrangement_all[i][1] = current_note;

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
        } else {
          if (i==0 || i == split)
          {
            current_mode = mode;
            current_note = starting_note;
          } else if (i%split >= 4) {
            current_mode = mode;
            current_note = starting_note + 7;
          }
          key_arrangement_all[i][0] = current_mode;
          key_arrangement_all[i][1] = current_note;

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

    int*** created_drums = drum_arrangement::create_tracks_from_arrangement(
      drum_arrangement_all,
      section_length_all,
      total_sections
    );

    bass_arrangement::create_tracks_from_arrangement_and_chords(
      key_arrangement_all,
      chord_arrangement_all,
      bass_arrangement_all,
      section_length_all,
      total_sections,
      created_drums
    );
  }
}
