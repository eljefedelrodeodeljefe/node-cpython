
{
  "targets": [
    {
      "target_name": "node-cpython",
      "sources": [
        "src/node-cpython.cc"
        ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")",
        './lib/cpython/Include',
        './lib/cpython'
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
