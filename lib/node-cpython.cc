#include <nan.h>



using namespace v8;

extern "C" {
  #include <Python.h>

  int run_Run(const char *filename, int arrc, char *arrv[]) {


    Py_Initialize();
    PySys_SetArgvEx(arrc, arrv, 0);

    // Get a reference to the main module.
    PyObject* main_module = PyImport_AddModule("__main__");

    // Get the main module's dictionary
    // and make a copy of it.
    PyObject* main_dict = PyModule_GetDict(main_module);
    PyObject* main_dict_copy = PyDict_Copy(main_dict);

    // Execute two different files of
    // Python code in separate environments
    FILE* file = fopen(filename, "r");
    PyRun_File(file, filename, Py_file_input, main_dict, main_dict);
    PyRun_SimpleString("import sys\n");
    PyRun_SimpleString("print sys.argv\n");



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



  int initialize() {

    Py_Initialize();
    return 0;
  }


  int finalize() {

    Py_Finalize();
    return 0;
  }

  // get "your own" argc and argv from above
  int pysetargv(int arrc, char *arrv[]) {

    PySys_SetArgvEx(arrc, arrv, 0);
    return 0;
  }

  int setprogramname(const char *namestr) {


    char *name;
    strcpy(name, namestr);

    Py_SetProgramName(name);
    return 0;
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

  if (args.Length() != 3) {
    NanThrowTypeError("Function expects one argument");
    NanReturnUndefined();
  }

  v8::String::Utf8Value py_filepath_string_param(args[0]->ToString());
  std::string param0 = std::string(*py_filepath_string_param);
  const char *py_filepath_cstr = param0.c_str();

  int arrc = args[1]->NumberValue();




  char *arrv[] = {};

  v8::Handle<v8::Object> arg[2];
// ... init obj from arguments or wherever ...

int length = 1;
if(arg[2]->IsArray())
{
    length = arg[2]->Get(v8::String::New("length"))->ToObject()->Uint32Value();
}

for(int i = 0; i < length; i++)
{
    v8::Local<v8::Value> element = arg[2]->Get(i);
    v8::String::Utf8Value string(element->ToString());
    std::string str = std::string(*string);
    const char *cstr= str.c_str();
    arrv[i] = cstr;
    // do something with element
}
  // int arrc = sizeof(arrv) / sizeof(char*) - 1;

  run_Run(py_filepath_cstr, arrc, arrv);

  // TODO: Clean-up
  NanReturnValue(NanNew("world2"));
}

//
//
NAN_METHOD(Method4) {
  NanScope();

  initialize();

  // TODO: Clean-up
  NanReturnValue(NanNew("world4"));
}

//
//
NAN_METHOD(Method5) {
  NanScope();

  finalize();

  // TODO: Clean-up
  NanReturnValue(NanNew("world5"));
}

//
//
NAN_METHOD(Method6) {
  NanScope();

  // v8::String::Utf8Value py_filename_string_param(args[0]->ToString());
  // std::string param1 = std::string(*py_filename_string_param);
  // const char *py_filename_cstr = param1.c_str();

  char *arrv[] = {"program name", "arg1", "arg2"};
  int arrc = sizeof(arrv) / sizeof(char*) - 1;

  pysetargv(arrc,arrv);

  // TODO: Clean-up
  NanReturnValue(NanNew("world6"));
}

NAN_METHOD(Method7) {
  NanScope();

  v8::String::Utf8Value py_program_name_string(args[0]->ToString());
  std::string param0 = std::string(*py_program_name_string);
  const char *py_program_name_cstr = param0.c_str();

  setprogramname(py_program_name_cstr);

  // TODO: Clean-up
  NanReturnValue(NanNew("world7"));
}

void Init(Handle<Object> exports) {
  exports->Set(NanNew("simpleString"), NanNew<FunctionTemplate>(Method)->GetFunction());
  exports->Set(NanNew("simpleFile"), NanNew<FunctionTemplate>(Method2)->GetFunction());
  exports->Set(NanNew("runRun"), NanNew<FunctionTemplate>(Method3)->GetFunction());
  exports->Set(NanNew("initialize"), NanNew<FunctionTemplate>(Method4)->GetFunction());
  exports->Set(NanNew("finalize"), NanNew<FunctionTemplate>(Method5)->GetFunction());
  exports->Set(NanNew("setargv"), NanNew<FunctionTemplate>(Method6)->GetFunction());
  exports->Set(NanNew("setprogramname"), NanNew<FunctionTemplate>(Method7)->GetFunction());
}


NODE_MODULE(cpython, Init)
