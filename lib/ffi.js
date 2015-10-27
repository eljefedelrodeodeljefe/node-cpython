const ffi = require('./bindings.js').FFI
const Transform = require("stream").Transform
const util = require('util')
const path = require('path')

function FFI() {
  Transform.call(this, { objectMode: true })

  this.stream = {}
  this.fnName = ''
  this.fileName = ''
}
util.inherits(FFI, Transform)

FFI.prototype._require = function (fileName) {
  this.fileName = fileName
  return ffi.require()
}

FFI.prototype._init = function (stream, done) {
  this.stream = stream
  // register at least this event in order to finalize decently. W
  // e anyhow allow the user to have an own `end` event, which gets stacked up.
  this.stream.on('end', function() {
    // here `done` callback is the call below of Py_Finalize()
    done()
  })
}

FFI.prototype._run = function (fnName) {
  this.fnName = fnName
  this.stream.pipe(this)
}

FFI.prototype._pipe = function () {
  // ffi.init()
}

FFI.prototype._transform = function (chunk, encoding, done) {
  this._ffi(chunk, encoding)
  return done()
}

FFI.prototype._ffi = function (chunk, encoding) {
  // this function call mirrors already 100% of what we'll do down in C.
  // chunk is expected to be an array. TODO: check type above
  return ffi.run(path.basename(this.fileName, '.py'), this.fnName, 2, chunk)
}

/**
 * Registers a .on listener from aboves .ffi.on, by name of event and a users callback.
 * An `end` event will be stacked up, since it's registered already in .init()
 * @param  {String} ffiEventName The events name.
 * @param  {Function} ffiCb        Mandatory callback
 */
FFI.prototype._registerEvent = function (ffiEventName, ffiCb) {
  this.stream.on(ffiEventName, ffiCb)
}

module.exports = new FFI()
