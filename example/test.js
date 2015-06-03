'use strict';
var module = require('../index');


module.on('error', function(err) {console.log(err);})
//module.simpleFile('some', 'test');

module.simpleString("from time import time,ctime\nprint('Today is',ctime(time()))\n")

module.simpleFile("example/multiply_2.py", "multiply_2")
module.run()



//module._getListOfFiles("**/*.js", {silent: true} , cb)


var fn = function(err, files) {
  console.log(files);
}
module._getListOfFiles("src/**/*.js", {silent: true} , fn)
