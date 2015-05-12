// A sample of python embedding (calling python classes from within C++ code)
//
#ifdef WIN32
#include <Windows.h>
#else
#define Sleep(x) sleep(x/1000)
#endif
#include <Python.h>


int main(int argc, char *argv[])
{
    PyObject *pName, *pModule, *pDict, *pClass, *pInstance;
    int i;

    if (argc < 4) 
    {
        fprintf(stderr,"Usage: exe_name python_filename class_name function_name[args]\n");
        return 1;
    }

    Py_Initialize();
    pName = PyString_FromString(argv[1]);
    if (pName == NULL)
    {
        PyErr_Print();
	fprintf(stderr, "Failed to create name object \"%s\"\n", argv[1]);
        return 1;
    }
    
    pModule = PyImport_Import(pName);
    if (pModule == NULL) 
    {
        PyErr_Print();
	fprintf(stderr, "Failed to create module object \"%s\"\n", argv[1]);
        return 1;
    }

    pDict = PyModule_GetDict(pModule);
    /* pDict is a borrowed reference */

    //////////////////////////////////////////////////////////////////////////
    // Call python classes
    //////////////////////////////////////////////////////////////////////////
   
    // Build callable class name 
    pClass = PyDict_GetItemString(pDict, argv[2]);
    if (pClass == NULL || !PyCallable_Check(pClass))
    {
        PyErr_Print();
        fprintf(stderr, "The class \"%s\" is not callable\n", argv[2]);
        return 1;
    }

    // Create instance
    pInstance = PyObject_CallObject(pClass, NULL); 
    if (pInstance == NULL)
    {
        PyErr_Print();
        fprintf(stderr, "Failed to create the class instance \"%s\"\n", argv[2]);
        return 1;
    }

    PyObject_CallMethod(pInstance, "start", NULL);
	
    i = 0;
    while(i<10)
    {
		printf("Printed from C thread...\n");
	
		// !!!Important!!! C thread will not release CPU to Python thread without the following call.
 		PyObject_CallMethod(pInstance, "join", "(f)", 0.001);		
		Sleep(1000);
		i++;
    }
	
    printf("C thread join and wait for Python thread to complete...\n");
    PyObject_CallMethod(pInstance, "join", NULL);		
    
    // Clean up
    Py_DECREF(pModule);
    Py_DECREF(pName);
    Py_Finalize();
    
    printf("Program completed gracefully.\n");

    return 0;
}
