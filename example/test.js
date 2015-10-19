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
module.repl()
