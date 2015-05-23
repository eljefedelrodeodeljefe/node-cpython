
{
  "variables": {
     "CC": "gcc",
     "BLDDIR" : "./deps/<(VERSION)/build/lib",
     "SRCDIR" : "./deps/<(VERSION)/build",
     "INCLUDES_DIR" : "<(SRCDIR)/include/python<(VERSION)",
     "VERSION" : "2.7",
     "OPT" : "-g",
     "INCLUDES" : "-I<(SRCDIR)/Include -I<(BLDDIR) -I<(SRCDIR)",
     "CFLAGS" :"<(OPT)",
     "CPPFLAGS" : "<(INCLUDES)",
     "LIBPYTHON" : "",
     #"LIBPYTHON" : "-I<(SRCDIR)/lib/libpython<(VERSION).a",
     "LIBS" : "-ldl -lreadline -ltermcap -lpthread -lutil",
     "LDFLAGS" : "-Xlinker",
     "SYSLIBS" : "-lm",
     "MODLIBS" : "",
     "ALLLIBS" : "-lpython<(VERSION) <(LIBPYTHON) <(MODLIBS) <(LIBS) <(SYSLIBS)"
    },
  "targets": [
    {
      "target_name": "node-cpython",
      "sources": [
        "lib/node-cpython.cc"
        ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")",
        '<(INCLUDES_DIR)'
      ],
      "libraries": [
        "<(ALLLIBS)",
      ]
    }
  ]
}
