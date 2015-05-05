#include <nan.h>
#include <Python.h>


using namespace v8;

extern "C" {
  #include <Python.h>

  void simple_File(int arrc, const char *arrv[])  {
      PyObject *pName, *pModule, *pDict, *pFunc;
      PyObject *pArgs, *pValue;
      int i;

      if (arrc < 3) {
         fprintf(stderr,"Usage: call pythonfile funcname [args]\n");
         // return 1;
         // TODO: Clean-up
      }

      Py_Initialize();
      // pName = PyString_FromString(arrv[1]);
      pName = PyString_FromString("multiply");
      /* Error checking of pName left out */

      pModule = PyImport_Import(pName);
      Py_DECREF(pName);

      if (pModule != NULL) {
          pFunc = PyObject_GetAttrString(pModule, arrv[2]);
          /* pFunc is a new reference */

          if (pFunc && PyCallable_Check(pFunc)) {
              pArgs = PyTuple_New(arrc - 3);
              for (i = 0; i < arrc - 3; ++i) {
                  pValue = PyInt_FromLong(atoi(arrv[i + 3]));
                  if (!pValue) {
                      Py_DECREF(pArgs);
                      Py_DECREF(pModule);
                      fprintf(stderr, "Cannot convert argument\n");
                      //return 1;
                      // TODO: Clean-up
                  }
                  /* pValue reference stolen here: */
                  PyTuple_SetItem(pArgs, i, pValue);
              }
              pValue = PyObject_CallObject(pFunc, pArgs);
              Py_DECREF(pArgs);
              if (pValue != NULL) {
                  printf("Result of call: %ld\n", PyInt_AsLong(pValue));
                  Py_DECREF(pValue);
              }
              else {
                  Py_DECREF(pFunc);
                  Py_DECREF(pModule);
                  PyErr_Print();
                  fprintf(stderr,"Call failed\n");
                  // return 1;
                  // TODO: Clean-up
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
          // return 1;
          // TODO: Clean-up
      }
      Py_Finalize();
  }
}


NAN_METHOD(Method) {
  NanScope();

  /*
  * This method takes the string from arguments and goes to
  * great length to convert from arguments to v8::String.. to
  * std::string to c-string, to eventually pass into cpython methods
  */
  // v8::String::Utf8Value py_file_string_param(args[0]->ToString());
  // std::string param = std::string(*py_file_string_param);
  // const char *py_file_cstr = param.c_str();

  const char *array[] = {"multiply", "multiply.py", "3", "2"};
  simple_File(4, array);

  // TODO: Clean-up
  NanReturnValue(NanNew("world"));
}

void Init(Handle<Object> exports) {
  exports->Set(NanNew("simpleFile"), NanNew<FunctionTemplate>(Method)->GetFunction());
}

NODE_MODULE(simpleFile, Init)
