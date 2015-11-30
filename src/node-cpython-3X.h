#ifndef NODECPYTHON3X_H
#define NODECPYTHON3X_H

#include <nan.h>
extern "C" {
  #include <Python.h>
}

class NodeCPython3X : public Nan::ObjectWrap {
 public:
  static void Init(v8::Local<v8::Object> exports);

 private:
  NodeCPython3X();
  ~NodeCPython3X();

  static void New(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static void GetValue(const Nan::FunctionCallbackInfo<v8::Value>& info);

  static void PreInit(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static void Initialize(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static void IsInitialized(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static void Finalize(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static void IsFinalized(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static void SetPath(const Nan::FunctionCallbackInfo<v8::Value>& info);

  static void SimpleString(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static void RunString(const Nan::FunctionCallbackInfo<v8::Value>& info);

  static void AddModule(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static void GetDict(const Nan::FunctionCallbackInfo<v8::Value>& info);

  static Nan::Persistent<v8::Function> constructor;
  static wchar_t *program;
  PyObject *main;
  PyObject *d;
};

#endif
