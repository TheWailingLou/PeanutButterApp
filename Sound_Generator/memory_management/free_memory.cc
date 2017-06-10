#include "free_memory.h"

namespace free_memory
{
  void Free_All_Memory(const FunctionCallbackInfo<Value>& args)
  {
    drum_track::free_all_track_memory();
    bass_track::free_all_track_memory();
    main_track::free_all_track_memory();
  }

  void Free_Bass_Memory(const FunctionCallbackInfo<Value>& args)
  {
    bass_track::free_all_track_memory();
  }

  void Free_Drum_Memory(const FunctionCallbackInfo<Value>& args)
  {
    drum_track::free_all_track_memory();
  }

  void Free_Main_Memory(const FunctionCallbackInfo<Value>& args)
  {
    main_track::free_all_track_memory();
  }

}
