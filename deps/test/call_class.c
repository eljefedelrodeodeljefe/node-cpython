// A sample of python embedding (calling python classes from within C++ code)
//
// To run:
// 1) setenv PYTHONPATH ${PYTHONPATH}:./
// 2) call_class py_source Multiply multiply
// 3) call_class py_source Multiply multiply 9 8
//

#include <Python.h>

int main(int argc, char *argv[])
{
    PyObject *pName, *pModule, *pDict, *pClass, *pInstance, *pValue;
    int i, arg[8];

    if (argc < 4)
    {
        fprintf(stderr,"Usage: call python_filename class_name function_name\n");
        return 1;
    }
    char pySearchPath[] = "/Users/robert.lindstaedt/Documents/repos/node-cpython/deps/2.7/cpython/Lib";
    Py_SetPythonHome(pySearchPath);

    Py_Initialize();
    pName = PyString_FromString(argv[1]);
    pModule = PyImport_Import(pName);
	pDict = PyModule_GetDict(pModule);

    // Build the name of a callable class
    pClass = PyDict_GetItemString(pDict, argv[2]);

    // Create an instance of the class
    if (PyCallable_Check(pClass))
    {
		pInstance = PyObject_CallObject(pClass, NULL);
    }

    // Build parameter list
    if( argc > 4 )
    {
    	for (i = 0; i < argc - 4; i++)
    	{
        	arg[i] = atoi(argv[i + 4]);
    	}
		// Call a method of the class with two parameters
    	pValue = PyObject_CallMethod(pInstance, argv[3], "(ii)", arg[0], arg[1]);

    } else
    {
		// Call a method of the class with no parameters
    	pValue = PyObject_CallMethod(pInstance, argv[3], NULL);
    }

	if (pValue != NULL)
    {
		printf("Return of call : %d\n", PyInt_AsLong(pValue));
		Py_DECREF(pValue);
    }
    else
    {
		PyErr_Print();
    }

    // Clean up
    Py_DECREF(pModule);
    Py_DECREF(pName);
    Py_Finalize();

    return 0;
}
