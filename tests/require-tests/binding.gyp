
{
  "targets": [
    {
      "target_name": "nantest",
      "sources": [ "nantest.cc" ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ]
    }
  ]
}
