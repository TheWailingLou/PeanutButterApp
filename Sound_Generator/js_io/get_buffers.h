#ifndef GET_BUFFERS_H
#define GET_BUFFERS_H

#include <node.h>
#include <array>
#include <math.h>
#include <iostream>

namespace main_track
{
  extern double** main_buffer;
  extern int main_buffer_size;
  extern int main_buffer_channels;
  extern void test_creation();
}

namespace drum_track
{
  extern double** main_buffer;
  extern int main_buffer_size;
  extern int main_buffer_channels;
  // extern void test_creation();
}

namespace bass_track
{
  extern double** main_buffer;
  extern int main_buffer_size;
  extern int main_buffer_channels;
  // extern void test_creation();
}

namespace audio_setup
{
  extern double** main_audio_buffer;
  extern int main_audio_buffer_size;
  extern int main_audio_buffer_channels;
}


namespace get_buffers
{
  using v8::FunctionCallbackInfo;
  using v8::Isolate;
  using v8::Local;
  using v8::Handle;
  using v8::Number;
  using v8::Value;
  using v8::Array;

  Local<Array> Get_Buffer(Isolate* isolate,
    double** buffer,
    int buffer_channels,
    int buffer_size
  );

  void Create_All_Tracks(const FunctionCallbackInfo<Value>& args);
  void Get_Main_Buffer(const FunctionCallbackInfo<Value>& args);
  void Get_Main_Drum_Buffer(const FunctionCallbackInfo<Value>& args);
  void Get_Main_Bass_Buffer(const FunctionCallbackInfo<Value>& args);
}

#endif
