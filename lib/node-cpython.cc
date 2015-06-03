#include <nan.h>



using namespace v8;

extern "C" {
  #include <Python.h>

  int run_Run() {
    char *argv[] = {"program name", "arg1", "arg2"};
    int argc = sizeof(argv) / sizeof(char*) - 1;

    Py_Initialize();
    PySys_SetArgvEx(argc, argv, 0);

    // Get a reference to the main module.
    PyObject* main_module = PyImport_AddModule("__main__");

    // Get the main module's dictionary
    // and make a copy of it.
    PyObject* main_dict = PyModule_GetDict(main_module);
    PyObject* main_dict_copy = PyDict_Copy(main_dict);

    // Execute two different files of
    // Python code in separate environments
    FILE* file_1 = fopen("example/multiply_2.py", "r");
    PyRun_File(file_1, "file1.py", Py_file_input, main_dict, main_dict);
    PyRun_SimpleString("import sys\n");
    PyRun_SimpleString("print sys.argv\n");

    FILE* file_2 = fopen("file2.py", "r");
    PyRun_File(file_2, "file2.py", Py_file_input, main_dict_copy, main_dict_copy);



    Py_Finalize();

    return 0;
  }

  void simple_String(const char *str) {

    // TODO: make it optional in JS and pass ProgramName down
    //Py_SetProgramName(argv[0]);  /* optional but recommended */
    Py_Initialize();
    PyRun_SimpleString(str);
    Py_Finalize();
  }

  void simple_File(FILE *fp, const char *filename) {

    // TODO: make it optional in JS and pass ProgramName down
    //Py_SetProgramName(argv[0]);  /* optional but recommended */
    Py_Initialize();
    PyRun_SimpleFile(fp, filename);
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

NAN_METHOD(Method2) {
  NanScope();

  // TODO: Check whether this check is necessary and
  // if not redundant to JS check
  // if (args.Length() != 1) {
  //   NanThrowTypeError("Function expects one argument");
  //   NanReturnUndefined();
  // }

  v8::String::Utf8Value py_filepath_string_param(args[0]->ToString());
  std::string param0 = std::string(*py_filepath_string_param);
  const char *py_filepath_cstr = param0.c_str();

  v8::String::Utf8Value py_filename_string_param(args[1]->ToString());
  std::string param1 = std::string(*py_filename_string_param);
  const char *py_filename_cstr = param1.c_str();

  FILE * fp;
  fp = fopen(py_filepath_cstr, "r");

  simple_File(fp, py_filename_cstr);

  // TODO: Clean-up
  NanReturnValue(NanNew("world2"));
}

NAN_METHOD(Method3) {
  NanScope();

  // TODO: Check whether this check is necessary and
  // if not redundant to JS check
  // if (args.Length() != 1) {
  //   NanThrowTypeError("Function expects one argument");
  //   NanReturnUndefined();
  // }
  //
  // v8::String::Utf8Value py_filepath_string_param(args[0]->ToString());
  // std::string param0 = std::string(*py_filepath_string_param);
  // const char *py_filepath_cstr = param0.c_str();
  //
  // v8::String::Utf8Value py_filename_string_param(args[1]->ToString());
  // std::string param1 = std::string(*py_filename_string_param);
  // const char *py_filename_cstr = param1.c_str();

  run_Run();

  // TODO: Clean-up
  NanReturnValue(NanNew("world2"));
}

void Init(Handle<Object> exports) {
  exports->Set(NanNew("simpleString"), NanNew<FunctionTemplate>(Method)->GetFunction());
  exports->Set(NanNew("simpleFile"), NanNew<FunctionTemplate>(Method2)->GetFunction());
  exports->Set(NanNew("runRun"), NanNew<FunctionTemplate>(Method3)->GetFunction());
}


NODE_MODULE(cpython, Init)
