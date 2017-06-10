#ifndef FREE_MEMORY_H
#define FREE_MEMORY_H

#include <node.h>

namespace drum_track
{
  extern void free_all_track_memory();
}

namespace bass_track
{
  extern void free_all_track_memory();
}

namespace main_track
{
  extern void free_all_track_memory();
}

namespace free_memory
{
  using v8::FunctionCallbackInfo;
  using v8::Isolate;
  using v8::Local;
  using v8::Handle;
  using v8::Number;
  using v8::Value;

  void Free_All_Memory(const FunctionCallbackInfo<Value>& args);
  void Free_Bass_Memory(const FunctionCallbackInfo<Value>& args);
  void Free_Drum_Memory(const FunctionCallbackInfo<Value>& args);
  void Free_Main_Memory(const FunctionCallbackInfo<Value>& args);
}

#endif
