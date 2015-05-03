#include <nan.h>



using namespace v8;

extern "C" {
  #include <Python.h>
  void simple_File() {
    // TODO: implement!
  }
}


NAN_METHOD(Method) {
  NanScope();

  simple_File();

  // TODO: Clean-up
  NanReturnValue(NanNew("world"));
}

void Init(Handle<Object> exports) {
  exports->Set(NanNew("simpleFile"), NanNew<FunctionTemplate>(Method)->GetFunction());
}

NODE_MODULE(simpleFile, Init)
