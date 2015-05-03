#include <nan.h>
#include <iostream>
#include <string>


using namespace v8;

extern "C" {
  #include <Python.h>
  void simple_String(const char *str) {

    // TODO: make it optional in JS and pass ProgramName down
    //Py_SetProgramName(argv[0]);  /* optional but recommended */
    Py_Initialize();
    PyRun_SimpleString(str);
    Py_Finalize();
  }
}


NAN_METHOD(Method) {
  NanScope();

  // TODO: Check whether this check is necessary and
  // if not redundant to JS check
  if (args.Length() != 1) {
    NanThrowTypeError("Function expects one argument");
    NanReturnUndefined();
  }

  /*
  * This method takes the string from arguments and goes to
  * great length to convert from arguments to v8::String.. to
  * std::string to c-string, to eventually pass into cpython methods
  */
  v8::String::Utf8Value py_string_param(args[0]->ToString());
  std::string param = std::string(*py_string_param);
  const char *py_cstr = param.c_str();

  simple_String(py_cstr);

  // TODO: Clean-up
  NanReturnValue(NanNew("world"));
}

void Init(Handle<Object> exports) {
  exports->Set(NanNew("simpleString"), NanNew<FunctionTemplate>(Method)->GetFunction());
}

NODE_MODULE(simpleString, Init)
