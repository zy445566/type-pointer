#include <nan.h>

void getObjectAddr(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if (info.Length() < 1) {
    Nan::ThrowTypeError("Wrong number of arguments");
    return;
  }
  v8::Local<v8::Object> obj = info[0]->ToObject();
  // v8::Local<v8::Object> *objP = (v8::Local<v8::Object>*)malloc(sizeof(v8::Local<v8::Object>));
  // *objP = obj;
  char objAddrStr[20]; //max 0x8000000000000000
  sprintf( objAddrStr,"%p",&obj);
  v8::Local<v8::String> v8ObjAddrStr = v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), objAddrStr);
  info.GetReturnValue().Set(v8ObjAddrStr);
}

void getObjectByAddr(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if (info.Length() < 1) {
    Nan::ThrowTypeError("Wrong number of arguments");
    return;
  }
  int64_t addr = info[0]->IntegerValue();
  v8::Local<v8::Object> *objP;
  objP = (v8::Local<v8::Object> *)addr;
  info.GetReturnValue().Set(*objP);
}

void Init(v8::Local<v8::Object> exports) {
  exports->Set(Nan::New("getObjectAddr").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(getObjectAddr)->GetFunction());
  exports->Set(Nan::New("getObjectByAddr").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(getObjectByAddr)->GetFunction());
}

NODE_MODULE(typePointer, Init)