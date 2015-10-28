'use strict'
var spawn = require('child_process').spawn

let gitOpts = ['clone','-b', 'v2.1.3','--depth=1','https://github.com/bnoordhuis/node-buffertools'];
let clone = spawn('git', gitOpts, {cwd: './tests/smoke', stdio: 'inherit'})

clone.on('close', function (code) {
  
});
