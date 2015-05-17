var spawn = require('child_process').spawn;

var EventEmitter = require('events');
var ee = new EventEmitter();


var configureOpts = ["--prefix=" + process.cwd() + "deps/2.7/cpython/build",  "--exec-prefix=" + process.cwd() + "deps/2.7/cpython/build"];

// console.log('Starting directory: ' + process.cwd());
// try {
//   process.chdir('deps/2.7/cpython');
//   console.log('New directory: ' + process.cwd());
// }
// catch (err) {
//   console.log('chdir: ' + err);
// }

var configure = spawn('./configure', configureOpts, {cwd: "deps/2.7/cpython"})


configure.stdout.on('data', function (data) {
  console.log('stdout: ' + data);
});

configure.stderr.on('data', function (data) {
  console.log('stderr: ' + data);
});

configure.on('close', function (code) {
  console.log('Configure: child process exited with code ' + code);
  ee.emit('done:configure')
});

ee.on('done:configure', function() {
  var make = spawn('make', {cwd: "deps/2.7/cpython"})
  make.stdout.on('data', function (data) {
    console.log('stdout: ' + data);
  });

  make.stderr.on('data', function (data) {
    console.log('stderr: ' + data);
  });

  make.on('close', function (code) {
    console.log('Make: child process exited with code ' + code);
    ee.emit('done:make')
  });
})

ee.on('done:make', function() {
  var makeInstall = spawn('make install', {cwd: "deps/2.7/cpython"})
  makeInstall.stdout.on('data', function (data) {
    console.log('stdout: ' + data);
  });

  makeInstall.stderr.on('data', function (data) {
    console.log('stderr: ' + data);
  });

  makeInstall.on('close', function (code) {
    console.log('Make install: child process exited with code ' + code);
    ee.emit('done:makeInstall')
  });
})

// ee.on('done:makeInstall', function () {
//   console.log('Changing workdir back from: ' + process.cwd());
//   try {
//     process.chdir('../../..');
//     console.log('Workdir now: ' + process.cwd());
//   }
//   catch (err) {
//     console.log('chdir: ' + err);
//   }
// })
