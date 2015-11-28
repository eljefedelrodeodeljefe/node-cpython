var addon = require('bindings')('node-cpython-2X')

module.exports = {
  NodeCPython2X: addon.NodeCPython2X,
  FFI: new addon.FFI()
}
