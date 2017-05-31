// HOME=~/.electron-gyp node-gyp rebuild --target=1.6.8 --arch=x64 --dist-url=https://atom.io/download/electron

#include <node.h>
#include <array>
#include <math.h>
#include <iostream>

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::Handle;
using v8::Number;
using v8::Value;
using v8::Array;
using v8::Float32Array;

namespace audio_setup
{
  // extern int sample_rate;
  // extern int tempo;
  // extern double** main_audio_buffer;
  // extern int main_audio_buffer_size;
  // extern int main_audio_buffer_channels;
  extern void Set_Mode(const FunctionCallbackInfo<Value>& args);
  extern void Set_Sample_Rate(const FunctionCallbackInfo<Value>& args);
  extern void Get_Sample_Rate(const FunctionCallbackInfo<Value>& args);
  extern void Set_Tempo(const FunctionCallbackInfo<Value>& args);
  extern void Get_Tempo(const FunctionCallbackInfo<Value>& args);
}

namespace drum_imports
{
  // extern double** kick_buffer;
  // extern int kick_buffer_channels;
  // extern int kick_buffer_size;
  // extern double** crash1_buffer;
  // extern int crash1_buffer_channels;
  // extern int crash1_buffer_size;
  // extern double** crash2_buffer;
  // extern int crash2_buffer_channels;
  // extern int crash2_buffer_size;
  // extern double** hi_hat_closed_buffer;
  // extern int hi_hat_closed_buffer_channels;
  // extern int hi_hat_closed_buffer_size;
  // extern double** hi_hat_open_buffer;
  // extern int hi_hat_open_buffer_channels;
  // extern int hi_hat_open_buffer_size;
  // extern double** ride1_buffer;
  // extern int ride1_buffer_channels;
  // extern int ride1_buffer_size;
  // extern double** ride2_buffer;
  // extern int ride2_buffer_channels;
  // extern int ride2_buffer_size;
  // extern double** snare_buffer;
  // extern int snare_buffer_channels;
  // extern int snare_buffer_size;
  // extern double** snare_soft_buffer;
  // extern int snare_soft_buffer_channels;
  // extern int snare_soft_buffer_size;
  // extern double** tom_floor1_buffer;
  // extern int tom_floor1_buffer_channels;
  // extern int tom_floor1_buffer_size;
  // extern double** tom_floor2_buffer;
  // extern int tom_floor2_buffer_channels;
  // extern int tom_floor2_buffer_size;
  // extern double** tom_high_buffer;
  // extern int tom_high_buffer_channels;
  // extern int tom_high_buffer_size;
  // extern double** tom_mid_buffer;
  // extern int tom_mid_buffer_channels;
  // extern int tom_mid_buffer_size;
  // extern double** tom_mid_high_buffer;
  // extern int tom_mid_high_buffer_channels;
  // extern int tom_mid_high_buffer_size;

  extern void Set_Buffer(Local<Array> input_array,
    double*** buffer,
    int* channels,
    int* buffer_size
  );

  extern void Set_Kick_Buffer(const FunctionCallbackInfo<Value>& args);
  extern void Set_Crash1_Buffer(const FunctionCallbackInfo<Value>& args);
  extern void Set_Crash2_Buffer(const FunctionCallbackInfo<Value>& args);
  extern void Set_Hi_Hat_Open_Buffer(const FunctionCallbackInfo<Value>& args);
  extern void Set_Hi_Hat_Closed_Buffer(const FunctionCallbackInfo<Value>& args);
  extern void Set_Ride1_Buffer(const FunctionCallbackInfo<Value>& args);
  extern void Set_Ride2_Buffer(const FunctionCallbackInfo<Value>& args);
  extern void Set_Snare_Buffer(const FunctionCallbackInfo<Value>& args);
  extern void Set_Snare_Soft_Buffer(const FunctionCallbackInfo<Value>& args);
  extern void Set_Tom_Floor1_Buffer(const FunctionCallbackInfo<Value>& args);
  extern void Set_Tom_Floor2_Buffer(const FunctionCallbackInfo<Value>& args);
  extern void Set_Tom_High_Buffer(const FunctionCallbackInfo<Value>& args);
  extern void Set_Tom_Mid_Buffer(const FunctionCallbackInfo<Value>& args);
  extern void Set_Tom_Mid_High_Buffer(const FunctionCallbackInfo<Value>& args);
  extern void Free_Drum_Memory(const FunctionCallbackInfo<Value>& args);
}

namespace get_buffers
{
  extern Local<Array> Get_Buffer(Isolate* isolate,
    double** buffer,
    int buffer_channels,
    int buffer_size
  );

  extern void Get_Main_Buffer(const FunctionCallbackInfo<Value>& args);
  extern void Get_Main_Drum_Buffer(const FunctionCallbackInfo<Value>& args);
  extern void Get_Main_Bass_Buffer(const FunctionCallbackInfo<Value>& args);
}





namespace sound_gen_main
{
  void init(Local<Object> exports)
  {
    NODE_SET_METHOD(exports, "setKick", drum_imports::Set_Kick_Buffer);
    NODE_SET_METHOD(exports, "setCrash1", drum_imports::Set_Crash1_Buffer);
    NODE_SET_METHOD(exports, "setCrash2", drum_imports::Set_Crash2_Buffer);
    NODE_SET_METHOD(exports, "setHiHatOpen", drum_imports::Set_Hi_Hat_Open_Buffer);
    NODE_SET_METHOD(exports, "setHiHatClosed", drum_imports::Set_Hi_Hat_Closed_Buffer);
    NODE_SET_METHOD(exports, "setRide1", drum_imports::Set_Ride1_Buffer);
    NODE_SET_METHOD(exports, "setRide2", drum_imports::Set_Ride2_Buffer);
    NODE_SET_METHOD(exports, "setSnare", drum_imports::Set_Snare_Buffer);
    NODE_SET_METHOD(exports, "setSnareSoft", drum_imports::Set_Snare_Soft_Buffer);
    NODE_SET_METHOD(exports, "setTomFloor1", drum_imports::Set_Tom_Floor1_Buffer);
    NODE_SET_METHOD(exports, "setTomFloor2", drum_imports::Set_Tom_Floor2_Buffer);
    NODE_SET_METHOD(exports, "setTomHigh", drum_imports::Set_Tom_High_Buffer);
    NODE_SET_METHOD(exports, "setTomMid", drum_imports::Set_Tom_Mid_Buffer);
    NODE_SET_METHOD(exports, "setTomMidHigh", drum_imports::Set_Tom_Mid_High_Buffer);

    NODE_SET_METHOD(exports, "freeAllMemory", drum_imports::Free_Drum_Memory);

    NODE_SET_METHOD(exports, "setSampleRate", audio_setup::Set_Sample_Rate);
    NODE_SET_METHOD(exports, "getSampleRate", audio_setup::Get_Sample_Rate);
    NODE_SET_METHOD(exports, "setTempo", audio_setup::Set_Tempo);
    NODE_SET_METHOD(exports, "getTempo", audio_setup::Get_Tempo);
    NODE_SET_METHOD(exports, "setMode", audio_setup::Set_Mode);

    NODE_SET_METHOD(exports, "getMainDrumBuffer", get_buffers::Get_Main_Drum_Buffer);
    NODE_SET_METHOD(exports, "getMainBassBuffer", get_buffers::Get_Main_Bass_Buffer);
    NODE_SET_METHOD(exports, "getMainBuffer", get_buffers::Get_Main_Buffer);

  }

  NODE_MODULE(soundGen, init)
}
