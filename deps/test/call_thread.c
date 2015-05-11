// A sample of python embedding (calling python functions from within C code)
// 
#include <Python.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#ifdef WIN32	// Windows includes
#include <Windows.h>
#include <process.h>
#define sleep(x) Sleep(1000*x)
HANDLE handle;
#else	// POSIX includes
#include <pthread.h>
pthread_t mythread;
#endif

void ThreadProc(void*);

#define NUM_ARGUMENTS 5
typedef struct 
{
   int argc;
   char *argv[NUM_ARGUMENTS]; 
} CMD_LINE_STRUCT;

int main(int argc, char *argv[])
{
    int i;
    CMD_LINE_STRUCT cmd;

    cmd.argc = argc;
    for( i = 0; i < NUM_ARGUMENTS; i++ )
    {
    	cmd.argv[i] = argv[i];
    }

    if (argc < 3) 
    {
        fprintf(stderr,"Usage: call python_filename function_name [args]\n");
        return 1;
    }

    // Create a thread
#ifdef WIN32
    // Windows code
    handle = (HANDLE) _beginthread( ThreadProc,0,&cmd);
#else
    // POSIX code
    pthread_create( &mythread, NULL, ThreadProc, (void*)&cmd );
#endif

    // Random testing code
    for(i = 0; i < 10; i++)
    {
    	printf("Printed from the main thread.\n");
		sleep(1);
    }

    printf("Main Thread waiting for My Thread to complete...\n");

    // Join and wait for the created thread to complete...
#ifdef WIN32
    // Windows code
    WaitForSingleObject(handle,INFINITE);
#else
    // POSIX code
    pthread_join(mythread, NULL);
#endif

    printf("Main thread finished gracefully.\n");

    return 0;
}

void ThreadProc( void *data )
{
    PyObject *pName, *pModule, *pDict, *pFunc;
    PyThreadState *mainThreadState, *myThreadState, *tempState;
    PyInterpreterState *mainInterpreterState;
    
    CMD_LINE_STRUCT* arg = (CMD_LINE_STRUCT*)data;

    // Initialize python inerpreter
    Py_Initialize();
        
    // Initialize thread support
    PyEval_InitThreads();

    // Save a pointer to the main PyThreadState object
    mainThreadState = PyThreadState_Get();

    // Get a reference to the PyInterpreterState
    mainInterpreterState = mainThreadState->interp;

    // Create a thread state object for this thread
    myThreadState = PyThreadState_New(mainInterpreterState);

	// Release global lock
	PyEval_ReleaseLock();
    
	// Acquire global lock
	PyEval_AcquireLock();

    // Swap in my thread state
    tempState = PyThreadState_Swap(myThreadState);

    // Now execute some python code (call python functions)
    pName = PyString_FromString(arg->argv[1]);
    pModule = PyImport_Import(pName);

    // pDict and pFunc are borrowed references 
    pDict = PyModule_GetDict(pModule);
    pFunc = PyDict_GetItemString(pDict, arg->argv[2]);

    if (PyCallable_Check(pFunc)) 
    {
        PyObject_CallObject(pFunc, NULL);
    }
    else {
        PyErr_Print();
    }

    // Clean up
    Py_DECREF(pModule);
    Py_DECREF(pName);

    // Swap out the current thread
    PyThreadState_Swap(tempState);

	// Release global lock
	PyEval_ReleaseLock();

    // Clean up thread state
    PyThreadState_Clear(myThreadState);
    PyThreadState_Delete(myThreadState);

    Py_Finalize();
    printf("My thread is finishing...\n");

    // Exiting the thread
#ifdef WIN32
    // Windows code
    _endthread();
#else
    // POSIX code
    pthread_exit(NULL);
#endif
}
