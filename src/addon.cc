#include <nan.h>
#include "node-cpython-2X.h"
#include "ffi.h"

void InitAll(v8::Local<v8::Object> exports) {
  NodeCPython2X::Init(exports);
  FFI::Init(exports);
}

NODE_MODULE(addon, InitAll)
