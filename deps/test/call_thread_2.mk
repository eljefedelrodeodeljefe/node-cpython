call_thread_2: 	call_thread_2.o

	gcc -o call_thread_2 call_thread_2.o -L/usr/lib/python2.7/config -lpython2.7 -lpthread -lm -ldl -lutil


call_thread_2.o: call_thread_2.c

	gcc -c call_thread_2.c -I/Users/robert.lindstaedt/Documents/repos/node-cpython/deps/2.7/cpython/Include -I/Users/robert.lindstaedt/Documents/repos/node-cpython/deps/2.7/cpython


clean:

	rm call_thread_2.o call_thread_2
