#ifndef DRUM_IMPORTS
#define DRUM_IMPORTS

#include <node.h>
#include <array>
#include <math.h>
#include <iostream>

namespace drum_track
{
  extern void free_all_track_memory();
}

namespace drum_imports
{
  using v8::FunctionCallbackInfo;
  using v8::Isolate;
  using v8::Local;
  using v8::Handle;
  using v8::Number;
  using v8::Value;
  using v8::Array;
  using v8::Float32Array;

  double** kick_buffer;
  int kick_buffer_channels;
  int kick_buffer_size;

  double** crash1_buffer;
  int crash1_buffer_channels;
  int crash1_buffer_size;

  double** crash2_buffer;
  int crash2_buffer_channels;
  int crash2_buffer_size;

  double** hi_hat_closed_buffer;
  int hi_hat_closed_buffer_channels;
  int hi_hat_closed_buffer_size;

  double** hi_hat_open_buffer;
  int hi_hat_open_buffer_channels;
  int hi_hat_open_buffer_size;

  double** ride1_buffer;
  int ride1_buffer_channels;
  int ride1_buffer_size;

  double** ride2_buffer;
  int ride2_buffer_channels;
  int ride2_buffer_size;

  double** snare_buffer;
  int snare_buffer_channels;
  int snare_buffer_size;

  double** snare_soft_buffer;
  int snare_soft_buffer_channels;
  int snare_soft_buffer_size;

  double** tom_floor1_buffer;
  int tom_floor1_buffer_channels;
  int tom_floor1_buffer_size;

  double** tom_floor2_buffer;
  int tom_floor2_buffer_channels;
  int tom_floor2_buffer_size;

  double** tom_high_buffer;
  int tom_high_buffer_channels;
  int tom_high_buffer_size;

  double** tom_mid_buffer;
  int tom_mid_buffer_channels;
  int tom_mid_buffer_size;

  double** tom_mid_high_buffer;
  int tom_mid_high_buffer_channels;
  int tom_mid_high_buffer_size;

  void Set_Buffer(Local<Array> input_array,
    double*** buffer,
    int* channels,
    int* buffer_size
  );
  void Set_Kick_Buffer(const FunctionCallbackInfo<Value>& args);
  void Set_Crash1_Buffer(const FunctionCallbackInfo<Value>& args);
  void Set_Crash2_Buffer(const FunctionCallbackInfo<Value>& args);
  void Set_Hi_Hat_Open_Buffer(const FunctionCallbackInfo<Value>& args);
  void Set_Hi_Hat_Closed_Buffer(const FunctionCallbackInfo<Value>& args);
  void Set_Ride1_Buffer(const FunctionCallbackInfo<Value>& args);
  void Set_Ride2_Buffer(const FunctionCallbackInfo<Value>& args);
  void Set_Snare_Buffer(const FunctionCallbackInfo<Value>& args);
  void Set_Snare_Soft_Buffer(const FunctionCallbackInfo<Value>& args);
  void Set_Tom_Floor1_Buffer(const FunctionCallbackInfo<Value>& args);
  void Set_Tom_Floor2_Buffer(const FunctionCallbackInfo<Value>& args);
  void Set_Tom_High_Buffer(const FunctionCallbackInfo<Value>& args);
  void Set_Tom_Mid_Buffer(const FunctionCallbackInfo<Value>& args);
  void Set_Tom_Mid_High_Buffer(const FunctionCallbackInfo<Value>& args);
  void Free_Drum_Memory(const FunctionCallbackInfo<Value>& args);
}

#endif
