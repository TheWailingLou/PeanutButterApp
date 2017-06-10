#include "audio_setup.h"

namespace audio_setup
{
  void Set_Key(const FunctionCallbackInfo<Value>& args) 
  {
    key = args[0]->NumberValue();
  }
  void Set_Sample_Rate(const FunctionCallbackInfo<Value>& args)
  {
    sample_rate = args[0]->NumberValue();
  }

  void Set_Mode(const FunctionCallbackInfo<Value>& args)
  {
    mode = args[0]->NumberValue();
  }

  void Get_Sample_Rate(const FunctionCallbackInfo<Value>& args)
  {
    Isolate* isolate = args.GetIsolate();
    Local<Number> num = Number::New(isolate, sample_rate);
    args.GetReturnValue().Set(num);
  }

  void Set_Tempo(const FunctionCallbackInfo<Value>& args)
  {
    tempo = args[0]->NumberValue();
  }

  void Get_Tempo(const FunctionCallbackInfo<Value>& args)
  {
    Isolate* isolate = args.GetIsolate();
    Local<Number> num = Number::New(isolate, tempo);
    args.GetReturnValue().Set(num);
  }
}
