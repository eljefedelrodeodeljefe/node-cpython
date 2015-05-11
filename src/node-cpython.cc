#include <nan.h>



using namespace v8;

extern "C" {
  #include <Python.h>

  int run_Run(int arrc, const char *arrv[]) {
    PyObject *pName, *pModule, *pDict, *pFunc;
    PyObject *pArgs, *pValue;
    int i;

    if (arrc < 3) {
        fprintf(stderr,"Usage: call pythonfile funcname [arrs]\n");
        return 1;
    }

    Py_Initialize();
    //pName = PyUnicode_DecodeFSDefault(arrv[1]);
    /* Error checking of pName left out */

    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL) {
        pFunc = PyObject_GetAttrString(pModule, arrv[2]);
        /* pFunc is a new reference */

        if (pFunc && PyCallable_Check(pFunc)) {
            pArgs = PyTuple_New(arrc - 3);
            for (i = 0; i < arrc - 3; ++i) {
                pValue = PyLong_FromLong(atoi(arrv[i + 3]));
                if (!pValue) {
                    Py_DECREF(pArgs);
                    Py_DECREF(pModule);
                    fprintf(stderr, "Cannot convert argument\n");
                    return 1;
                }
                /* pValue reference stolen here: */
                PyTuple_SetItem(pArgs, i, pValue);
            }
            pValue = PyObject_CallObject(pFunc, pArgs);
            Py_DECREF(pArgs);
            if (pValue != NULL) {
                printf("Result of call: %ld\n", PyLong_AsLong(pValue));
                Py_DECREF(pValue);
            }
            else {
                Py_DECREF(pFunc);
                Py_DECREF(pModule);
                PyErr_Print();
                fprintf(stderr,"Call failed\n");
                return 1;
            }
        }
        else {
            if (PyErr_Occurred())
                PyErr_Print();
            fprintf(stderr, "Cannot find function \"%s\"\n", arrv[2]);
        }
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    }
    else {
        PyErr_Print();
        fprintf(stderr, "Failed to load \"%s\"\n", arrv[1]);
        return 1;
    }
    Py_Finalize();
    printf("%s\n", "hello from within");

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
  int arc = 4;
  const char *arv[4];
  arv[1] = "multiply";
  arv[2] = "multiply";
  arv[3] = "2";
  arv[4] = "2";
  run_Run(arc, arv);

  // TODO: Clean-up
  NanReturnValue(NanNew("world2"));
}

void Init(Handle<Object> exports) {
  exports->Set(NanNew("simpleString"), NanNew<FunctionTemplate>(Method)->GetFunction());
  exports->Set(NanNew("simpleFile"), NanNew<FunctionTemplate>(Method2)->GetFunction());
  exports->Set(NanNew("runRun"), NanNew<FunctionTemplate>(Method3)->GetFunction());
}


NODE_MODULE(cpython, Init)
