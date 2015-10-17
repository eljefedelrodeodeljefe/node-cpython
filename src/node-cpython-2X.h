#ifndef NODECPYTHON2X_H
#define NODECPYTHON2X_H

#include <nan.h>

class NodeCPython2X : public Nan::ObjectWrap {
 public:
  static void Init(v8::Local<v8::Object> exports);

 private:
  NodeCPython2X();
  ~NodeCPython2X();

  static void New(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static void GetValue(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static void PlusOne(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static Nan::Persistent<v8::Function> constructor;
};

#endif
