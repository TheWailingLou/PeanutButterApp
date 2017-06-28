#include "music_gen.h"

namespace music_gen
{
  int** generate_bar_from_chords(int** chords, int octave)
  {
    int* current_chord = chords[0];
    int current_chord_duration = current_chord[0];
    int note_remaining_duration = 0;
    bool teenth_lock = false;
    bool eighth_lock = false;
    bool quarter_lock = false;
    bool half_lock = false;

    int** teenth_array = new int* [16];
    for (int i=0; i<16; i++)
    {
      teenth_array[i] = new int [2];

      if (chords[i][0] != -1) {
        current_chord = chords[i];
        current_chord_duration = current_chord[0];
        teenth_lock = false;
        eighth_lock = false;
        quarter_lock = false;
        half_lock = false;
      }

      if (note_remaining_duration > 0) {
        teenth_array[i][0] = -1;
        teenth_array[i][1] = 1;
      } else {
        int note_index = 1+(rand()%6);
        int note = current_chord[note_index] + (octave * 12);
        int duration;

        int lock_prob = rand()%100;

        if (lock_prob > 92)
        {
          half_lock = true;
          quarter_lock = false;
          eighth_lock = false;
          teenth_lock = false;
        } else if (lock_prob <= 92 && lock_prob > 77) {
          half_lock = false;
          quarter_lock = true;
          eighth_lock = false;
          teenth_lock = false;
        } else if (lock_prob <= 20 && lock_prob > 7) {
          half_lock = false;
          quarter_lock = false;
          eighth_lock = true;
          teenth_lock = false;
        } else if (lock_prob <= 7) {
          half_lock = false;
          quarter_lock = false;
          eighth_lock = false;
          teenth_lock = true;
        }

        if (half_lock) {
            duration = 8;
        } else if (quarter_lock) {
          duration = 4;
        } else if (eighth_lock) {
          duration = 2;
        } else if (teenth_lock) {
          duration = 1;
        } else {
          int duration_prob = rand()%100;
          if (duration_prob < 50) {
            duration = 2;
          } else if (duration_prob >= 50 && duration_prob < 70) {
            duration = 4;
          } else if (duration_prob >= 70 && duration_prob < 85) {
            duration = 1;
          } else {
            duration = rand()%current_chord_duration + 1;
          }
        }

        if (duration > current_chord_duration) {
          duration = current_chord_duration;
        }

        if (rand()%100 < 10 && !eighth_lock && !teenth_lock && !half_lock && !quarter_lock)
        {
          note = -1;
          duration = 1;
        }

        teenth_array[i][0] = note;
        teenth_array[i][1] = duration;

        note_remaining_duration = duration;
      }
      current_chord_duration -= 1;
      note_remaining_duration -= 1;
    }

    return teenth_array;
  }

  int** generate_bar_from_chords_and_drums(int* kick, int* snare, int* hi_hat, int** chords, int octave)
  {
    int* current_chord = chords[0];
    int current_chord_duration = current_chord[0];
    int note_remaining_duration = 0;
    bool teenth_lock = false;
    bool eighth_lock = false;
    bool quarter_lock = false;
    bool half_lock = false;

    int** teenth_array = new int* [16];
    for (int i=0; i<16; i++)
    {
      teenth_array[i] = new int [2];

      if (chords[i][0] != -1) {
        current_chord = chords[i];
        current_chord_duration = current_chord[0];
        teenth_lock = false;
        eighth_lock = false;
        quarter_lock = false;
        half_lock = false;
      }

      if (note_remaining_duration > 0) {
        teenth_array[i][0] = -1;
        teenth_array[i][1] = 1;
      } else {
        int duration;
        int note;

        int lock_prob = rand()%100;

        if (lock_prob > 92)
        {
          half_lock = true;
          quarter_lock = false;
          eighth_lock = false;
          teenth_lock = false;
        } else if (lock_prob <= 92 && lock_prob > 77) {
          half_lock = false;
          quarter_lock = true;
          eighth_lock = false;
          teenth_lock = false;
        } else if (lock_prob <= 20 && lock_prob > 7) {
          half_lock = false;
          quarter_lock = false;
          eighth_lock = true;
          teenth_lock = false;
        } else if (lock_prob <= 7) {
          half_lock = false;
          quarter_lock = false;
          eighth_lock = false;
          teenth_lock = true;
        }

        if (half_lock) {
            duration = 8;
        } else if (quarter_lock) {
          duration = 4;
        } else if (eighth_lock) {
          duration = 2;
        } else if (teenth_lock) {
          duration = 1;
        } else {
          int duration_prob = rand()%100;
          if (duration_prob < 50) {
            duration = 2;
          } else if (duration_prob >= 50 && duration_prob < 70) {
            duration = 4;
          } else if (duration_prob >= 70 && duration_prob < 85) {
            duration = 1;
          } else {
            duration = rand()%current_chord_duration + 1;
          }
        }

        if (duration > current_chord_duration) {
          duration = current_chord_duration;
        }

        if (kick[i] == 0 && snare[i] == 0 && hi_hat[i] != 2)
        {
          if (hi_hat[i] == 1 || rand()%100 > 70)
          {
            int note_index = 1+(rand()%6);
            note = current_chord[note_index] + (octave * 12);
          } else {
            note = -1;
            duration = 1;
          }
        } else {
          // do snare and kick and open_hi_hat hit stuff here.
          bool kick_snare = (kick[i] != 0 && snare[i] !=0);
          bool kick_hat = (kick[i] != 0 && hi_hat[i] == 2);
          bool snare_hat = (snare[i] !=0 && hi_hat[i] == 2);

          if (kick_snare || kick_hat || snare_hat) {
            int note_index;
            if (rand()%100 > 50) {
              note_index = 1 + (2*(rand()%2));
            } else {
              note_index = 1 + rand()%3;
            }
            note = current_chord[note_index] + (octave * 12);
          } else {
            if (hi_hat[i] == 2) {
              int note_index;
              if (rand()%100 > 30) {
                note_index = 3;
              } else {
                note_index = 1 + rand()%6;
              }
              note = current_chord[note_index] + (octave * 12);
            } else if (snare[i] != 0) {
              int note_index;
              if (rand()%100 > 50) {
                note_index = 1;
              } else {
                note_index = 1 + (2*(rand()%2));
              }
              note = current_chord[note_index] + (octave * 12);
            } else { // kick
              int note_index;
              if (rand()%100 > 30) {
                note_index = 1 + (2*(rand()%2));
              } else {
                note_index = 1 + rand()%3;
              }
              note = current_chord[note_index] + (octave * 12);
            }
          }
        }
        teenth_array[i][0] = note;
        teenth_array[i][1] = duration;
        note_remaining_duration = duration;
      }
      current_chord_duration -= 1;
      note_remaining_duration -= 1;
    }
    return teenth_array;
  }


  int** stick_to_root(int* kick, int* snare, int* hi_hat, int** chords, int octave)
  {
    int* current_chord = chords[0];
    int current_chord_duration = current_chord[0];
    int note_remaining_duration = 0;
    bool teenth_lock = false;
    bool eighth_lock = false;
    bool quarter_lock = false;
    bool half_lock = false;

    int** teenth_array = new int* [16];
    for (int i=0; i<16; i++)
    {
      if (chords[i][0] != -1) {
        current_chord = chords[i];
        current_chord_duration = current_chord[0];
        teenth_lock = false;
        eighth_lock = false;
        quarter_lock = false;
        half_lock = false;
      }
      teenth_array[i] = new int [2];

      if (note_remaining_duration > 0) {
        teenth_array[i][0] = -1;
        teenth_array[i][1] = 1;
      } else {
        int duration;
        int note;

        int lock_prob = rand()%100;

        if (lock_prob > 92)
        {
          half_lock = true;
          quarter_lock = false;
          eighth_lock = false;
          teenth_lock = false;
        } else if (lock_prob <= 92 && lock_prob > 77) {
          half_lock = false;
          quarter_lock = true;
          eighth_lock = false;
          teenth_lock = false;
        } else if (lock_prob <= 20 && lock_prob > 7) {
          half_lock = false;
          quarter_lock = false;
          eighth_lock = true;
          teenth_lock = false;
        } else if (lock_prob <= 7) {
          half_lock = false;
          quarter_lock = false;
          eighth_lock = false;
          teenth_lock = true;
        }

        if (half_lock) {
            duration = 8;
        } else if (quarter_lock) {
          duration = 4;
        } else if (eighth_lock) {
          duration = 2;
        } else if (teenth_lock) {
          duration = 1;
        } else {
          int duration_prob = rand()%100;
          if (duration_prob < 50) {
            duration = 2;
          } else if (duration_prob >= 50 && duration_prob < 70) {
            duration = 4;
          } else if (duration_prob >= 70 && duration_prob < 85) {
            duration = 1;
          } else {
            duration = rand()%current_chord_duration + 1;
          }
        }

        if (duration > current_chord_duration) {
          duration = current_chord_duration;
        }

        if (kick[i] == 0 && snare[i] == 0 && hi_hat[i] != 2)
        {
          if (hi_hat[i] == 1 || rand()%100 > 70)
          {
            int note_index = 1+(2*(rand()%2)); // 1 or 5;
            note = current_chord[note_index] + (octave * 12);
          } else {
            note = -1;
            duration = 1;
          }
        } else {
          // do snare and kick and open_hi_hat hit stuff here.
          bool kick_snare = (kick[i] != 0 && snare[i] !=0);
          bool kick_hat = (kick[i] != 0 && hi_hat[i] == 2);
          bool snare_hat = (snare[i] !=0 && hi_hat[i] == 2);

          if (kick_snare || kick_hat || snare_hat) {
            int note_index;
            if (rand()%100 > 50) {
              note_index = 1 + (2*(rand()%2));
            } else {
              note_index = 1;
            }
            note = current_chord[note_index] + (octave * 12);
          } else {
            if (hi_hat[i] == 2) {
              int note_index;
              if (rand()%100 > 30) {
                note_index = 1;
              } else {
                note_index = 3;
              }
              note = current_chord[note_index] + (octave * 12);
            } else if (snare[i] != 0) {
              int note_index;
              if (rand()%100 > 50) {
                note_index = 1;
              } else {
                note_index = 1 + (2*(rand()%2));
              }
              note = current_chord[note_index] + (octave * 12);
            } else { // kick
              int note_index;
              if (rand()%100 > 30) {
                note_index = 1;
              } else {
                note_index = 1 + (2*(rand()%2));
              }
              note = current_chord[note_index] + (octave * 12);
            }
          }
        }
        teenth_array[i][0] = note;
        teenth_array[i][1] = duration;
        note_remaining_duration = duration;
      }
      current_chord_duration -= 1;
      note_remaining_duration -= 1;
    }
    return teenth_array;
  }

  int** modify_bar_to_new_mode_or_key(int** bar, int mode, int starting_note, int new_mode, int new_starting_note, int octave)
  {
    if (mode == new_mode && starting_note == new_starting_note)
    {
      return bar;
    }
    int** new_bar = new int* [16];
    int new_lowest_note = notes::find_lowest_note(new_starting_note);
    int* new_scale = notes::get_single_octave(new_lowest_note, new_mode, false);
    for (int i=0; i<16; i++)
    {
      new_bar[i] = new int [2];
      int note = bar[i][0];
      int duration = bar[i][1];
      if (note != -1)
      {
        int note_val = notes::convert_to_note_value(note, mode, starting_note);
        int new_note = new_scale[note_val] + 12*octave;
        
        new_bar[i][0] = new_note;
        new_bar[i][1] = duration;
      } else {
        new_bar[i][0] = -1;
        new_bar[i][1] = duration;
      }
    }
    delete[] new_scale;
    return new_bar;
  }

  int** modify_bar_for_fill(int** bar, int* fill)
  {
    int fill_start = -1;
    for (int i=0; i<16; i++)
    {
      if (fill[i] != 0)
      {
        fill_start = i;
        break;
      }
    }
    if (fill_start == -1)
    {
      return bar;
    }

    int** new_bar = new int* [16];

    int no_note_fill = rand()%100 > 60;

    for (int i=0; i<16; i++)
    {
      new_bar[i] = new int [2];

      int stored_note = 0;
      if (i < fill_start)
      {
        new_bar[i][0] = bar[i][0];
        if (bar[i][1] + i > fill_start)
        {
          new_bar[i][1] = fill_start - i;
        } else {
          new_bar[i][1] = bar[i][1];
        }
        stored_note = bar[i][0];
      } else {
        if (!no_note_fill)
        {
          int max_duration = 16-i;
          for (int j=i; j<16; j++)
          {
            if (bar[j][0] != -1)
            {
              max_duration = (j-i)+1;
              break;
            }
          }
          if (fill[i] != 0 && bar[i][0] != -1)
          {
            new_bar[i][0] = bar[i][0];
            stored_note = bar[i][0];
            if (rand()%100 > 50)
            {
              new_bar[i][1] = bar[i][1];
            } else {
              new_bar[i][1] = (rand()%max_duration) + 1;
            }
          } else {
            if (fill[i] == 0 && bar[i][0] != -1)
            {
              if (rand()%100 > 80)
              {
                new_bar[i][0] = bar[i][0];
                stored_note = bar[i][0];
                if (rand()%100 > 30)
                {
                  new_bar[i][1] = (rand()%max_duration) + 1;
                } else {
                  new_bar[i][1] = bar[i][1];
                }
              }
            } else if (fill[i] != 0 && bar[i][0] == -1) {
              if (rand()%100 > 40)
              {
                new_bar[i][0] = stored_note;
                new_bar[i][1] = 1;
              } else {
                new_bar[i][0] = -1;
                new_bar[i][1] = 1;
              }
            } else {
              new_bar[i][0] = -1;
              new_bar[i][1] = 1;
            }
          }
        } else {

          new_bar[i][0] = -1;
          new_bar[i][1] = 1;
        }
      }
    }

    return new_bar;
  }
}
