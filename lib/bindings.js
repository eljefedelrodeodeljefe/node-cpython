var addon = require('bindings')('node-cpython')

module.exports = {
  NodeCPython2X: addon.NodeCPython2X,
  NodeCPython3X: addon.NodeCPython3X,
  FFI: new addon.FFI()
}
