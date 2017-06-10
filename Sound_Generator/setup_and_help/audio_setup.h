#ifndef AUDIO_SETUP_H
#define AUDIO_SETUP_H

#include <node.h>
#include <array>
#include <math.h>
#include <iostream>

namespace audio_setup
{
  using v8::FunctionCallbackInfo;
  using v8::Isolate;
  using v8::Local;
  using v8::Handle;
  using v8::Number;
  using v8::Value;

  int sample_rate;
  int tempo;
  int mode;
  int key;
  double** main_audio_buffer;
  int main_audio_buffer_size;
  int main_audio_buffer_channels;

  void Set_Key(const FunctionCallbackInfo<Value>& args) ;
  void Set_Mode(const FunctionCallbackInfo<Value>& args);
  void Set_Sample_Rate(const FunctionCallbackInfo<Value>& args);
  void Get_Sample_Rate(const FunctionCallbackInfo<Value>& args);
  void Set_Tempo(const FunctionCallbackInfo<Value>& args);
  void Get_Tempo(const FunctionCallbackInfo<Value>& args);
}

#endif
