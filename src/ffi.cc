#include "ffi.h"

#include <Python.h>

Nan::Persistent<v8::Function> FFI::constructor;

FFI::FFI() {
}

FFI::~FFI() {
}

void FFI::Init(v8::Local<v8::Object> exports) {
  Nan::HandleScope scope;

  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("FFI").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  Nan::SetPrototypeMethod(tpl, "require", Require);
  Nan::SetPrototypeMethod(tpl, "run", Run);

  constructor.Reset(tpl->GetFunction());
  exports->Set(Nan::New("FFI").ToLocalChecked(), tpl->GetFunction());
}

void FFI::New(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if (info.IsConstructCall()) {
    // Invoked as constructor: `new FFI(...)`
    FFI* obj = new FFI();
    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
  } else {
    // Invoked as plain function `FFI(...)`, turn into construct call.
    const int argc = 1;
    v8::Local<v8::Value> argv[argc] = { info[0] };
    v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
    info.GetReturnValue().Set(cons->NewInstance(argc, argv));
  }
}

/**
 * Entry point for FFI calls. Logic will be as follows:
 *
 * This implementation follows the CPython cuntion call examples and leans on it.
 * Since this was written for command line usage we just emulate argv, and argc.
 * As a full example you would have the followong function body, however we implement
 * this in parts callable by JS. Starting point is import: which file from where:
 *
 * ```c
 *   PyObject *pName, *pModule, *pDict, *pFunc;
 *   PyObject *pArgs, *pValue;
 *   int i;
 *   int arrc = 5;
 *
 *   // the below is everything the naked
 *   const char *arrv[] = { "", "multiply", "multiply", "3", "2"};
 *
 *   if (arrc < 3) {
 *       fprintf(stderr,"Usage: call pythonfile funcname [args]\n");
 *       return;
 *   }
 *
 *   Py_Initialize();
 *
 *   // as an example
 *   PySys_SetPath("../examples");
 *
 *   pName = PyString_FromString(arrv[1]);
 *   // Error checking of pName left out
 *   pModule = PyImport_Import(pName);
 *   Py_DECREF(pName); *
 *   if (pModule != NULL) {
 *       pFunc = PyObject_GetAttrString(pModule, arrv[2]);
 *       // pFunc is a new reference
 *       if (pFunc && PyCallable_Check(pFunc)) {
 *           pArgs = PyTuple_New(arrc - 3);
 *           for (i = 0; i < arrc - 3; ++i) {
 *               pValue = PyInt_FromLong(atoi(arrv[i + 3]));
 *               if (!pValue) {
 *                   Py_DECREF(pArgs);
 *                   Py_DECREF(pModule);
 *                   fprintf(stderr, "Cannot convert argument\n");
 *                   return;
 *               }
 *               // pValue reference stolen here:
 *               PyTuple_SetItem(pArgs, i, pValue);
 *           }
 *           pValue = PyObject_CallObject(pFunc, pArgs);
 *           Py_DECREF(pArgs);
 *           if (pValue != NULL) {
 *               printf("Result of call: %ld\n", PyInt_AsLong(pValue));
 *               Py_DECREF(pValue);
 *           }
 *           else {
 *               Py_DECREF(pFunc);
 *               Py_DECREF(pModule);
 *               PyErr_Print();
 *               fprintf(stderr,"Call failed\n");
 *               return;
 *           }
 *       }
 *       else {
 *           if (PyErr_Occurred())
 *               PyErr_Print();
 *           fprintf(stderr, "Cannot find function \"%s\"\n", arrv[2]);
 *       }
 *       Py_XDECREF(pFunc);
 *       Py_DECREF(pModule);
 *   }
 *   else {
 *       PyErr_Print();
 *       fprintf(stderr, "Failed to load \"%s\"\n", arrv[1]);
 *       return;
 *   }
 *   Py_Finalize();
 * ```
 */
void FFI::Require(const Nan::FunctionCallbackInfo<v8::Value>& info) {

}

const char* FFI::_ToCString(v8::Local<v8::Value> Str) {
  v8::String::Utf8Value v8_str(Str->ToString());
  std::string cpp_str = std::string(*v8_str);
  const char *arg = cpp_str.c_str();
  return arg;
}

void FFI::Run(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  PyObject *pName, *pModule, *pDict, *pFunc;
  PyObject *pArgs, *pValue;
  // oddly the cast didn't didn't for when used with PyObject_GetAttrString
  // Needed to do this by hand REVIEW
  // TODO: check refactor potential for the 3 steps. See Nan Example
  v8::String::Utf8Value v8_str(info[1]->ToString());
  std::string cpp_str = std::string(*v8_str);
  const char *fnname = cpp_str.c_str();

  const char *filename =  FFI::_ToCString(info[0]);

  int i; // loop
  // length already in specified in JS land
  const int arrc = info[2]->NumberValue();


  pName = PyString_FromString(filename);
  // Error checking of pName left out
  pModule = PyImport_Import(pName);
  Py_DECREF(pName); // keep track of the refrences

  if (pModule != NULL) {
    pFunc = PyObject_GetAttrString(pModule, fnname);
  } else {
    PyErr_Print();
    fprintf(stderr, "Failed to load \"%s\"\n", fnname);
    return;
  }
  // pFunc is a new reference
  if (pFunc && PyCallable_Check(pFunc)) {

  } else {
    if (PyErr_Occurred())
    PyErr_Print();
    fprintf(stderr, "Cannot find function \"%s\"\n", fnname);
    return;
  }

  // construct a python tuple for it to be the function's args
  pArgs = PyTuple_New(arrc);
  v8::Local<v8::Array> arr= v8::Local<v8::Array>::Cast(info[3]);

  // The below is taken from:
  //
  // int arrc = info[0]->NumberValue();
  //
  // Local<Array> arr= Local<Array>::Cast(args[2]);
  // char * arrv[] = {};
  //
  // for (size_t i = 0; i < arrc; i++) {
  //
  //   Local<Value> item = arr->Get(i);
  //   v8::String::Utf8Value array_string(item->ToString());
  //   std::string param = std::string(*array_string);
  //
  //   // first cast const char to char and then
  //   arrv[i] = strdup((char *) param.c_str());
  // }
  // last statement: http://stackoverflow.com/a/1788749/3580261
  for (i = 0; i < arrc; i++) {
    v8::Local<v8::Value> item = arr->Get(i);

    if (item->IsNumber()) {
      // REVIEW: because of deprecation warning from V8
      pValue = PyInt_FromLong(item->NumberValue()); // passes double
    } else if (item->IsString()) {

      v8::String::Utf8Value v8_argstr(item->ToString());
      std::string cpp_argstr = std::string(*v8_argstr);
      const char *argstr = cpp_str.c_str();

      pValue = PyString_FromString(argstr); // passes c-str.
    } else if (item->IsBoolean()) {
      // https://docs.python.org/2/c-api/bool.html
      pValue = item->BooleanValue() ? Py_True : Py_False; // passes boolean object
    }


    if (!pValue) {
      Py_DECREF(pArgs);
      Py_DECREF(pModule);
      fprintf(stderr, "Cannot convert argument\n");
      return;
    }
    // pValue reference stolen here:
    PyTuple_SetItem(pArgs, i, pValue);
  }


  pValue = PyObject_CallObject(pFunc, pArgs);
  Py_DECREF(pArgs);

  // do some type checking and send back return value to v8
  if (pValue != NULL) {
    printf("Result of call: %ld\n", PyInt_AsLong(pValue)); // TODO: cleanup

    if (PyInt_Check(pValue)) {
      // return a v8 local number castesd from and PyInt as long
      info.GetReturnValue().Set(v8::Local<v8::Number>(Nan::New((double) PyInt_AsLong(pValue))));
    } else if (PyString_Check(pValue)) {

      // info.GetReturnValue().Set(v8::Local<v8::String>(Nan::New((char*) PyString_AsString(pValue))).ToLocalChecked());
    } else if (PyBool_Check(pValue)) {
      /* code */
    }

    Py_DECREF(pValue);
  } else {
    Py_DECREF(pFunc);
    Py_DECREF(pModule);
    PyErr_Print();
    fprintf(stderr,"Call failed\n");
    return;
  }

  Py_XDECREF(pFunc);
  Py_DECREF(pModule);
  // context safely Ended
  // Needs finalization from Py_Finalize.
  // HINT: done outside of this scope from JS land
}
