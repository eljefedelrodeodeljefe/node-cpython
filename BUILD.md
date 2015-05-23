```bash
# from cpython root
./configure --prefix=$(pwd)/build --exec-prefix=$(pwd)/build
make
make install
```

Example makefile:

```makefile
# Makefile for embedded Python use demo.
# (This version originally written on Red Hat Linux 6.1;
# edit lines marked with XXX.)

# XXX The compiler you are using
CC=	 	gcc

# XXX Top of the build tree and source tree
blddir=		../../build/lib
srcdir=		../..

# Python version
VERSION=	2.7

# Compiler flags
OPT=		-g
INCLUDES=	-I$(srcdir)/Include -I$(blddir) -I$(srcdir)
CFLAGS=		$(OPT)
CPPFLAGS=	$(INCLUDES)

# The Python library
LIBPYTHON=	$(blddir)/libpython$(VERSION).a

# XXX edit LIBS (in particular) to match $(blddir)/Makefile
LIBS=		-ldl -lreadline -ltermcap -lpthread -lutil
LDFLAGS=	-Xlinker
SYSLIBS=	-lm
MODLIBS=
ALLLIBS=	$(LIBPYTHON) $(MODLIBS) $(LIBS) $(SYSLIBS)

# Build the demo applications
all:		demo loop call_class importexc
demo:		demo.o
		$(CC) $(LDFLAGS) demo.o $(ALLLIBS) -o demo

call_class:		call_class.o
		$(CC) $(LDFLAGS) call_class.o $(ALLLIBS) -o call_class

loop:		loop.o
		$(CC) $(LDFLAGS) loop.o $(ALLLIBS) -o loop

importexc:	importexc.o
		$(CC) $(LDFLAGS) importexc.o $(ALLLIBS) -o importexc

# Administrative targets

test:		demo
		./demo

COMMAND="print 'hello world'"
looptest:	loop
		./loop $(COMMAND)

clean:
		-rm -f *.o core

clobber:	clean
		-rm -f *~ @* '#'* demo loop importexc

realclean:	clobber

```
