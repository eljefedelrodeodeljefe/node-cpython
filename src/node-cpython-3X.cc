#include <nan.h>



using namespace v8;
using namespace std;

extern "C" {
  #include <Python.h>


}


// NAN_METHOD(simpleString) {
//   NanScope();
//
//   // TODO: Check whether this check is necessary and
//   // if not redundant to JS check
//   if (args.Length() != 1) {
//     NanThrowTypeError("Function expects one argument");
//     NanReturnUndefined();
//   }
//
//   /*
//   * This method takes the string from arguments and goes to
//   * great length to convert from arguments to v8::String.. to
//   * std::string to c-string, to eventually pass into cpython methods
//   */
//   v8::String::Utf8Value py_string_param(args[0]->ToString());
//   std::string param = std::string(*py_string_param);
//   const char *py_cstr = param.c_str();
//
//   simple_String(py_cstr);
//
//   // TODO: Clean-up
//   NanReturnValue(NanNew(0));
// }
//
// NAN_METHOD(simpleFile) {
//   NanScope();
//
//   // TODO: Check whether this check is necessary and
//   // if not redundant to JS check
//   // if (args.Length() != 1) {
//   //   NanThrowTypeError("Function expects one argument");
//   //   NanReturnUndefined();
//   // }
//
//   // v8::String::Utf8Value py_filepath_string_param(args[0]->ToString());
//   // std::string param0 = std::string(*py_filepath_string_param);
//   // const char *py_filepath_cstr = param0.c_str();
//   //
//   // v8::String::Utf8Value py_filename_string_param(args[1]->ToString());
//   // std::string param1 = std::string(*py_filename_string_param);
//   // const char *py_filename_cstr = param1.c_str();
//
//   FILE * fp;
//   fp = fopen(py_filepath_cstr, "r");
//
//   simple_File(fp, py_filename_cstr);
//
//   // TODO: Clean-up
//   NanReturnValue(NanNew(0));
// }
//
// NAN_METHOD(run) {
//   NanScope();
//
//   if (args.Length() != 3) {
//     NanThrowTypeError("Function expects one argument");
//     NanReturnUndefined();
//   }
//
//
//
//   v8::String::Utf8Value py_program_path_string(args[0]->ToString());
//   std::string param0 = std::string(*py_program_path_string);
//   const char *path = param0.c_str();
//
//   char *program_path;
//   strcpy(program_path, path);
//
//   printf("hello %s\n", program_path);
//
//   int arrc = args[1]->NumberValue();
//
//   Local<Array> arr= Local<Array>::Cast(args[2]);
//   char * arrv[] = {};
//
//   for (size_t i = 0; i < arrc; i++) {
//
//     Local<Value> item = arr->Get(i);
//     v8::String::Utf8Value array_string(item->ToString());
//     std::string param = std::string(*array_string);
//
//     // first cast const char to char and then
//     arrv[i] = strdup((char *) param.c_str());
//   }
//   // last statement: http://stackoverflow.com/a/1788749/3580261
//
//
//
//   run(program_path , arrc , arrv);
//
//   // TODO: Clean-up
//   NanReturnValue(NanNew(0));
// }
//
// //
// //
// NAN_METHOD(initialize) {
//   NanScope();
//
//   initialize();
//
//   // TODO: Clean-up
//   NanReturnValue(NanNew(0));
// }
//
// //
// //
// NAN_METHOD(finalize) {
//   NanScope();
//
//   finalize();
//
//   // TODO: Clean-up
//   NanReturnValue(NanNew(0));
// }
//
// //
// //
// NAN_METHOD(setArgv) {
//   NanScope();
//
//   // v8::String::Utf8Value py_filename_string_param(args[0]->ToString());
//   // std::string param1 = std::string(*py_filename_string_param);
//   // const char *py_filename_cstr = param1.c_str();
//
//   char *arrv[] = {"program name", "arg1", "arg2"};
//   int arrc = sizeof(arrv) / sizeof(char*) - 1;
//
//   pysetargv(arrc,arrv);
//
//   // TODO: Clean-up
//   NanReturnValue(NanNew(0));
// }
//
// NAN_METHOD(setProgramName) {
//   NanScope();
//
//   v8::String::Utf8Value py_program_name_string(args[0]->ToString());
//   std::string param0 = std::string(*py_program_name_string);
//   const char *py_program_name_cstr = param0.c_str();
//
//   setprogramname(py_program_name_cstr);
//
//   // TODO: Clean-up
//   NanReturnValue(NanNew(0));
// }
//
void Init(Handle<Object> exports) {
  // exports->Set(NanNew("simpleString"), NanNew<FunctionTemplate>(simpleString)->GetFunction());
  // exports->Set(NanNew("simpleFile"), NanNew<FunctionTemplate>(simpleFile)->GetFunction());
  // exports->Set(NanNew("runRun"), NanNew<FunctionTemplate>(run)->GetFunction());
  // exports->Set(NanNew("initialize"), NanNew<FunctionTemplate>(initialize)->GetFunction());
  // exports->Set(NanNew("finalize"), NanNew<FunctionTemplate>(finalize)->GetFunction());
  // exports->Set(NanNew("setargv"), NanNew<FunctionTemplate>(setArgv)->GetFunction());
  // exports->Set(NanNew("setprogramname"), NanNew<FunctionTemplate>(setProgramName)->GetFunction());
}


NODE_MODULE(cpython, Init)
