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
rs.push([3,2]);
rs.push([7,8]);
rs.push([7,8]);
rs.push([7,8]);
rs.push([7,8]);
rs.push(null);




module.ffi
  .require('multiply.py', { path: '/Users/Jefe/Documents/repos/node-cpython/examples' }) // intitializes python
  .init(rs /*, options {objectMode: true}*/)
  .run() // expects events from above
  .pipe(/*some transform*/) // add your own transform or any other stream here
  .on('end', function() {
    console.log('Ended python context here.');
  })

module.ffi(/*path to function*/)
