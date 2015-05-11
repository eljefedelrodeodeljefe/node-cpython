
{
  "targets": [
    {
      "target_name": "node-cpython",
      "sources": [
        "src/node-cpython.cc"
        ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")",
        './deps/2.7/cpython/Include',
        './deps/2.7/cpython'
      ],
      "libraries": [
        "-lpython2.7",
        "-lpthread",
        "-lm",
        "-ldl",
        "-lutil"
      ]
    }
  ]
}
