#include <nan.h>
#include<sys/mman.h>
#include<sys/types.h>
#include<fcntl.h>
#include<string.h>
#include<stdio.h>
#include<unistd.h>

v8::Local<v8::String> getAddrString(Nan::Persistent<v8::Value> * valueP)
{
  char objAddrStr[20];
  sprintf( objAddrStr,"%p",valueP);
  return v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), objAddrStr);
}

void mallocValueAddr(const Nan::FunctionCallbackInfo<v8::Value>& info)
{
  if (info.Length() < 1) {
    Nan::ThrowTypeError("Wrong number of arguments");
    return;
  }
  Nan::Persistent<v8::Value> persistent(info[0]);
  Nan::Persistent<v8::Value> * valueP = (Nan::Persistent<v8::Value> *)malloc(sizeof(Nan::Persistent<v8::Value>));
  memcpy(valueP,&persistent,sizeof(Nan::Persistent<v8::Value>));
  v8::Local<v8::String> v8AddrStr = getAddrString(valueP);
  info.GetReturnValue().Set(v8AddrStr);
}

void readValueByAddr(const Nan::FunctionCallbackInfo<v8::Value>& info)
{
  if (info.Length() < 1) {
    Nan::ThrowTypeError("Wrong number of arguments");
    return;
  }
  if (!info[0]->IsNumber()) {
    Nan::ThrowTypeError("size must be pointer number");
    return;
  }
  int64_t addr = info[0]->IntegerValue();
  Nan::Persistent<v8::Value> * valueP = (Nan::Persistent<v8::Value> * )addr;
  v8::Local<v8::Value> value = New(*valueP);
  info.GetReturnValue().Set(value);
}

void writeValueByAddr(const Nan::FunctionCallbackInfo<v8::Value>& info)
{
  if (info.Length() < 2) {
    Nan::ThrowTypeError("Wrong number of arguments");
    return;
  }
  if (!info[0]->IsNumber()) {
    Nan::ThrowTypeError("size must be pointer number");
    return;
  }
  int64_t addr = info[0]->IntegerValue();
  Nan::Persistent<v8::Value> persistent(info[1]);
  Nan::Persistent<v8::Value> * valueP = (Nan::Persistent<v8::Value> * )addr;
  (*valueP).Reset();
  memcpy(valueP,&persistent,sizeof(Nan::Persistent<v8::Value>));
  v8::Local<v8::String> v8AddrStr = getAddrString(valueP);
  info.GetReturnValue().Set(v8AddrStr);
}

void freeValueByAddr(const Nan::FunctionCallbackInfo<v8::Value>& info)
{
  if (info.Length() < 1) {
    Nan::ThrowTypeError("Wrong number of arguments");
    return;
  }
  if (!info[0]->IsNumber()) {
    Nan::ThrowTypeError("size must be pointer number");
    return;
  }
  int64_t addr = info[0]->IntegerValue();
  Nan::Persistent<v8::Value> * valueP = (Nan::Persistent<v8::Value> * )addr;
  (*valueP).Reset();
  free(valueP);
  info.GetReturnValue().Set(Nan::True());
}

void Init(v8::Local<v8::Object> exports) {
  exports->Set(Nan::New("mallocValueAddr").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(mallocValueAddr)->GetFunction());
  exports->Set(Nan::New("readValueByAddr").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(readValueByAddr)->GetFunction());
  exports->Set(Nan::New("writeValueByAddr").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(writeValueByAddr)->GetFunction());
  exports->Set(Nan::New("freeValueByAddr").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(freeValueByAddr)->GetFunction());
}

NODE_MODULE(typePointer, Init)