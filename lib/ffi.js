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

FFI.prototype.init = function (stream) {
  // ffi.init()
  this.stream = stream
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

FFI.prototype._ffi = function (chunk, encoding, done) {
     // TODO
     console.log(chunk[0] + chunk[1]);
}



module.exports = new FFI()
