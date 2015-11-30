#include "node-cpython-3X.h"

extern "C" {
  #include <Python.h>
}

Nan::Persistent<v8::Function> NodeCPython3X::constructor;

NodeCPython3X::NodeCPython3X() {
  Py_Initialize();
}

NodeCPython3X::~NodeCPython3X() {
  Py_Finalize();
}

void NodeCPython3X::Init(v8::Local<v8::Object> exports) {
  Nan::HandleScope scope;

  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("NodeCPython3X").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  Nan::SetPrototypeMethod(tpl, "value", GetValue);

  Nan::SetPrototypeMethod(tpl, "preInit", PreInit);
  Nan::SetPrototypeMethod(tpl, "initialize", Initialize);
  Nan::SetPrototypeMethod(tpl, "isInitialized", Initialize);
  Nan::SetPrototypeMethod(tpl, "finalize", Finalize);
  Nan::SetPrototypeMethod(tpl, "isFinalized", Finalize);
  Nan::SetPrototypeMethod(tpl, "setPath", SetPath);

  Nan::SetPrototypeMethod(tpl, "addModule", AddModule);
  Nan::SetPrototypeMethod(tpl, "getDict", GetDict);

  Nan::SetPrototypeMethod(tpl, "simpleString", SimpleString);
  Nan::SetPrototypeMethod(tpl, "runString", RunString);

  constructor.Reset(tpl->GetFunction());
  exports->Set(Nan::New("NodeCPython3X").ToLocalChecked(), tpl->GetFunction());
}

void NodeCPython3X::New(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if (info.IsConstructCall()) {
    // Invoked as constructor: `new NodeCPython3X(...)`
    NodeCPython3X* obj = new NodeCPython3X();
    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
  } else {
    // Invoked as plain function `NodeCPython3X(...)`, turn into construct call.
    const int argc = 1;
    v8::Local<v8::Value> argv[argc] = { info[0] };
    v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
    info.GetReturnValue().Set(cons->NewInstance(argc, argv));
  }
}

void NodeCPython3X::GetValue(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  // NodeCPython3X* obj = ObjectWrap::Unwrap<NodeCPython3X>(info.Holder());
  // info.GetReturnValue().Set(Nan::New(obj->value_));
}


void NodeCPython3X::PreInit(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  // NodeCPython3X* obj = ObjectWrap::Unwrap<NodeCPython3X>(info.Holder());
  // obj->value_ += 1;
  // program = Py_DecodeLocale(info[0], NULL);
  // if (program == NULL) {
  //     fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
  //     exit(1);
  // }
  // obj->value_ = program;
  // info.GetReturnValue().Set(Nan::New(obj->program));
  // info.GetReturnValue().Set(Nan::New(obj->value_));
}

void NodeCPython3X::Initialize(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Py_Initialize();
  info.GetReturnValue().Set(Nan::True());
}

void NodeCPython3X::IsInitialized(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if (Py_IsInitialized()) {
    info.GetReturnValue().Set(Nan::True());
  } else {
    info.GetReturnValue().Set(Nan::False());
  }
}

void NodeCPython3X::Finalize(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Py_Finalize();
  info.GetReturnValue().Set(Nan::True());
}

void NodeCPython3X::IsFinalized(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if (!Py_IsInitialized()) {
    info.GetReturnValue().Set(Nan::True());
  } else {
    info.GetReturnValue().Set(Nan::False());
  }
}

void NodeCPython3X::SetPath(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  std::string argStr = std::string(*Nan::Utf8String(info[0]->ToString()));
  const char *str = argStr.c_str();
  // Lorenzo did some magic below
  PySys_SetPath(const_cast<char*>(str));
}

void NodeCPython3X::AddModule(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  NodeCPython3X* obj = ObjectWrap::Unwrap<NodeCPython3X>(info.Holder());

  obj->main = PyImport_AddModule("__main__");
  info.GetReturnValue().Set(Nan::New(obj->main));
}

void NodeCPython3X::GetDict(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  NodeCPython3X* obj = ObjectWrap::Unwrap<NodeCPython3X>(info.Holder());

  obj->d = PyModule_GetDict(obj->main);
  info.GetReturnValue().Set(Nan::New(obj->d));
}

// =============================================================================
// ================================== High Level ===============================
// =============================================================================

void NodeCPython3X::SimpleString(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  std::string pyStr = std::string(*Nan::Utf8String(info[0]->ToString()));
  const char *str = pyStr.c_str();
  PyRun_SimpleString(str);
}

void NodeCPython3X::RunString(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  NodeCPython3X* obj = ObjectWrap::Unwrap<NodeCPython3X>(info.Holder());

  std::string pyStr = std::string(*Nan::Utf8String(info[0]->ToString()));
  const char *str = pyStr.c_str();

  PyRun_String(str, Py_single_input, obj->d, obj->d);
}
