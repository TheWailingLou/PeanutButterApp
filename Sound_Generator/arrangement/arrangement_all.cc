#include "arrangement_all.h"

namespace arrangement_all
{
  void create_tracks(int starting_note, int mode)
  {
    srand(time(NULL));

    std::cout << "Rand test: " << rand()%10 << " " << rand()%10 << std::endl;
    int main_start = 4*(rand()%3);
    // int breakdown_length = 4*(rand()%3);
    int end_length = 5 + (4*(rand()%3));

    std::cout << "(14) END_LENGTH " << end_length << std::endl;
    int main_sections = 12 + rand()%13;

    // int main_start = 0;
    // int end_length = 0;
    int breakdown_length = 0;

    int total_sections = main_start + (main_sections*4) + end_length;

    // set up all the sections

    int** drum_arrangement = new int* [5];
    for (int i=0; i<5; i++)
    {
      drum_arrangement[i] = new int [total_sections];
    }
    int** key_arrangement = new int* [total_sections];
    int* chord_arrangement = new int [total_sections];
    int* bass_arrangement = new int [total_sections];
    int* section_length = new int [total_sections];
    for (int i=0; i<total_sections+1; i++)
    {
      drum_arrangement[0][i] = 0;
      drum_arrangement[1][i] = 0;
      drum_arrangement[2][i] = 0;
      drum_arrangement[3][i] = -1;
      drum_arrangement[4][i] = 0;

      key_arrangement[i] = new int [2];
      key_arrangement[i][0] = mode;
      key_arrangement[i][1] = starting_note;

      chord_arrangement[i] = 1;
      bass_arrangement[i] = 0;
      section_length[i] = 1;
    }
    bool alternate_bass_1 = true;
    bool alternate_chords_1 = (rand()%100) > 50;
    bool alternate_hi_hat_1 = (rand()%100) > 50;
    bool alternate_kick_1 = (rand()%100) > 50;
    bool alternate_snare_1 = (rand()%100) > 50;
    for (int i=0; i<4; i++)
    {
      if (alternate_hi_hat_1)
      {
        drum_arrangement[0][i+main_start] = 1 + (i%2);
      } else {
        drum_arrangement[0][i+main_start] = 1;
      }
      if (alternate_snare_1)
      {
        drum_arrangement[1][i+main_start] = 1 + (i%2);
      } else {
        drum_arrangement[1][i+main_start] = 1;
      }
      if (alternate_kick_1)
      {
        drum_arrangement[2][i+main_start] = 1 + (i%2);
      } else {
        drum_arrangement[2][i+main_start] = 1;
      }

      if (alternate_bass_1)
      {
        bass_arrangement[i+main_start] = 1 + (i%2);
        if (alternate_chords_1)
        {
          chord_arrangement[i+main_start] = 1 + (i%2);
        }
      } else {
        bass_arrangement[i+main_start] = 1;
        chord_arrangement[i+main_start] = 1;
      }
    }

    for (int section=1; section<main_sections; section++)
    {
      int root_section = mod_four_bars_bass(key_arrangement, chord_arrangement, bass_arrangement, section, main_start);
      mod_four_bars_drums(drum_arrangement, section, main_start, root_section);
    }

    intro_bars(bass_arrangement, drum_arrangement, main_start);

    int crash = 0;

    for (int i=1; i<main_sections; i++)
    {
      int riff1 = bass_arrangement[i*4 + main_start];
      int riff2 = bass_arrangement[i*4 + main_start + 1];
      int compare1 = bass_arrangement[i*4 + main_start - 2];
      int compare2 = bass_arrangement[i*4 + main_start - 1];
      if (compare1 != riff1 || compare2 != riff2)
      {
        drum_arrangement[4][i*4 + main_start] = (crash%2) + 1;
        crash += 1;
        drum_arrangement[3][i*4 + main_start - 1] = 4 + (4*(rand()%3));
      }

      int note1 = key_arrangement[i*4 + main_start][1];
      int note2 = key_arrangement[i*4 + main_start+1][1];
      int mode1 = key_arrangement[i*4 + main_start][0];
      int mode2 = key_arrangement[i*4 + main_start+1][0];

      int comp_note1 = key_arrangement[i*4 + main_start-2][1];
      int comp_note2 = key_arrangement[i*4 + main_start-1][1];
      int comp_mode1 = key_arrangement[i*4 + main_start-2][0];
      int comp_mode2 = key_arrangement[i*4 + main_start-1][0];

      bool note_diff = (note1 != comp_note1 || note2 != comp_note2);
      bool mode_diff = (mode1 != comp_mode1 || mode2 != comp_mode2);
      if ((note_diff || mode_diff) && (rand()%100 > 50))
      {
        drum_arrangement[4][i*4 + main_start] = (crash%2) + 1;
        crash += 1;
        drum_arrangement[3][i*4 + main_start - 1] = 4 + (4*(rand()%3));
      }
    }

    bool tom_fill_to_start = (main_start > 0) && (rand()%100 > 60);
    bool crash_to_start = (main_start > 0) && (tom_fill_to_start) && (rand()%100 > 60);
    if (tom_fill_to_start)
    {
      drum_arrangement[3][main_start - 1] = 4 + (4*(rand()%3));
    }
    if (crash_to_start)
    {
      drum_arrangement[4][main_start] = 1 + (rand()%2);
    }

    std::cout << "\nBASS: " << std::endl;
    for (int i=0; i<total_sections; i++)
    {
      std::cout << bass_arrangement[i] << " ";
    }
    std::cout << '\n\n' << std::endl;

    std::cout << "(129) END_LENGTH " << end_length << std::endl;
    end_bars (bass_arrangement, key_arrangement, drum_arrangement, end_length, total_sections, main_start);

    std::cout << "finishing generating ending" << std::endl;

    int*** all_drum_tracks = drum_arrangement::create_tracks_from_arrangement(
      drum_arrangement,
      section_length,
      total_sections
    );

    std::cout << "MAKING IT PAST DRUMS..." << std::endl;

    bass_arrangement::create_tracks_from_arrangement_and_chords(
      key_arrangement,
      chord_arrangement,
      bass_arrangement,
      section_length,
      total_sections,
      all_drum_tracks
    );

    std::cout << "MAKING IT PAST BASS... " << std::endl;
  }

  void intro_bars (int* bass_arrangement, int** drum_arrangement, int main_start)
  {
    std::cout << "\n\n\n\nINTRO LENGTH: " << main_start << "\n\n\n\n" << std::endl;
    if (main_start == 0)
    {
      return;
    }
    int what_intro = rand()%15;
    if (what_intro == 0 || what_intro == 10 || what_intro == 14)
    {
      std::cout << "Intro 1" << std::endl;
      for (int i=0; i<main_start; i++) {
        bass_arrangement[i] = bass_arrangement[(i%4)+main_start];
        if (i >= 4) {
          drum_arrangement[0][i] = drum_arrangement[0][(i%4)+main_start];
        }
      }

    } else if (what_intro == 1) {
      std::cout << "Intro 2" << std::endl;
      for (int i=0; i<main_start; i++) {
        drum_arrangement[0][i] = drum_arrangement[0][(i%4)+main_start];
        if (i >= 4) {
          bass_arrangement[i] = bass_arrangement[(i%4)+main_start];
        }
      }
    } else if (what_intro == 2) {
      std::cout << "Intro 3" << std::endl;
      for (int i=0; i<main_start; i++) {
        drum_arrangement[2][i] = drum_arrangement[2][(i%4)+main_start];
        if (i >= 4) {
          bass_arrangement[i] = bass_arrangement[(i%4)+main_start];
        }
      }
    } else if (what_intro == 3) {
      std::cout << "Intro 4" << std::endl;
      for (int i=0; i<main_start; i++) {
        drum_arrangement[2][i] = drum_arrangement[2][(i%4)+main_start];
        if (i >= 4) {
          drum_arrangement[0][i] = drum_arrangement[2][(i%4)+main_start];
        }
      }
    } else if (what_intro == 4 || what_intro == 11) {
      std::cout << "Intro 5" << std::endl;
      for (int i=0; i<main_start; i++) {
        bass_arrangement[i] = bass_arrangement[(i%4)+main_start];
        if (i >= 4) {
          drum_arrangement[2][i] = drum_arrangement[2][(i%4)+main_start];
          drum_arrangement[0][i] = drum_arrangement[2][(i%4)+main_start];
        }
      }
    } else if (what_intro == 5) {
      std::cout << "Intro 6" << std::endl;
      for (int i=0; i<main_start; i++) {
        drum_arrangement[2][i] = drum_arrangement[2][(i%4)+main_start];
        drum_arrangement[0][i] = drum_arrangement[2][(i%4)+main_start];
        if (i >= 4) {
          bass_arrangement[i] = bass_arrangement[(i%4)+main_start];
        }
      }
    } else if (what_intro == 6) {
      std::cout << "Intro 7" << std::endl;
      for (int i=0; i<main_start; i++) {
        drum_arrangement[2][i] = drum_arrangement[2][(i%4)+main_start];
        drum_arrangement[0][i] = drum_arrangement[2][(i%4)+main_start];
        drum_arrangement[1][i] = drum_arrangement[1][(i%4)+main_start];
      }
    } else if (what_intro == 7 || what_intro == 12) {
      std::cout << "Intro 8" << std::endl;
      for (int i=0; i<main_start; i++) {
        bass_arrangement[i] = bass_arrangement[(i%4)+main_start];
        if (i >= 4) {
          drum_arrangement[2][i] = drum_arrangement[0][(i%4)+main_start];
        }
      }
    } else if (what_intro == 8 || what_intro == 13) {
      std::cout << "Intro 9" << std::endl;
      for (int i=0; i<main_start; i++) {
        bass_arrangement[i] = bass_arrangement[(i%4)+main_start];
      }
    } else if (what_intro == 9) {
      std::cout << "Intro 10" << std::endl;
      for (int i=0; i<main_start; i++) {
        drum_arrangement[2][i] = drum_arrangement[2][(i%4)+main_start];
        drum_arrangement[0][i] = drum_arrangement[2][(i%4)+main_start];
        if (i >= 4) {
          drum_arrangement[1][i] = drum_arrangement[0][(i%4)+main_start];
        }
      }
    }
  }

  void end_bars (int* bass_arrangement, int** key_arrangement, int** drum_arrangement, int end_length, int total_length, int main_start)
  {
    std::cout << "\n\nKEY ARR PROBLEM ??? k: " << key_arrangement[total_length-1][1] << std::endl;
    std::cout << "total_length -1: " << total_length - 1 << std::endl;
    std::cout << "\n\n\n\nEND LENGTH: " << end_length << "\n\n\n\n" << std::endl;
    // if (end_length == 0)
    // {
    //   return;
    // }
    int what_end = rand()%5;
    int current_bar = total_length-end_length;
    for (int i=0; i<end_length-1; i++)
    {
      bass_arrangement[current_bar+i] = bass_arrangement[main_start+(i%4)];
      drum_arrangement[0][current_bar+i] = bass_arrangement[main_start+(i%4)];
      drum_arrangement[1][current_bar+i] = bass_arrangement[main_start+(i%4)];
      drum_arrangement[2][current_bar+i] = bass_arrangement[main_start+(i%4)];
      drum_arrangement[3][current_bar+i] = -1;
      drum_arrangement[4][current_bar+i] = 0;
    }
    bass_arrangement[total_length-1] = 0;
    drum_arrangement[0][total_length-1] = 0;
    drum_arrangement[1][total_length-1] = 0;
    drum_arrangement[2][total_length-1] = 0;
    drum_arrangement[3][total_length-1] = -1;
    drum_arrangement[4][total_length-1] = 0;
    if (what_end == 0)
    {
      std::cout << "Ending 1" << std::endl;
      // drum intensify;
      for (int i=0; i<end_length-1; i++)
      {

        if (i >= 4)
        {
          if (i%2 == 0)
          {
            drum_arrangement[4][current_bar+i] = 2;
          } else {
            drum_arrangement[3][current_bar+i] = 4;
          }
        }

        if (i >= 8)
        {
          if (i%2 == 0 || i%4==3)
          {
            drum_arrangement[4][current_bar+i] = 2;
          }
          if (i%4 > 0)
          {
            drum_arrangement[3][current_bar+i] = 4;
          }
        }
        if (i%4 == 0)
        {
          drum_arrangement[4][current_bar+i] = 1;
        } else if (i%4 == 3) {
          drum_arrangement[3][current_bar+i] = 8;
        }
      }
      drum_arrangement[4][total_length-1] = 1;
      bass_writer::final_note(key_arrangement[total_length-1][1], 16, 1, total_length-1);
    } else if (what_end == 1) {
      // drum intensify2;
      std::cout << "Ending 2" << std::endl;
      for (int i=0; i<end_length-1; i++)
      {

        if (i >= 4)
        {
          if (i%2 == 0)
          {
            drum_arrangement[4][current_bar+i] = 2;
          } else {
            drum_arrangement[3][current_bar+i] = 4;
          }
        }

        if (i >= 8)
        {
          if (i%2 == 0 || i%4==3)
          {
            drum_arrangement[4][current_bar+i] = 2;
          }
          if (i%4 > 0)
          {
            drum_arrangement[3][current_bar+i] = 4;
          }
        }
        if (i%4 == 0)
        {
          drum_arrangement[4][current_bar+i] = 1;
        } else if (i%4 == 3) {
          drum_arrangement[3][current_bar+i] = 8;
        }
      }
      drum_arrangement[4][total_length-1] = 0;
      std::cout << "\n\nMaking it past filling in of ending??\n\n" << std::endl;
      if (rand()%2 == 0)
      {
        int snare_end [16] = {1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0};
        snare_writer::write_from_array_at_bar(snare_end, total_length-1);
        bass_writer::final_note(key_arrangement[total_length-1][1], 2, 1, total_length-1);
      } else {
        int snare_end [16] = {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        snare_writer::write_from_array_at_bar(snare_end, total_length-1);
        bass_writer::final_note(key_arrangement[total_length-1][1], 1, 1, total_length-1);
      }
      std::cout << "\n\nMaking it past filling in of ending??\n\n" << std::endl;
    } else if (what_end == 2) {

      std::cout << "Ending 3" << std::endl;
      // bass_solo_after4
      for (int i=0; i<end_length-1; i++)
      {
        if (i%4 == 0)
        {
          drum_arrangement[4][current_bar+i] = 2;
        } else if (i%4 == 3) {
          drum_arrangement[3][current_bar+i] = 6;
        }
        if (i >= 4)
        {
          drum_arrangement[0][current_bar+i] = 0;
          drum_arrangement[1][current_bar+i] = 0;
          drum_arrangement[2][current_bar+i] = 0;
          drum_arrangement[3][current_bar+i] = -1;
          drum_arrangement[4][current_bar+i] = 0;
        }
        if (i == 4) {
          drum_arrangement[4][total_length-1] = 1;
        }
      }

      bass_writer::final_note(key_arrangement[total_length-1][1], 8, 1, total_length-1);
      std::cout << "\n\nMaking it past filling in of ending??\n\n" << std::endl;
    } else if (what_end == 3) {
      std::cout << "Ending 4" << std::endl;
      // bass_solo_after8
      for (int i=0; i<end_length-1; i++)
      {
        if (i%4 == 0)
        {
          drum_arrangement[4][current_bar+i] = 2;
        } else if (i%4 == 3) {
          drum_arrangement[3][current_bar+i] = 6;
        }
        if (i >= 8)
        {
          drum_arrangement[0][current_bar+i] = 0;
          drum_arrangement[1][current_bar+i] = 0;
          drum_arrangement[2][current_bar+i] = 0;
          drum_arrangement[3][current_bar+i] = -1;
          drum_arrangement[4][current_bar+i] = 0;
        }
        if (i == 8) {
          drum_arrangement[4][current_bar+i] = 1;
        }
      }
      if (rand()%2 == 0)
      {
        bass_writer::final_note(key_arrangement[total_length-1][1], 8, 1, total_length-1);
      } else {
        bass_writer::final_note(key_arrangement[total_length-1][1], 2, 1, total_length-1);
      }

      std::cout << "\n\nMaking it past filling in of ending??\n\n" << std::endl;
    } else if (what_end == 4) {
      std::cout << "Ending 5" << std::endl;
      // bass_solo_entire
      for (int i=0; i<end_length-1; i++)
      {
        drum_arrangement[0][current_bar+i] = 0;
        drum_arrangement[1][current_bar+i] = 0;
        drum_arrangement[2][current_bar+i] = 0;
        drum_arrangement[3][current_bar+i] = -1;
        drum_arrangement[4][current_bar+i] = 0;
      }
      if (rand()%2 == 0)
      {
        bass_writer::final_note(key_arrangement[total_length-1][1], 8, 1, total_length-1);
      } else {
        bass_writer::final_note(key_arrangement[total_length-1][1], 2, 1, total_length-1);
      }
      std::cout << "\n\nMaking it past filling in of ending??\n\n" << std::endl;
    }
  }

  int mod_four_bars_bass (int** key_arrangement, int* chord_arrangement, int* bass_arrangement, int current_section, int main_start)
  {
    int mod_what = rand()%13;
    int root_section = main_start + (rand()%current_section)*4;
    std::cout << "\nROOT SECTION: " << root_section << "\n" << std::endl;

    int current_bar = (current_section*4) + main_start;

    std::cout << "\nCURRENT_BAR: " << current_bar << "\n" << std::endl;
    if (mod_what == 0 || mod_what == 3 || mod_what == 6)
    {
      for (int i=0; i<4; i++)
      {
        key_arrangement[i+current_bar][0] = key_arrangement[i+root_section][0];
        key_arrangement[i+current_bar][1] = key_arrangement[i+root_section][1];
        bass_arrangement[i+current_bar] = bass_arrangement[i+root_section];
        chord_arrangement[i+current_bar] = chord_arrangement[i+root_section];
      }
    } else if (mod_what == 1 || mod_what == 4 || mod_what == 7) {
      bool mod_key = (rand()%100) > 50;
      bool normal_mod = (rand()%100) > 7;
      for (int i=0; i<4; i++)
      {
        if (mod_key)
        {
          if (normal_mod)
          {
            std::cout << "DOING A NORMAL MOD " << std::endl;
            int current_mode = key_arrangement[i+root_section][0];
            if (current_mode == 5)
            {
              key_arrangement[i+current_bar][0] = 0;
              key_arrangement[i+current_bar][1] = key_arrangement[i+root_section][1] + 3;
            } else if (current_mode == 0) {
              key_arrangement[i+current_bar][0] = 5;
              key_arrangement[i+current_bar][1] = key_arrangement[i+root_section][1] + 9;
            } else {
              key_arrangement[i+current_bar][0] = (current_mode + 4)%7;
              key_arrangement[i+current_bar][1] = key_arrangement[i+root_section][1];
            }
          } else {
            std::cout << "\n\n\nWEIRD MOD!\n\n " << std::endl;
            if (rand()%100 > 40)
            {
              key_arrangement[i+current_bar][0] = key_arrangement[i+current_bar][0] + ((3*(i+1))%7);
              key_arrangement[i+current_bar][1] = key_arrangement[i+root_section][1];
            } else {
              key_arrangement[i+current_bar][0] = rand()%7;
              key_arrangement[i+current_bar][1] = key_arrangement[i+root_section][1];
            }

          }
        } else {
          if (normal_mod)
          {
            key_arrangement[i+current_bar][0] = key_arrangement[i+root_section][0];
            key_arrangement[i+current_bar][1] = key_arrangement[i+root_section][1] + 7;
          } else {
            if (rand()%100 > 40)
            {
              key_arrangement[i+current_bar][0] = key_arrangement[i+root_section][0];
              key_arrangement[i+current_bar][1] = key_arrangement[i+root_section][1] + (((i+1)*2)%12);
            } else {
              key_arrangement[i+current_bar][0] = key_arrangement[i+root_section][0];
              key_arrangement[i+current_bar][1] = key_arrangement[i+root_section][1] + (rand()%12);
            }

            std::cout << "\n\n\nWEIRD MOD!\n\n " << std::endl;
          }
        }
        bass_arrangement[i+current_bar] = bass_arrangement[i+root_section];
        chord_arrangement[i+current_bar] = chord_arrangement[i+root_section];
      }
    } else if (mod_what == 2 || mod_what == 5 || (mod_what >= 8 && mod_what <= 11)) {


      bool mod_chords_too = (rand()%100) > 50;
      // bool alternate_section = (rand()%100) > 50;
      for (int i=0; i<4; i++)
      {
        key_arrangement[i+current_bar][0] = key_arrangement[i+root_section][0];
        key_arrangement[i+current_bar][1] = key_arrangement[i+root_section][1];
        bass_arrangement[i+current_bar] = bass_arrangement[i+root_section] + 2;
        if (mod_chords_too) {
          chord_arrangement[i+current_bar] = chord_arrangement[i+root_section] + 2;
        } else {
          chord_arrangement[i+current_bar] = chord_arrangement[i+root_section];
        }
      }
    } else {
      bool mod_key = (rand()%100) > 50;
      bool normal_mod = (rand()%100) > 7;
      bool mod_chords_too = (rand()%100) > 50;
      for (int i=0; i<4; i++)
      {

        bass_arrangement[i+current_bar] = bass_arrangement[i+root_section] + 2;
        if (mod_chords_too) {
          chord_arrangement[i+current_bar] = chord_arrangement[i+root_section] + 2;
        } else {
          chord_arrangement[i+current_bar] = chord_arrangement[i+root_section];
        }

        if (mod_key)
        {
          if (normal_mod)
          {
            int current_mode = key_arrangement[i+root_section][0];
            if (current_mode == 5)
            {
              key_arrangement[i+current_bar][0] = 0;
              key_arrangement[i+current_bar][1] = key_arrangement[i+root_section][1] + 3;
            } else if (current_mode == 0) {
              key_arrangement[i+current_bar][0] = 5;
              key_arrangement[i+current_bar][1] = key_arrangement[i+root_section][1] + 9;
            } else {
              key_arrangement[i+current_bar][0] = (current_mode + 4)%7;
              key_arrangement[i+current_bar][1] = key_arrangement[i+root_section][1];
            }
          } else {
            key_arrangement[i+current_bar][0] = rand()%7;
            key_arrangement[i+current_bar][1] = key_arrangement[i+root_section][1];
          }
        } else {
          if (normal_mod)
          {
            key_arrangement[i+current_bar][0] = key_arrangement[i+root_section][0];
            key_arrangement[i+current_bar][1] = key_arrangement[i+root_section][1] + 7;
          } else {
            key_arrangement[i+current_bar][0] = key_arrangement[i+root_section][0];
            key_arrangement[i+current_bar][1] = key_arrangement[i+root_section][1] + (rand()%12);
          }
        }
      }
    }
    return root_section;
  }

  void mod_four_bars_drums (int** drum_arrangement, int current_section, int main_start, int root_section)
  {

    if (rand()%100 > 70)
    {
      root_section = main_start + (rand()%current_section)*4;
    }
    int current_bar = (current_section*4) + main_start;

    int mod_what = rand()%15;

    for (int i=0; i<4; i++)
    {
      if (mod_what == 0 || mod_what == 7 || mod_what == 11)
      {
        drum_arrangement[0][i+current_bar] = drum_arrangement[0][i+root_section];
        drum_arrangement[1][i+current_bar] = drum_arrangement[1][i+root_section];
        drum_arrangement[2][i+current_bar] = drum_arrangement[2][i+root_section];
      } else if (mod_what == 1 || mod_what == 8 || mod_what == 12) {
        drum_arrangement[0][i+current_bar] = drum_arrangement[0][i+root_section] + 2;
        drum_arrangement[1][i+current_bar] = drum_arrangement[1][i+root_section];
        drum_arrangement[2][i+current_bar] = drum_arrangement[2][i+root_section];
      } else if (mod_what == 2) {
        drum_arrangement[0][i+current_bar] = drum_arrangement[0][i+root_section];
        drum_arrangement[1][i+current_bar] = drum_arrangement[1][i+root_section] + 2;
        drum_arrangement[2][i+current_bar] = drum_arrangement[2][i+root_section];
      } else if (mod_what == 3 || mod_what == 9) {
        drum_arrangement[0][i+current_bar] = drum_arrangement[0][i+root_section];
        drum_arrangement[1][i+current_bar] = drum_arrangement[1][i+root_section];
        drum_arrangement[2][i+current_bar] = drum_arrangement[2][i+root_section] + 2;
      } else if (mod_what == 4 || mod_what == 13) {
        drum_arrangement[0][i+current_bar] = drum_arrangement[0][i+root_section] + 2;
        drum_arrangement[1][i+current_bar] = drum_arrangement[1][i+root_section] + 2;
        drum_arrangement[2][i+current_bar] = drum_arrangement[2][i+root_section];
      } else if (mod_what == 5 || mod_what == 10) {
        drum_arrangement[0][i+current_bar] = drum_arrangement[0][i+root_section] + 2;
        drum_arrangement[1][i+current_bar] = drum_arrangement[1][i+root_section];
        drum_arrangement[2][i+current_bar] = drum_arrangement[2][i+root_section] + 2;
      } else if (mod_what == 6) {
        drum_arrangement[0][i+current_bar] = drum_arrangement[0][i+root_section];
        drum_arrangement[1][i+current_bar] = drum_arrangement[1][i+root_section] + 2;
        drum_arrangement[2][i+current_bar] = drum_arrangement[2][i+root_section] + 2;
      } else {
        drum_arrangement[0][i+current_bar] = drum_arrangement[0][i+root_section] + 2;
        drum_arrangement[1][i+current_bar] = drum_arrangement[1][i+root_section] + 2;
        drum_arrangement[2][i+current_bar] = drum_arrangement[2][i+root_section] + 2;
      }
    }
  }
}