const ffi = require('./bindings.js').FFI
const Transform = require("stream").Transform
const util = require('util')

function FFI() {
  Transform.call(this, { objectMode: true })
  this.stream = {}
}
util.inherits(FFI, Transform)

FFI.prototype.require = function () {
  ffi.require()
}

FFI.prototype.init = function (stream, done) {
  this.stream = stream
  // register at least this event in order to finalize decently. W
  // e anyhow allow the user to have an own `end` event, which gets stacked up.
  this.stream.on('end', function() {
    // here `done` callback is the call below of Py_Finalize()
    done()
  })
}

FFI.prototype.run = function () {
  this.stream.pipe(this)
}

FFI.prototype.pipe = function () {
  // ffi.init()
}

FFI.prototype._transform = function (chunk, encoding, done) {
  this._ffi(chunk, encoding)
  return done()
}

FFI.prototype._ffi = function (chunk, encoding) {
  console.log(chunk[0] + chunk[1]);
  ffi.run("multiply", "multiply", 2, [3,2])
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
