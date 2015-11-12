'use strict'
const spawn = require('child_process').spawn;
const EventEmitter = require('events');
const ee = new EventEmitter();

let smokeNodeGyp
let npmInstallGyp
let rebuild
let version

smokeNodeGyp = spawn('git', ['clone','-b','master','--depth=1', 'https://github.com/nodejs/node-gyp'], {cwd: '.', stdio: 'inherit'})

smokeNodeGyp.on('close', function () {
  ee.emit('endClone')
})

ee.on('endClone', function () {
  npmInstallGyp = spawn('npm', ['install','-production'], {cwd: './node-gyp', stdio: 'inherit'})

  npmInstallGyp.on('close' , function () {
    ee.emit('endInstall')
  })
})

ee.on('endInstall', function () {
  version = spawn('./node-gyp/bin/node-gyp.js', ['-v'], {cwd: '.', stdio: 'inherit'})
  rebuild = spawn('./node-gyp/bin/node-gyp.js', ['-v'], {cwd: '.', stdio: 'inherit'})

  rebuild.on('close' , function () {
    ee.emit('endRebuild')
  })
})

ee.on('endRebuild', function () {

})
