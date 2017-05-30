#include "drum_imports.h"

namespace drum_imports
{
  void Set_Buffer(Local<Array> input_array, double*** buffer, int* channels, int* buffer_size)
  {
    *channels = input_array->Length();
    double** placeholder = new double* [*channels];
    for (int channel=0; channel<*channels; channel++)
    {
      Local<Float32Array> channel_array = Handle<Float32Array>::Cast(input_array->Get(channel));
      *buffer_size = channel_array->Length();
      placeholder[channel] = new double[*buffer_size];
      placeholder[channel][0] = 0;
      for (int i=0; i<*buffer_size; i++)
      {
        double num = channel_array->Get(i)->NumberValue();
        placeholder[channel][i] = num;
      }
    }
    *buffer = placeholder;
  }

  void Set_Kick_Buffer(const FunctionCallbackInfo<Value>& args)
  {
    Local<Array> input_array = Handle<Array>::Cast(args[0]);
    Set_Buffer(input_array, &kick_buffer, &kick_buffer_channels, &kick_buffer_size);
  }

  void Set_Crash1_Buffer(const FunctionCallbackInfo<Value>& args)
  {
    Local<Array> input_array = Handle<Array>::Cast(args[0]);
    Set_Buffer(input_array, &crash1_buffer, &crash1_buffer_channels, &crash1_buffer_size);
  }

  void Set_Crash2_Buffer(const FunctionCallbackInfo<Value>& args)
  {
    Local<Array> input_array = Handle<Array>::Cast(args[0]);
    Set_Buffer(input_array, &crash2_buffer, &crash2_buffer_channels, &crash2_buffer_size);
  }

  void Set_Hi_Hat_Open_Buffer(const FunctionCallbackInfo<Value>& args)
  {
    Local<Array> input_array = Handle<Array>::Cast(args[0]);
    Set_Buffer(input_array, &hi_hat_open_buffer, &hi_hat_open_buffer_channels, &hi_hat_open_buffer_size);
  }

  void Set_Hi_Hat_Closed_Buffer(const FunctionCallbackInfo<Value>& args)
  {
    Local<Array> input_array = Handle<Array>::Cast(args[0]);
    Set_Buffer(input_array, &hi_hat_closed_buffer, &hi_hat_closed_buffer_channels, &hi_hat_closed_buffer_size);
  }

  void Set_Ride1_Buffer(const FunctionCallbackInfo<Value>& args)
  {
    Local<Array> input_array = Handle<Array>::Cast(args[0]);
    Set_Buffer(input_array, &ride1_buffer, &ride1_buffer_channels, &ride1_buffer_size);
  }

  void Set_Ride2_Buffer(const FunctionCallbackInfo<Value>& args)
  {
    Local<Array> input_array = Handle<Array>::Cast(args[0]);
    Set_Buffer(input_array, &ride2_buffer, &ride2_buffer_channels, &ride2_buffer_size);
  }

  void Set_Snare_Buffer(const FunctionCallbackInfo<Value>& args)
  {
    Local<Array> input_array = Handle<Array>::Cast(args[0]);
    Set_Buffer(input_array, &snare_buffer, &snare_buffer_channels, &snare_buffer_size);
  }

  void Set_Snare_Soft_Buffer(const FunctionCallbackInfo<Value>& args)
  {
    Local<Array> input_array = Handle<Array>::Cast(args[0]);
    Set_Buffer(input_array, &snare_soft_buffer, &snare_soft_buffer_channels, &snare_soft_buffer_size);
  }

  void Set_Tom_Floor1_Buffer(const FunctionCallbackInfo<Value>& args)
  {
    Local<Array> input_array = Handle<Array>::Cast(args[0]);
    Set_Buffer(input_array, &tom_floor1_buffer, &tom_floor1_buffer_channels, &tom_floor1_buffer_size);
  }

  void Set_Tom_Floor2_Buffer(const FunctionCallbackInfo<Value>& args)
  {
    Local<Array> input_array = Handle<Array>::Cast(args[0]);
    Set_Buffer(input_array, &tom_floor2_buffer, &tom_floor2_buffer_channels, &tom_floor2_buffer_size);
  }

  void Set_Tom_High_Buffer(const FunctionCallbackInfo<Value>& args)
  {
    Local<Array> input_array = Handle<Array>::Cast(args[0]);
    Set_Buffer(input_array, &tom_high_buffer, &tom_high_buffer_channels, &tom_high_buffer_size);
  }

  void Set_Tom_Mid_Buffer(const FunctionCallbackInfo<Value>& args)
  {
    Local<Array> input_array = Handle<Array>::Cast(args[0]);
    Set_Buffer(input_array, &tom_mid_buffer, &tom_mid_buffer_channels, &tom_mid_buffer_size);
  }

  void Set_Tom_Mid_High_Buffer(const FunctionCallbackInfo<Value>& args)
  {
    Local<Array> input_array = Handle<Array>::Cast(args[0]);
    Set_Buffer(input_array, &tom_mid_high_buffer, &tom_mid_high_buffer_channels, &tom_mid_high_buffer_size);
  }

  void Free_Drum_Memory(const FunctionCallbackInfo<Value>& args)
  {
    drum_track::free_all_track_memory();

    for (int i=0; i<kick_buffer_channels; i++)
    {
      delete[] kick_buffer[i];
    }
    delete[] kick_buffer;

    for (int i=0; i<crash1_buffer_channels; i++)
    {
      delete[] crash1_buffer[i];
    }
    delete[] crash1_buffer;

    for (int i=0; i<crash2_buffer_channels; i++)
    {
      delete[] crash2_buffer[i];
    }
    delete[] crash2_buffer;

    for (int i=0; i<hi_hat_closed_buffer_channels; i++)
    {
      delete[] hi_hat_closed_buffer[i];
    }
    delete[] hi_hat_closed_buffer;

    for (int i=0; i<hi_hat_open_buffer_channels; i++)
    {
      delete[] hi_hat_open_buffer[i];
    }
    delete[] hi_hat_open_buffer;

    for (int i=0; i<ride1_buffer_channels; i++)
    {
      delete[] ride1_buffer[i];
    }
    delete[] ride1_buffer;

    for (int i=0; i<ride2_buffer_channels; i++)
    {
      delete[] ride2_buffer[i];
    }
    delete[] ride2_buffer;

    for (int i=0; i<snare_buffer_channels; i++)
    {
      delete[] snare_buffer[i];
    }
    delete[] snare_buffer;

    for (int i=0; i<snare_soft_buffer_channels; i++)
    {
      delete[] snare_soft_buffer[i];
    }
    delete[] snare_soft_buffer;

    for (int i=0; i<tom_floor1_buffer_channels; i++)
    {
      delete[] tom_floor1_buffer[i];
    }
    delete[] tom_floor1_buffer;

    for (int i=0; i<tom_floor2_buffer_channels; i++)
    {
      delete[] tom_floor2_buffer[i];
    }
    delete[] tom_floor2_buffer;

    for (int i=0; i<tom_high_buffer_channels; i++)
    {
      delete[] tom_high_buffer[i];
    }
    delete[] tom_high_buffer;

    for (int i=0; i<tom_mid_buffer_channels; i++)
    {
      delete[] tom_mid_buffer[i];
    }
    delete[] tom_mid_buffer;

    for (int i=0; i<tom_mid_high_buffer_channels; i++)
    {
      delete[] tom_mid_high_buffer[i];
    }
    delete[] tom_mid_high_buffer;
  }
}
