
{
  "targets": [
    {
      "target_name": "cpython",
      "sources": [ "src/simpleString.cc" ],
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
