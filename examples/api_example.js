'use strict';
var ncpy = require('../index');

// hit "a = (1, 2, 3)"
//
//  or as smoke test...
//
// > a = 1
// > b = 2
// > a,b = b,a
// > a
// 2
// > b
// 1
// module.repl()

var Readable = require('stream').Readable;
var SomeStream = new Readable({ "objectMode": true })

SomeStream.push([1,2])
SomeStream.push([20,3])
SomeStream.push([3,40])
SomeStream.push([4,50])
SomeStream.push([55,66])
SomeStream.push(null)

ncpy.ffi
  // load the python script and intitialize the python interpreter
  .require('multiplication.py', { path: './examples' })
  // this expects a stream (in { objectMode: true })
  .init(SomeStream)
  // Tell `ncpy` what function to excute.
  .run('multiply')
  // add your own transform or any other stream here
  .pipe(/*some transform*/)
  .on('end', function() {
    console.log('ncpy -> Ending python context here.');
  })


ncpy.ffi('multiplication.py', 'multiply', [ 20, 5], function (err, res) {
  console.log('ncpy -> easy call to multiply, here');
  console.log('ncpy -> ' + res + '\n');
})
