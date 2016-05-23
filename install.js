'use strict'
const spawn = require('child_process').spawn
const os = require('os')

const EventEmitter = require('events')
const ee = new EventEmitter()
const path = require('path')

const pathTo27 = 'deps/python/2.7'

let v27 = '2.7'

/*
* This is the install script which runs on 'npm pre-install'.
* Not much magic. It just `./configure`s, `make && make install`s inside cpython directory.
* Most of the code here presents the users output and errors into the console and pretty-prints stuff.
*
*/
let configureOpts = [
  `--prefix=${process.cwd()}/deps/python/${v27}/build`,
  `--exec-prefix=${process.cwd()}/deps/python/${v27}/build`,
  // "--with-PACKAGE=no",
  '--without-doc-strings',
  '-q'
]

// TODO: do both in a child process.
let time = process.hrtime()
let configure27 = spawn('./configure', configureOpts, {cwd: pathTo27, stdio: 'inherit'})

configure27.on('close', function (code) {
  let diff = process.hrtime(time)
  let prettyTime = '[' + ('0' + ~~(diff[0] / 60)).slice(-2) + ':' + ( '0'+ diff[0] % 60).slice(-2) + '] mm:ss'
  console.log('\n' + 'Configure: child process exited with code ' + code + '\n' + 'after ' + prettyTime + '\n')

  ee.emit('done:configure')
})

ee.on('done:configure', function() {
  let time = process.hrtime()

  let makeOpts = ['-j' + os.cpus().length, '--silent'] // run make in parrallel with max. cpus
  let make27 = spawn('make', makeOpts, {cwd: pathTo27, stdio: 'inherit'})

  make27.on('close', function (code) {
    let diff = process.hrtime(time)
    let prettyTime = '[' + ('0' + ~~(diff[0] / 60)).slice(-2) + ':' + ( '0'+ diff[0] % 60).slice(-2) + '] mm:ss'
    console.log('\n' + 'make: child process exited with code ' + code + '\n' + 'after ' + prettyTime + '\n')

    ee.emit('done:make')
  })
})

ee.on('done:make', function() {
  let time = process.hrtime()
  let installOpts = ['install','--silent']

  let makeInstall27 = spawn('make', installOpts, {cwd: pathTo27, stdio: 'inherit'})

  makeInstall27.on('close', function (code) {
    let diff = process.hrtime(time)
    let prettyTime = '[' + ('0' + ~~(diff[0] / 60)).slice(-2) + ':' + ( '0'+ diff[0] % 60).slice(-2) + '] mm:ss'
    console.log('\n' + 'make install: child process exited with code ' + code + '\n' + 'after ' + prettyTime + '\n')
  })
})
