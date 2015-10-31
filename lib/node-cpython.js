'use strict'
const EventEmitter = require('events')
const util = require('util')
const glob = require('glob')
const NodeCPython2X = require('./bindings.js').NodeCPython2X
const FFI = require('./ffi.js')

/**
* Implements the Ncpy Python interpreter
* @class Ncpy
*/
function Ncpy () {
  EventEmitter.call(this)
  // default options
  this.opts = {
    version: 2.7 // 2.7 or 3.5
  }
  this.programs = []
}
util.inherits(Ncpy, EventEmitter)

/**
 * intitialze this module from init function rather than over constructor
 *
 * @example
 * const cpython = require('node-cpython')
 *
 * let options = {
 * 	\/\* Options go in here \*\/
 * }
 *
 * cpython.init(options)
 * \/\/ available options [here]{@link https://github.com/eljefedelrodeodeljefe/node-cpython#options}
 *
 * @param  {Object} arguments object where keys represent toggles of individual features or point to files
 * @return {Object}           returns itself is chainable
 */
Ncpy.prototype.init = function () {
  // let args = Array.prototype.slice.call(arguments)
}

/**
* Executes any number of Python source code files.
* This is JS userland API and automates and abstracts many choices of the
* below C-API. If you want to have more control, please use the below methods.
*
* @example
* 'use strict'
* let cpython = require('cpython')
*
* cpython.on('error', function(err) {console.log(err)})
*
* cpython.run('[example/**\/*.py', function(result) { console.log(result) })
*
* @param {string|string[]} glob - a glob of valid .py files
* @param {callback} [cb] - Optional callback
*/
// TODO: actually implement callbacks
Ncpy.prototype.run = function (glob, callback) {
  // let args = Array.prototype.slice.call(arguments)

  // //TODO: check if condition is valid at all (after first review: seems to be the case)
  // if (args.length !== 2 || typeof filepath !== 'string' || filepath instanceof String) {
  //
  //   let err = new Error('Method 'simpleString' expects one argument, which must be a string')
  //   err.name = 'InputError'
  //
  //   this.emit('error', err)
  //   return
  // }

  /**
  * call simpleFile from below and pass args as string
  */
  // nanCPython.runRun(glob, args[1].length, args[1])

  // TODO: Check if chainability is actually usuful
  return this
}

/**
*
*/
Ncpy.prototype.anyFile = function (glob, callback) {

}

/**
*
*/
Ncpy.prototype.runString = function (/* list of args*/) {
  let args = Array.prototype.slice.call(arguments)

  // http://stackoverflow.com/a/9541411/3580261 for below
  NodeCPython2X.runString(args[0])
}

/**
*
*/
Ncpy.prototype.repl = function (/* list of args*/) {
  // let args = Array.prototype.slice.call(arguments)

  // http://stackoverflow.com/a/9541411/3580261 for below
  NodeCPython2X.initialize()
  NodeCPython2X.addModule()
  NodeCPython2X.getDict()

  process.stdin.setEncoding('utf8')

  process.stdin.on('readable', function () {
    let chunk = process.stdin.read()
    process.stdout.write('> ')
    if (chunk !== null) {
      // TODO: implement pass-down to interactiveLoop
      NodeCPython2X.runString(chunk)
    }
  })

  process.stdin.on('end', function () {
    process.stdout.write('-------\nPyREPL connection end.\n')
    NodeCPython2X.finalize()
  })

  process.on('SIGINT', function () {
    process.stdout.write('\n-------\nPyREPL closed.\n')

    NodeCPython2X.finalize()
    process.exit(0)
  })
}

/**
* Executes the Python source code from command.
* See also [Python docs]{@link https://docs.python.org/2/c-api/veryhigh.html#c.PyRun_SimpleStringFlags} for Reference
*
* @example
* 'use strict'
* let cpython = require('cpython')
*
* cpython.on('error', function(err) {console.log(err)})
*
* cpython.simpleString('from time import time,ctime\nprint 'Today is',ctime(time())\n')
*
* @param {string} str - String of python denoted code
* @param {string|string[]} [flags=null] - Compiler flag or array of flags for CPython
* @param {callback} [cb] - Optional callback
*/
// TODO: actually implement compiler flags and callbacks
Ncpy.prototype.simpleString = function (str, flags, cb) {
  let args = Array.prototype.slice.call(arguments)
  if (args.length !== 1 || typeof str !== 'string' || str instanceof String) {
    let err = new Error('Method `simpleString` expects one argument, which must be a string')
    err.name = 'InputError'

    this.emit('error', err)
    return
  }

  NodeCPython2X.initialize()
  NodeCPython2X.simpleString(args[0])
  NodeCPython2X.finalize()

  return this
}

/**
* Executes the Python source code from file.
* Similar to simpleString(), but the Python source code is read from a file
* instead of an in-memory string. filename should be the name of the file.
* See also [Python docs]{@link https://docs.python.org/2/c-api/veryhigh.html#c.PyRun_SimpleFileExFlags} for Reference
*
* @example
* 'use strict'
* let cpython = require('cpython')
*
* cpython.on('error', function(err) {console.log(err)})
*
* cpython.simpleFile('example/multiply.py', 'multiply.py')
* // passing the filename seems to be a necessity of the C-API
* // TODO: this will only last very shortly and be made optional
*
* @param {string} filepath - String of filepath
* @param {string} filename - String of filename
* @param {string|string[]} [flags=null] - Compiler flag or array of flags for CPython
* @param {callback} [cb] - Optional callback
*/
// TODO: actually implement compiler flags and callbacks
Ncpy.prototype.simpleFile = function (filepath, filename, flags, callback) {
  let args = Array.prototype.slice.call(arguments)

  // TODO: check if condition is valid at all (after first review: seems to be the case)
  if (args.length !== 2 || typeof filepath !== 'string' || filepath instanceof String) {
    let err = new Error('Method `simpleString` expects one argument, which must be a string')
    err.name = 'InputError'

    this.emit('error', err)
    return
  }

  /**
  * call simpleFile from below and pass args as string
  */
  // nanCPython.simpleFile(filepath, filename)

  // TODO: Check if chainability is actually usuful
  return this
}

/**
* [callForeignFunction description]
* @param  {string} file        [description]
* @param  {string} functioname [description]
* @return {function}             [description]
*/
Ncpy.prototype.callForeignFunction = function (file, functioname) {
  // TODO: Check if chainability is actually usuful
  return this
}

/**
* The ffi method serves as entry point fo genreally executing Python functions
* from .py-files. Important to note is, that is branching in two modes, depending
* how many arguments get passed. If there are arguments it makes a singular call
* to the script, you open and close a whole Python memory contexts for it.
*
* Second, when called in a chain with the stream API (see below). The context get's
* created and only closed on stream end.
*
* Use it accourdingly:
*
*	@example
* const ncpy = require('node-cpython')
*
* ncpy.ffi('multiplication.py', 'multiply', [ 20, 5], function (err, res) {
*   console.log('ncpy -> easy call to multiply, here');
*   console.log('ncpy -> ' + res + '\n');
* })
*	var Readable = require('stream').Readable;
* var SomeStream = new Readable({ "objectMode": true })
*
* SomeStream.push([1,2])
* SomeStream.push([20,3])
* SomeStream.push([3,40])
* SomeStream.push([4,50])
* SomeStream.push([55,66])
* SomeStream.push(null)

* ncpy.ffi
*   // load the python script and intitialize the python interpreter
*   .require('multiplication.py', { path: './examples' })
*   // this expects a stream (in { objectMode: true })
*   .init(SomeStream)
*   // Tell `ncpy` what function to excute.
*   .run('multiply')
*   // add your own transform or any other stream here
*   .pipe()
*   .on('end', function() {
*     console.log('ncpy -> Ending python context here.');
*   })
*
* @param  {String} file         .py file with function definition
* @param  {String} functionname name of function definition
* @return {Callback}              Tailcall with err and res
*/
Ncpy.prototype.ffi = function (file, functionname, argList, cb) {
  let args = Array.prototype.slice.call(arguments)
  let err = {}
  let res

  if (args.length === 0) {
    return // to stream
  }

  cb = (typeof cb === 'function') ? cb : function() {}

  return cb(err, res)
}

Ncpy.prototype.ffi.require = function (file, options) {


  Object.defineProperty(this, 'fileParam', {
    get: function() {
        return [file || '', options.path || '']
    }
  })

  // go down to ffi in JS land
  FFI._require(this.fileParam[0])
  return this
}

Ncpy.prototype.ffi._setPath = function () {
  // go directly down to cc-land
  return NodeCPython2X.setPath(this.fileParam[1])
}

Ncpy.prototype.ffi.init = function (stream) {
  let self = this

  NodeCPython2X.initialize()

  this._setPath()

  this.stream = stream
  // the callback for init function shoots at 'end' event
  // However this might currently be unsafe since we don't
  // listen for SIGINT (and sorts)
  // REVIEW: for memory leaks
  FFI._init(stream, function () {
    NodeCPython2X.finalize()
  })
  return this
}

Ncpy.prototype.ffi.run = function (fnName) {
  FFI._run(fnName)
  return this
}

Ncpy.prototype.ffi.pipe = function () {
  return this
}

Ncpy.prototype.ffi.on = function (ffiEventName, ffiCb) {
  FFI._registerEvent(ffiEventName, ffiCb)
  return this
}

/**
*
*/
Ncpy.prototype.interactiveOne = function () {

}

/**
*
*/
Ncpy.prototype.interactiveLoop = function () {

}

/**
*
*/
Ncpy.prototype.simpleParseString = function () {

}

/**
*
*/
Ncpy.prototype.simpleParseFile = function () {

}

/**
*
*/
Ncpy.prototype.string = function () {

}

/**
*
*/
Ncpy.prototype.file = function () {

}

/**
*
*/
Ncpy.prototype.compileString = function () {

}

/**
*
*/
Ncpy.prototype.evalCode = function () {

}

/**
*
*/
Ncpy.prototype.evalFrame = function () {

}

/**
* initialize python context, reserve memory.
*
*/
Ncpy.prototype.initialize = function () {
  NodeCPython2X.initialize()
}

/**
* Finalize python context, clear memory.
* @param {callback} callback for completion of py context
*/
Ncpy.prototype.finalize = function () {
  NodeCPython2X.finalize()
}

/**
* set low level python program name (optional)
* @param {string} Program name.
*/
Ncpy.prototype.setProgramName = function (str) {
  // nanCPython.setprogramname(str)
}

/**
* set low level python argv
* @param {string|string[]} string or an array of strings as argv argc is auto computed by the arrays length
*/
Ncpy.prototype.setArgv = function (arr) {
  // nanCPython.setargv(arr)
}

/**
* Create a context in memory to run the python script and injects a python function to run in.
* @param {callback} python function to run in the memory
*/
Ncpy.prototype.pyCreateContext = function (program) {
  this.setProgramName()
  this.initialize()
  this.setArgv

  // execute program here
  program()

  this.finalize(function (err) {
    this.emit('err', err)
  })
}

/**
* Create a context in memory to run the python script in
* @private
* @param {string[]} globbing pattern
* @param {callback} [cb] - Optional callback
*/
Ncpy.prototype._getListOfFiles = function (pattern, options, cb) {
  // let args = Array.prototype.slice.call(arguments)
  glob(pattern, options, function (err, files) {
    return cb(err, files)
  })
}

module.exports = new Ncpy()
