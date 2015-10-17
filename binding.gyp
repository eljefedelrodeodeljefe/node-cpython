
{
  "variables": {
     "CC": "gcc",
     "VERSION_2X" : "2.7",
     "VERSION_3X" : "3.X",
     "VERSION_MAX" : "3.5m",
     "SRCDIR_2X" : "./deps/python/<(VERSION_2X)/build",
     "SRCDIR_3X" : "./deps/python/<(VERSION_3X)/build",
     "BLDDIR_2X" : "<(SRCDIR_2X)/lib",
     "BLDDIR_3X" : "<(SRCDIR_3X)/lib",
     "INCLUDES_DIR_2X" : "<(SRCDIR_2X)/include/python<(VERSION_2X)",
     # please be aware of the below and REVIEW
     "INCLUDES_DIR_3X" : "<(SRCDIR_2X)/include/python<(VERSION_MAX)",
     "OPT" : "-g",
     "INCLUDES_2X" : "-I<(SRCDIR_2X)/Include -I<(BLDDIR_2X) -I<(SRCDIR_2X)",
     "INCLUDES_3X" : "-I<(SRCDIR_3X)/Include -I<(BLDDIR_3X) -I<(SRCDIR_3X)",
     "CFLAGS" :"<(OPT)",
     "CPPFLAGS_2X" : "<(INCLUDES_2X)",
     "CPPFLAGS_3X" : "<(INCLUDES_3X)",
    #  "LIBPYTHON" : "",
     "LIBPYTHON_2X" : "-I<(SRCDIR_2X)/lib/libpython<(VERSION_2X).a",
     "LIBPYTHON_3X" : "-I<(SRCDIR_2X)/lib/libpython<(VERSION_MAX).a",
     "LIBS" : "-ldl -lreadline -ltermcap -lpthread -lutil",
     "LDFLAGS" : "-Xlinker",
     "SYSLIBS" : "-lm",
     "MODLIBS" : "",
     "ALLLIBS_2X" : "-lpython<(VERSION_2X) <(LIBPYTHON_2X) <(MODLIBS) <(LIBS) <(SYSLIBS)",
     "ALLLIBS_3X" : "-lpython<(VERSION_MAX) <(LIBPYTHON_3X) <(MODLIBS) <(LIBS) <(SYSLIBS)"
    },
  "targets": [
    {
      "target_name": "node-cpython-2X",
      "sources": [
        "src/addon.cc",
        "src/node-cpython-2X.cc"
        ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")",
        '<(INCLUDES_DIR_2X)'
      ],
      "libraries": [
        "<(ALLLIBS_2X)",
      ]
    }#,
    # {
    #   "target_name": "node-cpython-3X",
    #   "sources": [
    #     "src/node-cpython-3X.cc"
    #     ],
    #   "include_dirs": [
    #     "<!(node -e \"require('nan')\")",
    #     '<(INCLUDES_DIR_3X)'
    #   ],
    #   "libraries": [
    #     "<(ALLLIBS_3X)",
    #   ]
    # }
  ]
}
