call_class: 	call_class.o

	gcc -o call_class call_class.o -L/usr/lib/python2.7/config -lpython2.7 -lpthread -lm -ldl -lutil

call_class.o:	call_class.c

	gcc -c call_class.c -I/Users/robert.lindstaedt/Documents/repos/node-cpython/deps/2.7/cpython/Include -I/Users/robert.lindstaedt/Documents/repos/node-cpython/deps/2.7/cpython


clean:

	rm call_class.o call_class
