#include "node-cpython-2X.h"

extern "C" {
  #include <Python.h>
}

Nan::Persistent<v8::Function> NodeCPython2X::constructor;

NodeCPython2X::NodeCPython2X() {
  Py_Initialize();
}

NodeCPython2X::~NodeCPython2X() {
  Py_Finalize();
}

void NodeCPython2X::Init(v8::Local<v8::Object> exports) {
  Nan::HandleScope scope;

  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("NodeCPython2X").ToLocalChecked());
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
  exports->Set(Nan::New("NodeCPython2X").ToLocalChecked(), tpl->GetFunction());
}

void NodeCPython2X::New(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if (info.IsConstructCall()) {
    // Invoked as constructor: `new NodeCPython2X(...)`
    NodeCPython2X* obj = new NodeCPython2X();
    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
  } else {
    // Invoked as plain function `NodeCPython2X(...)`, turn into construct call.
    const int argc = 1;
    v8::Local<v8::Value> argv[argc] = { info[0] };
    v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
    info.GetReturnValue().Set(cons->NewInstance(argc, argv));
  }
}

void NodeCPython2X::GetValue(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  // NodeCPython2X* obj = ObjectWrap::Unwrap<NodeCPython2X>(info.Holder());
  // info.GetReturnValue().Set(Nan::New(obj->value_));
}


void NodeCPython2X::PreInit(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  // NodeCPython2X* obj = ObjectWrap::Unwrap<NodeCPython2X>(info.Holder());
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

void NodeCPython2X::Initialize(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Py_Initialize();
  info.GetReturnValue().Set(Nan::True());
}

void NodeCPython2X::IsInitialized(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if (Py_IsInitialized()) {
    info.GetReturnValue().Set(Nan::True());
  } else {
    info.GetReturnValue().Set(Nan::False());
  }
}

void NodeCPython2X::Finalize(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Py_Finalize();
  info.GetReturnValue().Set(Nan::True());
}

void NodeCPython2X::IsFinalized(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if (!Py_IsInitialized()) {
    info.GetReturnValue().Set(Nan::True());
  } else {
    info.GetReturnValue().Set(Nan::False());
  }
}

void NodeCPython2X::SetPath(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  std::string argStr = std::string(*Nan::Utf8String(info[0]->ToString()));
  const char *str = argStr.c_str();
  // Lorenzo did some magic below
  PySys_SetPath(const_cast<char*>(str));
}

void NodeCPython2X::AddModule(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  NodeCPython2X* obj = ObjectWrap::Unwrap<NodeCPython2X>(info.Holder());

  obj->main = PyImport_AddModule("__main__");
  info.GetReturnValue().Set(Nan::New(obj->main));
}

void NodeCPython2X::GetDict(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  NodeCPython2X* obj = ObjectWrap::Unwrap<NodeCPython2X>(info.Holder());

  obj->d = PyModule_GetDict(obj->main);
  info.GetReturnValue().Set(Nan::New(obj->d));
}

// =============================================================================
// ================================== High Level ===============================
// =============================================================================

void NodeCPython2X::SimpleString(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  std::string pyStr = std::string(*Nan::Utf8String(info[0]->ToString()));
  const char *str = pyStr.c_str();
  PyRun_SimpleString(str);
}

void NodeCPython2X::RunString(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  NodeCPython2X* obj = ObjectWrap::Unwrap<NodeCPython2X>(info.Holder());

  std::string pyStr = std::string(*Nan::Utf8String(info[0]->ToString()));
  const char *str = pyStr.c_str();

  PyRun_String(str, Py_single_input, obj->d, obj->d);
}
