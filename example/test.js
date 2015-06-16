'use strict';
var module = require('../index');


module.on('error', function(err) {console.log(err);})
//module.simpleFile('some', 'test');

module.simpleString("from time import time,ctime\nprint('Today is',ctime(time()))\n")

module.simpleFile("example/multiply.py", "multiply")
module.run("example/multiply_2.py", ["name1","name2", "name3"])



//module._getListOfFiles("**/*.js", {silent: true} , cb)


// var fn = function(err, files) {
//   console.log(files);
// }
// module._getListOfFiles("src/**/*.js", {silent: true} , fn)
//
//
//
// var b = function() { console.log('From within Create context')}
//
// module.pyCreateContext(b)
