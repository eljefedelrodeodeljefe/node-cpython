var spawn = require('child_process').spawn;
var log = require('util').log;

var EventEmitter = require('events');
var ee = new EventEmitter();

var colors = require('./bin/colors.js');




/*
* This is the install script which runs on 'npm pre-install'.
* Not much magic. It just `./configure`s, `make && make install`s inside cpython directory.
* Most of the code here presents the users output and errors into the console and pretty-prints stuff.
*
*/

var configureOpts = ["--prefix=" + process.cwd() + "/deps/2.7/build",
                     "--exec-prefix=" + process.cwd() + "/deps/2.7/build",
                     "--with-PACKAGE=no"];

var installTime = process.hrtime();
var time = process.hrtime();
var configure = spawn('./configure',configureOpts, {cwd: "deps/2.7/cpython"})

configure.stdout.on('data', function (data) { console.log(colors + data); });
configure.stderr.on('data', function (data) { console.log(colors+ 'ERR: ' + data); });

configure.on('close', function (code) {
  var diff = process.hrtime(time);
  var prettyTime = '[' + ('0' + ~~(diff[0] / 60)).slice(-2) + ':' + ( '0'+ diff[0] % 60).slice(-2) + '] mm:ss\n'
  console.log('\n\n\n' + colors + 'Configure: child process exited with code after' + code + '\n' + colors + 'after ' + prettyTime + '\n\n');
  ee.emit('done:configure')
});



ee.on('done:configure', function() {
  var time = process.hrtime();
  var make = spawn('make', {cwd: "deps/2.7/cpython"})

  make.stdout.on('data', function (data) { console.log(colors + data); });
  make.stderr.on('data', function (data) { console.log(colors+ 'ERR: ' + data); });

  make.on('close', function (code) {
    var diff = process.hrtime(time);
    var prettyTime = '[' + ('0' + ~~(diff[0] / 60)).slice(-2) + ':' + ( '0'+ diff[0] % 60).slice(-2) + '] mm:ss\n'
    console.log('\n\n\n' + colors + 'Make: child process exited with code ' + code + '\n'+ colors + 'after ' + diff + '\n\n');
    ee.emit('done:make')
  });
})


ee.on('done:make', function() {
  var time = process.hrtime();
  var makeInstall = spawn('make', ['install'], {cwd: "deps/2.7/cpython"})

  makeInstall.stdout.on('data', function (data) { console.log(colors + data); });
  makeInstall.stderr.on('data', function (data) { console.log(colors+ 'ERR: ' + data); });

  makeInstall.on('close', function (code) {
    var diff = process.hrtime(time);
    var prettyTime = '[' + ('0' + ~~(diff[0] / 60)).slice(-2) + ':' + ( '0'+ diff[0] % 60).slice(-2) + '] mm:ss\n'
    console.log('\n\n\n' + colors + 'Make install: child process exited with code ' + code + '\n'+ colors + 'after ' + prettyTime + '\n\n');
    ee.emit('done:makeInstall')
  });
})


ee.on('done:makeInstall', function() {
  var installDiff = process.hrtime(installTime);
  // pretty hrtime -> [$mm:$ss] mm:ss
  var prettyTime = '[' + ('0' + ~~(installDiff[0] / 60)).slice(-2) + ':' + ( '0'+ installDiff[0] % 60).slice(-2) + '] mm:ss\n'
  console.log('\n\n\n' + colors + 'Install took ' + prettyTime + '\n\n');
})
