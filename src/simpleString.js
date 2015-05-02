var addon = require('bindings')('../build/Release/cpython');

console.log(addon.simpleString()); // 'world'
