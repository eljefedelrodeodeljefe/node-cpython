#include "ffi.h"

#include <Python.h>

Nan::Persistent<v8::Function> FFI::constructor;

FFI::FFI() : main() {
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
