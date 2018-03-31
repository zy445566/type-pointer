#include <nan.h>
#include<sys/mman.h>
#include<sys/types.h>
#include<fcntl.h>
#include<string.h>
#include<stdio.h>
#include<unistd.h>

// class MallocArrayBufferAllocator : public v8::ArrayBuffer::Allocator {
// public:
//   virtual void* Allocate(size_t length) { return malloc(length); }
//   virtual void* AllocateUninitialized(size_t length) { return malloc(length); }
//   virtual void Free(void* data, size_t length) { free(data); }
// };
// v8::V8::SetArrayBufferAllocator(new MallocArrayBufferAllocator);


void * getEmptyPMap(const char* path,long unsigned int size)
{
    int fd;
    fd = open(path,O_CREAT|O_RDWR|O_TRUNC,00777);
    void * p_map;
    p_map=(void *)mmap(NULL,size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    write(fd,"",1);
    close(fd);
    return p_map;
}

void * getPMap(const char* path,long unsigned int size)
{
    int fd;
    void *  p_map;
    fd = open(path,O_CREAT|O_RDWR,00777);
    p_map = mmap(NULL,size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    close(fd);
    return p_map;
}

void * getClosePMap(const char* path,long unsigned int size)
{
    void * p_map = getPMap(path,size);
    munmap(p_map,size);
    msync(p_map,size,MS_ASYNC);
    return p_map;
}

Nan::Persistent<v8::Object> *  getPMapByOffset(const char* path,long unsigned int size,long unsigned int offset)
{
    Nan::Persistent<v8::Object> *   p_map = (Nan::Persistent<v8::Object> *)getPMap(path,size);
    p_map+=offset;
    return p_map;
}

void * flushMem(const char* path,long unsigned int size)
{
    return getEmptyPMap(path,size);
}


void * closeMem(const char* path,long unsigned int size)
{
    return getClosePMap(path,size);
}

long unsigned int writeMem(const char* path,long unsigned int size,long unsigned int offset,Nan::Persistent<v8::Object>* objP)
{
    Nan::Persistent<v8::Object> *   p_map = getPMapByOffset(path,size,offset);
    memcpy(p_map,objP,sizeof(Nan::Persistent<v8::Object>));
    return offset;
}

Nan::Persistent<v8::Object> * readMem(const char* path,long unsigned int size,long unsigned int offset)
{
    Nan::Persistent<v8::Object> *  p_map = getPMapByOffset(path,size,offset);
    return p_map;
}

const char* ToCString(const v8::String::Utf8Value& value) {
  return *value;
}

void typeFlush(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if (info.Length() < 2) {
    Nan::ThrowTypeError("Wrong number of arguments");
    return;
  }
  if (!info[0]->IsString()) {
    Nan::ThrowTypeError("path must be string");
    return;
  }
  if (!info[1]->IsNumber()) {
    Nan::ThrowTypeError("size must be number");
    return;
  }
  v8::String::Utf8Value str0(info[0]->ToString());
  const char* path= ToCString(str0);
  uint32_t size = info[1]->Uint32Value();
  void * p = flushMem(path,size);
  char objAddrStr[20];
  sprintf( objAddrStr,"%p",p);
  v8::Local<v8::String> v8AddrStr = v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), objAddrStr);
  info.GetReturnValue().Set(v8AddrStr);
}

void typeClose(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if (info.Length() < 2) {
    Nan::ThrowTypeError("Wrong number of arguments");
    return;
  }
  if (!info[0]->IsString()) {
    Nan::ThrowTypeError("path must be string");
    return;
  }
  if (!info[1]->IsNumber()) {
    Nan::ThrowTypeError("size must be number");
    return;
  }
  v8::String::Utf8Value str0(info[0]->ToString());
  const char* path= ToCString(str0);
  uint32_t size = info[1]->Uint32Value();
  void * p = closeMem(path,size);
  char objAddrStr[20];
  sprintf( objAddrStr,"%p",p);
  v8::Local<v8::String> v8AddrStr = v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), objAddrStr);
  info.GetReturnValue().Set(v8AddrStr);
}

void typeWrite(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if (info.Length() < 2) {
    Nan::ThrowTypeError("Wrong number of arguments");
    return;
  }
  if (!info[0]->IsString()) {
    Nan::ThrowTypeError("path must be string");
    return;
  }
  if (!info[1]->IsNumber()) {
    Nan::ThrowTypeError("size must be number");
    return;
  }
  if (!info[2]->IsNumber()) {
    Nan::ThrowTypeError("offset must be number");
    return;
  }
  if (!info[3]->IsObject()) {
    Nan::ThrowTypeError("obj must be object");
    return;
  }
  v8::String::Utf8Value str0(info[0]->ToString());
  const char* path= ToCString(str0);
  uint32_t size = info[1]->Uint32Value();
  uint32_t offset = info[2]->Uint32Value();
  Nan::Persistent<v8::Object> persistent(Nan::To<v8::Object>(info[3]).ToLocalChecked());
  Nan::Persistent<v8::Object> * objP = &persistent;
  uint32_t writeOffset = writeMem(path,size,offset,objP);
  v8::Local<v8::Uint32> resOffset= Nan::New(writeOffset);
  info.GetReturnValue().Set(resOffset);
}

void typeRead(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if (info.Length() < 2) {
    Nan::ThrowTypeError("Wrong number of arguments");
    return;
  }
  if (!info[0]->IsString()) {
    Nan::ThrowTypeError("path must be string");
    return;
  }
  if (!info[1]->IsNumber()) {
    Nan::ThrowTypeError("size must be number");
    return;
  }
  if (!info[2]->IsNumber()) {
    Nan::ThrowTypeError("offset must be number");
    return;
  }
  v8::String::Utf8Value str0(info[0]->ToString());
  const char* path= ToCString(str0);
  uint32_t size = info[1]->Uint32Value();
  uint32_t offset = info[2]->Uint32Value();
  Nan::Persistent<v8::Object> * p_map = readMem(path,size,offset);
  v8::Local<v8::Object> obj = New(*p_map);
  info.GetReturnValue().Set(obj);
}

void typeReset(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if (info.Length() < 2) {
    Nan::ThrowTypeError("Wrong number of arguments");
    return;
  }
  if (!info[0]->IsString()) {
    Nan::ThrowTypeError("path must be string");
    return;
  }
  if (!info[1]->IsNumber()) {
    Nan::ThrowTypeError("size must be number");
    return;
  }
  if (!info[2]->IsNumber()) {
    Nan::ThrowTypeError("offset must be number");
    return;
  }
  v8::V8::SetArrayBufferAllocator(new MallocArrayBufferAllocator);
  v8::String::Utf8Value str0(info[0]->ToString());
  const char* path= ToCString(str0);
  uint32_t size = info[1]->Uint32Value();
  uint32_t offset = info[2]->Uint32Value();
  Nan::Persistent<v8::Object> * p_map = readMem(path,size,offset);
  (*p_map).Reset();
  info.GetReturnValue().Set(info[2]);
}

// void typeTest(const Nan::FunctionCallbackInfo<v8::Value>& info)
// {
//   v8::String::Utf8Value str0(info[0]->ToString());
//   const char* path= ToCString(str0);
//   uint32_t size = info[1]->Uint32Value();
//   uint32_t offset = info[2]->Uint32Value();
//   Nan::Persistent<v8::Object> persistent(Nan::To<v8::Object>(info[3]).ToLocalChecked());
//   int fd;
//   Nan::Persistent<v8::Object> *   p_map;
//   fd = open(path,O_CREAT|O_RDWR,00777);
//   p_map = (Nan::Persistent<v8::Object> *)mmap(NULL,size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
//   p_map += offset;
//   memcpy(p_map,&persistent,sizeof(Nan::Persistent<v8::Object>));
//   close(fd);
//   info.GetReturnValue().Set(Nan::EmptyString());
// }

void Init(v8::Local<v8::Object> exports) {
  exports->Set(Nan::New("typeFlush").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(typeFlush)->GetFunction());
  exports->Set(Nan::New("typeClose").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(typeClose)->GetFunction());
  exports->Set(Nan::New("typeWrite").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(typeWrite)->GetFunction());
  exports->Set(Nan::New("typeRead").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(typeRead)->GetFunction());
  exports->Set(Nan::New("typeReset").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(typeReset)->GetFunction());
}

NODE_MODULE(typePointer, Init)