#include "myobject.h"
#include <nan.h>

using namespace v8;

MyObject::MyObject(){};
MyObject::~MyObject(){};

Nan::Persistent<v8::Function> MyObject::constructor;

void MyObject::Init() {
  Nan::HandleScope scope;

  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("MyObject").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);
  // Prototype
  tpl->PrototypeTemplate()->Set(Nan::New("plusOne").ToLocalChecked(),
                                Nan::New<v8::FunctionTemplate>(PlusOne));

  constructor.Reset(
      tpl->GetFunction(Nan::GetCurrentContext()).ToLocalChecked());
}

void MyObject::New(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Context> context = info.GetIsolate()->GetCurrentContext();

  MyObject* obj = new MyObject();
  obj->counter_ =
      info[0]->IsUndefined() ? 0 : info[0]->NumberValue(context).FromJust();
  obj->Wrap(info.This());

  info.GetReturnValue().Set(info.This());
}

v8::Local<v8::Object> MyObject::NewInstance(v8::Local<v8::Value> arg) {
  Nan::EscapableHandleScope scope;

  const unsigned argc = 1;
  v8::Local<v8::Value> argv[argc] = {arg};
  v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
  v8::Local<v8::Context> context =
      v8::Isolate::GetCurrent()->GetCurrentContext();
  v8::Local<v8::Object> instance =
      cons->NewInstance(context, argc, argv).ToLocalChecked();

  return scope.Escape(instance);
}

void MyObject::PlusOne(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  MyObject* obj = ObjectWrap::Unwrap<MyObject>(info.This());
  obj->counter_ += 1;

  info.GetReturnValue().Set(Nan::New(obj->counter_));
}
