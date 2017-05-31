#include "get_buffers.h"


namespace get_buffers
{
  Local<Array> Get_Buffer(Isolate* isolate, double** buffer, int buffer_channels, int buffer_size)
  {
    Local<Array> output_array = Array::New(isolate);
    for (int channel=0; channel<buffer_channels; channel++)
    {
      Local<Array> channel_array = Array::New(isolate);
      for (int i=0; i<buffer_size; i++)
      {
        Local<Number> num = Number::New(isolate, buffer[channel][i]);
        channel_array->Set(i, num);
      }
      output_array->Set(channel, channel_array);
    }
    return output_array;
  }

  void Get_Main_Buffer(const FunctionCallbackInfo<Value>& args)
  {
    Isolate* isolate = args.GetIsolate();
    Local<Array> output_array = Get_Buffer(isolate,
      audio_setup::main_audio_buffer,
      audio_setup::main_audio_buffer_channels,
      audio_setup::main_audio_buffer_size
    );
    args.GetReturnValue().Set(output_array);
  }

  void Get_Main_Drum_Buffer(const FunctionCallbackInfo<Value>& args)
  {
    drum_track::test_creation();
    Isolate* isolate = args.GetIsolate();
    Local<Array> output_array = Get_Buffer(isolate,
      drum_track::main_buffer,
      drum_track::main_buffer_channels,
      drum_track::main_buffer_size
    );
    args.GetReturnValue().Set(output_array);
  }

  void Get_Main_Bass_Buffer(const FunctionCallbackInfo<Value>& args)
  {
    bass_track::test_creation();
    Isolate* isolate = args.GetIsolate();
    Local<Array> output_array = Get_Buffer(isolate,
      bass_track::main_buffer,
      bass_track::main_buffer_channels,
      bass_track::main_buffer_size
    );
    args.GetReturnValue().Set(output_array);
  }
}
