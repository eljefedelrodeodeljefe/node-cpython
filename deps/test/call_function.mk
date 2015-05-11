call_function: 	call_function.o

	gcc -o call_function call_function.o -L/usr/lib/python2.7/config -I/usr/lib/python2.7 -lpython2.7 -lpthread -lm -ldl -lutil


call_function.o:call_function.c

	gcc -c call_function.c -I/Users/robert.lindstaedt/Documents/repos/node-cpython/deps/2.7/cpython/Include -I/Users/robert.lindstaedt/Documents/repos/node-cpython/deps/2.7/cpython -I/usr/lib/python2.7


clean:

	rm call_function.o call_function
