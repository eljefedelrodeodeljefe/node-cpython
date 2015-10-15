'use strict'
const spawn = require('child_process').spawn;
const log = require('util').log;
const os = require('os');

const EventEmitter = require('events');
const ee = new EventEmitter();
const path = require('path');

const pathTo27 = 'deps/python/2.7'
const pathTo3X = 'deps/python/3'

let v27 = '2.7'
const v3x = '3.X'

/*
* This is the install script which runs on 'npm pre-install'.
* Not much magic. It just `./configure`s, `make && make install`s inside cpython directory.
* Most of the code here presents the users output and errors into the console and pretty-prints stuff.
*
*/

let configureOpts = [
                    '--prefix=' + process.cwd() + '/deps/python/'+ v27 ? v27 : v3x + '/build', // Fancy me  ¯\_(ツ)_/¯ -> Tying to be real clever here
                    '--exec-prefix=' + process.cwd() + '/deps/python/'+ v27 ? v27 : v3x + '/build', // Fancy me  ¯\_(ツ)_/¯
                    // "--with-PACKAGE=no",
                    '--without-doc-strings'
                  ];


let time = process.hrtime();
let configure27 = spawn('./configure', configureOpts, {cwd: pathTo27, stdio: 'inherit'})

configure27.on('close', function (code) {
  v27 = null //  ¯\_(ツ)_/¯
  let configure3X = spawn('./configure', configureOpts, {cwd: pathTo3X, stdio: 'inherit'})
  configure27.on('close', function (code) {

    let diff = process.hrtime(time);
    let prettyTime = '[' + ('0' + ~~(diff[0] / 60)).slice(-2) + ':' + ( '0'+ diff[0] % 60).slice(-2) + '] mm:ss\n'
    console.log('\n\n' + 'Configure: child process exited with code ' + code + '\n' + 'after ' + prettyTime + '\n\n');

    ee.emit('done:configure')
  })
});

ee.on('done:configure', function() {
  let time = process.hrtime();

  let makeOpts = ['-j' + os.cpus().length] // run make in parrallel with max. cpus
  let make27 = spawn('make', makeOpts, {cwd: pathTo27, stdio: 'inherit'})

  make27.on('close', function (code) {
    var make3X = spawn('make', makeOpts, {cwd: pathTo3X, stdio: 'inherit'})

    make27.on('close', function (code) {
      let diff = process.hrtime(time);
      let prettyTime = '[' + ('0' + ~~(diff[0] / 60)).slice(-2) + ':' + ( '0'+ diff[0] % 60).slice(-2) + '] mm:ss\n'
      console.log('\n\n' + 'Configure: child process exited with code ' + code + '\n' + 'after ' + prettyTime + '\n\n');

      ee.emit('done:make')
    })
  });
})

ee.on('done:make', function() {
  let time = process.hrtime();

  var makeInstall27 = spawn('make', ['install'], {cwd: pathTo27, stdio: 'inherit'})

  makeInstall27.on('close', function (code) {
    var makeInstall27 = spawn('make', ['install'], {cwd: pathTo3X, stdio: 'inherit'})

    makeInstall27.on('close', function (code) {
      let diff = process.hrtime(time);
      let prettyTime = '[' + ('0' + ~~(diff[0] / 60)).slice(-2) + ':' + ( '0'+ diff[0] % 60).slice(-2) + '] mm:ss\n'
      console.log('\n\n' + 'Configure: child process exited with code ' + code + '\n' + 'after ' + prettyTime + '\n\n');

      ee.emit('done:configure')
    })
  });
})
