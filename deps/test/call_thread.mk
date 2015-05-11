call_thread: 	call_thread.o

	gcc -o call_thread call_thread.o -L/usr/lib/python2.7/config -lpython2.7 -lpthread -lm -ldl -lutil


call_thread.o:	call_thread.c

	gcc -c call_thread.c -I/Users/robert.lindstaedt/Documents/repos/node-cpython/deps/2.7/cpython/Include -I/Users/robert.lindstaedt/Documents/repos/node-cpython/deps/2.7/cpython


clean:

	rm call_thread.o call_thread
