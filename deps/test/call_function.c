// call_function.c - A sample of calling python functions from C code
//
#include <Python.h>

int main(int argc, char *argv[])
{
	setenv("PYTHONPATH",".",1);
	printf("1 ");
	int i;
	PyObject *pName, *pModule, *pDict, *pFunc, *pArgs, *pValue, *moduleName;

	if (argc < 3)
	{
		printf("Usage: exe_name python_source function_name\n");
		return 1;
	}
	printf("2 ");
	char * path;
	/*
	/Users/robert.lindstaedt/Documents/repos/node-cpython/deps/test/some/lib/python27.zip
	/Users/robert.lindstaedt/Documents/repos/node-cpython/deps/test/some/lib/python2.7/
	/Users/robert.lindstaedt/Documents/repos/node-cpython/deps/test/some/lib/python2.7/plat-darwin
	/Users/robert.lindstaedt/Documents/repos/node-cpython/deps/test/some/lib/python2.7/plat-mac
	/Users/robert.lindstaedt/Documents/repos/node-cpython/deps/test/some/lib/python2.7/plat-mac/lib-scriptpackages
	/Users/robert.lindstaedt/Documents/repos/node-cpython/deps/test/some/lib/python2.7/
	../../Extras/lib/python
	/Users/robert.lindstaedt/Documents/repos/node-cpython/deps/test/some/lib/python2.7/lib-tk
	/Users/robert.lindstaedt/Documents/repos/node-cpython/deps/test/some/lib/python2.7/lib-old
	/Users/robert.lindstaedt/Documents/repos/node-cpython/deps/test/some/lib/python2.7/lib-dynload

	--prefix=PREFIX         install architecture-independent files in PREFIX
												[/usr/local]
	--exec-prefix=EPREFIX   install architecture-dependent files in EPREFIX
												[PREFIX]
  --libexecdir=DIR        program executables [EPREFIX/libexec]
  --libdir=DIR            object code libraries [EPREFIX/lib]
	./configure --prefix=/Users/robert.lindstaedt/Documents/repos/node-cpython/deps/2.7/python --exec-prefix=/Users/robert.lindstaedt/Documents/repos/node-cpython/deps/2.7/python --libdir=/Users/robert.lindstaedt/Documents/repos/node-cpython/deps/2.7/cpython/Lib

	*/
	char pySearchPath[] = "/usr/";
	char pyName[] = "pyName";
	Py_SetPythonHome(pySearchPath);
	Py_SetProgramName(pyName);
	printf("3 ");
	path = Py_GetPythonHome();
	printf(" %s ", path);

	//char * pySetName;
	//pySetName = Py_GetPath();
	//printf(" %s ", pySetName);
	// Initialize the Python Interpreter
	int init;

	Py_Initialize();
	init = Py_IsInitialized();
	printf("Is initialized with %i", init);
	// Build the name object

	moduleName = "/call_function/";


	// Load the module object


	// pDict is a borrowed reference


	// pFunc is also a borrowed reference




	// Finish the Python Interpreter
	Py_Finalize();

	return 0;
}
