#include <nan.h>
#include "node-cpython-2X.h"

void InitAll(v8::Local<v8::Object> exports) {
  NodeCPython2X::Init(exports);
}

NODE_MODULE(addon, InitAll)
