var spawn = require('child_process').spawn;
var log = require('util').log;

var EventEmitter = require('events');
var ee = new EventEmitter();

var colors = require('./bin/colors.js');


// var configureOpts = ["--prefix=/Users/robert.lindstaedt/Documents/repos/node-cpython/deps/2.7/build",
//                      "--exec-prefix=/Users/robert.lindstaedt/Documents/repos/node-cpython/deps/2.7/build",
//                      "--without-PACKAGE"];
//
// // console.log('Starting directory: ' + process.cwd());
// // try {
// //   process.chdir('deps/2.7/cpython');
// //   console.log('New directory: ' + process.cwd());
// // }
// // catch (err) {
// //   console.log('chdir: ' + err);
// // }
// console.log('Spawn: started');
// var configure = spawn('./configure', configureOpts, {cwd: "./deps/2.7/cpython"})
//
// console.log('Configure: started');
// configure.stdout.on('data', function (data) {
//   console.log('stdout: ' + data);
// });
//
// configure.stderr.on('data', function (data) {
//   console.log('stderr: ' + data);
// });
//
// configure.on('close', function (code) {
//   console.log('Configure: child process exited with code ' + code);
//   ee.emit('done:configure')
// });
//
// ee.on('done:configure', function() {
//   console.log('Make: started');
//   var make = spawn('make', {cwd: "deps/2.7/cpython"})
//
//   make.stdout.on('data', function (data) {
//     console.log('stdout: ' + data);
//   });
//
//   make.stderr.on('data', function (data) {
//     console.log('stderr: ' + data);
//   });
//
//   make.on('close', function (code) {
//     console.log('Make: child process exited with code ' + code);
//     ee.emit('done:make')
//   });
// })
//
//
// ee.on('done:make', function() {
//   console.log('Make install: started');
//   var makeInstall = spawn('make install', {cwd: "deps/2.7/cpython"})
//   makeInstall.stdout.on('data', function (data) {
//     console.log('stdout: ' + data);
//   });
//
//   makeInstall.stderr.on('data', function (data) {
//     console.log('stderr: ' + data);
//   });
//
//   makeInstall.on('close', function (code) {
//     console.log('Make install: child process exited with code ' + code);
//     ee.emit('done:makeInstall')
//   });
// })
// ee.emit('done:make');
//
// // ee.on('done:makeInstall', function () {
// //   console.log('Changing workdir back from: ' + process.cwd());
// //   try {
// //     process.chdir('../../..');
// //     console.log('Workdir now: ' + process.cwd());
// //   }
// //   catch (err) {
// //     console.log('chdir: ' + err);
// //   }
// // })
