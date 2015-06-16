#include <nan.h>



using namespace v8;
using namespace std;

extern "C" {
  #include <Python.h>

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

  int run(char *filename, char *somepath, int arrc, char *arrv[]) {

    Py_Initialize();
    PySys_SetArgvEx(arrc, arrv, 0);

    // Get a reference to the main module.
    PyObject* main_module = PyImport_AddModule("__main__");

    // Get the main module's dictionary
    PyObject* main_dict = PyModule_GetDict(main_module);

    // Execute two different files of
    // Python code in separate environments
    FILE* file = fopen("/Users/rob/Desktop/node-cpython/example/multiply_2.py", "r");
    PyRun_File(file, "example/multiply_2.py", Py_file_input, main_dict, main_dict);
    PyRun_SimpleString("import sys\n");

    Py_Finalize();

    return 0;
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


    char *name= {};
    strcpy(name, namestr);

    Py_SetProgramName(name);
    return 0;
  }


}


NAN_METHOD(simpleString) {
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
  NanReturnValue(NanNew(0));
}

NAN_METHOD(simpleFile) {
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
  NanReturnValue(NanNew(0));
}

NAN_METHOD(run) {
  NanScope();

  if (args.Length() != 4) {
    NanThrowTypeError("Function expects four argument");
    NanReturnUndefined();
  }

  //  first arg: filename
  v8::String::Utf8Value py_file_name_string(args[0]->ToString());
  std::string param0 = std::string(*py_file_name_string);
  const char *pname = param0.c_str();
  char *pfilename;
  strcpy(pfilename, pname);

  //  second arg: filepath
  v8::String::Utf8Value py_program_path_string(args[1]->ToString());
  std::string param2 = std::string(*py_program_path_string);
  const char *ppath = param2.c_str();
  char *program_path;
  strcpy(program_path, ppath);
  program_path ="/Users/rob/Desktop/node-cpython/example/multiply_2.py";


  //  third arg: array counter
  int arrc = args[2]->NumberValue();

  //  forth arg: array of args for py
  Local<Array> arr= Local<Array>::Cast(args[3]);
  char * arrv[] = {};

  for (int i = 0; i < arrc; i++) {

    Local<Value> item = arr->Get(i);
    v8::String::Utf8Value array_string(item->ToString());
    std::string param = std::string(*array_string);

    // first cast const char to char and then
    arrv[i] = strdup((char *) param.c_str());
  }
  // last statement: http://stackoverflow.com/a/1788749/3580261



  run(pfilename, program_path , arrc , arrv);

  // TODO: Clean-up
  NanReturnValue(NanNew(0));
}

//
//
NAN_METHOD(initialize) {
  NanScope();

  initialize();

  // TODO: Clean-up
  NanReturnValue(NanNew(0));
}

//
//
NAN_METHOD(finalize) {
  NanScope();

  finalize();

  // TODO: Clean-up
  NanReturnValue(NanNew(0));
}

//
//
NAN_METHOD(setArgv) {
  NanScope();

  // v8::String::Utf8Value py_filename_string_param(args[0]->ToString());
  // std::string param1 = std::string(*py_filename_string_param);
  // const char *py_filename_cstr = param1.c_str();

  //pysetargv(arrc,arrv);

  // TODO: Clean-up
  NanReturnValue(NanNew(0));
}

NAN_METHOD(setProgramName) {
  NanScope();

  v8::String::Utf8Value py_program_name_string(args[0]->ToString());
  std::string param0 = std::string(*py_program_name_string);
  const char *py_program_name_cstr = param0.c_str();

  setprogramname(py_program_name_cstr);

  // TODO: Clean-up
  NanReturnValue(NanNew(0));
}

void Init(Handle<Object> exports) {
  exports->Set(NanNew("simpleString"), NanNew<FunctionTemplate>(simpleString)->GetFunction());
  exports->Set(NanNew("simpleFile"), NanNew<FunctionTemplate>(simpleFile)->GetFunction());
  exports->Set(NanNew("run"), NanNew<FunctionTemplate>(run)->GetFunction());
  exports->Set(NanNew("initialize"), NanNew<FunctionTemplate>(initialize)->GetFunction());
  exports->Set(NanNew("finalize"), NanNew<FunctionTemplate>(finalize)->GetFunction());
  exports->Set(NanNew("setargv"), NanNew<FunctionTemplate>(setArgv)->GetFunction());
  exports->Set(NanNew("setprogramname"), NanNew<FunctionTemplate>(setProgramName)->GetFunction());
}


NODE_MODULE(cpython, Init)
