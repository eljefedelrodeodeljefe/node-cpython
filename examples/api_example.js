'use strict';
var module = require('../index');

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

var rs = new Readable({ "objectMode": true });
rs.push([1,2]);
rs.push([20,3]);
rs.push([3,40]);
rs.push([4,50]);
rs.push([55,66]);
rs.push(null);




module.ffi
  .require('multiply.py', { path: '/Users/Jefe/Documents/repos/node-cpython/examples' }) // load the python script and intitialize the python interpreter
  .init(rs) // this epects the stream to be in { objectMode: true }
  .run('multiply') // Tell node what function to excute.
  .pipe(/*some transform*/) // add your own transform or any other stream here
  .on('end', function() {
    console.log('Ended python context here.');
  })

module.ffi(/*path to function*/)
