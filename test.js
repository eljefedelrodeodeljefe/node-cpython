'use strict';
var module = require('./index');


module.on('error', function(err) {console.log(err);})
module.simpleFile('some', 'test', 'it is');
