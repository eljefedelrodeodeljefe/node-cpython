
#include <nan.h>

using namespace v8;

int foo(){
  return 1;
}

int bar(){
  printf("%s\n", "hello");
  return 0;
}


NAN_METHOD(Method) {
  NanScope();

  NanReturnValue(NanNew(bar()));
}

/**
* This one needs to be udnerstood, really.
*/
void Init(Handle<Object> exports) {
  exports->Set(NanNew("nantest"), NanNew<FunctionTemplate>(Method)->GetFunction());
}

NODE_MODULE(nantest, Init)
