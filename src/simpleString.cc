#include <nan.h>


using namespace v8;

extern "C" {
  #include <Python.h>
  void simple_String()
  {
    //Py_SetProgramName(argv[0]);  /* optional but recommended */
    Py_Initialize();
    PyRun_SimpleString("from time import time,ctime\n"
                       "print 'Today is',ctime(time())\n");
    Py_Finalize();
    printf("%s\n", "hello");
  }
}


NAN_METHOD(Method) {
  NanScope();
  simple_String();
  NanReturnValue(NanNew("world"));
}

void Init(Handle<Object> exports) {
  exports->Set(NanNew("simpleString"), NanNew<FunctionTemplate>(Method)->GetFunction());
}

NODE_MODULE(simpleString, Init)
