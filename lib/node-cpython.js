'use strict'
const EventEmitter = require('events')
const util = require('util')
const glob = require('glob')
const NCPY2 = require('./bindings.js').NodeCPython2X
var NCPy2 = new NCPY2()
const FFI = require('./ffi.js')
const path = require('path')

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
 * const ncpy = require('node-cpython')
 *
 * let options = {
 * 	\/\* Options go in here \*\/
 * }
 *
 * ncpy.init(options)
 * \/\/ available options [here]{@link https://github.com/eljefedelrodeodeljefe/node-cpython#options}
 *
 * @param  {Object} options object where keys represent toggles of individual features or point to files
 * @return {Object}           returns itself is chainable
 */
Ncpy.prototype.init = function (options) {
  return new Ncpy(options)
}

/**
 * Starts a Python contexts, runs a newline delimited string of python from Node's
 * `stdin`, listens for `SIGINT` and finalizes the Python context.
 */
Ncpy.prototype.repl = function () {
  // http://stackoverflow.com/a/9541411/3580261 for below
  NCPy2.initialize()
  NCPy2.addModule()
  NCPy2.getDict()

  process.stdin.setEncoding('utf8')

  process.stdin.on('readable', function () {
    let chunk = process.stdin.read()
    process.stdout.write('> ')
    if (chunk !== null) {
      // TODO: implement pass-down to interactiveLoop
      NCPy2.runString(chunk)
    }
  })

  process.stdin.on('end', function () {
    process.stdout.write('-------\nPyREPL connection end.\n')
    NCPy2.finalize()
  })

  process.on('SIGINT', function () {
    process.stdout.write('\n-------\nPyREPL closed.\n')

    NCPy2.finalize()
    process.exit(0)
  })
}

/**
* Executes the Python source code from file.
* Similar to simpleString(), but the Python source code is read from a file
* instead of an in-memory string. filename should be the name of the file.
* See also [Python docs]{@link https://docs.python.org/2/c-api/veryhigh.html#c.PyRun_SimpleFileExFlags} for Reference
*
*/

/**
* Executes any number of Python source code files.
* This is JS userland API and automates and abstracts many choices of the
* below C-API. If you want to have more control, please use the below methods.
*
* @example
* 'use strict'
* const ncpy = require('node-cpython')
*
* ncpy.on('error', function(err) {console.log(err)})
*
* ncpy.run('[example/**\/*.py',[2, 10, 'someOtherArg'], function(err) {
* 	console.log(err)
* })
*
* @param {String|String[]} glob a glob of valid .py files
* @param {Array} Argv global arguments array
* @param {Callback} [cb] Optional callback
*/
Ncpy.prototype.run = function (glob, argv, cb) {
  // let args = Array.prototype.slice.call(arguments)
  // let err = {}

  // //TODO: check if condition is valid at all (after first review: seems to be the case)
  // if (args.length !== 2 || typeof filepath !== 'string' || filepath instanceof String) {
  //
  //   let err = new Error('Method 'simpleString' expects one argument, which must be a string')
  //   err.name = 'InputError'
  //
  //   this.emit('error', err)
  //   return
  // }
  NCPy2.initialize()
  // let one = function() {
  //   console.log('one');
  // }
  //
  // let two = function() {
  //   let array = []
  //   for (var i = 0; i < 20000000; i++) {
  //     array[i] = i
  //   }
  //   console.log('two');
  // }
  //
  // let arr = [one, two]
  // let taskLen = arr.length
  //
  // arr.forEach(function (el) {
  //   setImmediate(el)
  // })
  //
  // setImmediate(function () {
  //   return cb(err)
  // })

  NCPy2.finalize()
  /**
  * call simpleFile from below and pass args as string
  */
  // nanCPython.runRun(glob, args[1].length, args[1])
}

/**
*
* @param {String|String[]} glob a glob of valid .py files
* @param {Array} Argv global arguments array
* @param {Callback} [cb] Optional callback
*/
Ncpy.prototype.runSync = function (glob, argv, cb) {
  // let args = Array.prototype.slice.call(arguments)
}

/**
 * Exuute a line of Python script
 * @param  {String} string a valid string of Python script
 */
Ncpy.prototype.runString = function (string) {
  let args = Array.prototype.slice.call(arguments)
  // http://stackoverflow.com/a/9541411/3580261 for above repl implementation
  return NCPy2.runString(args[0])
}

/**
* Executes the Python source code from command.
* See also [Python docs]{@link https://docs.python.org/2/c-api/veryhigh.html#c.PyRun_SimpleStringFlags} for Reference
*
* @example
* 'use strict'
* const ncpy = require('node-cpython')
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
Ncpy.prototype.simpleString = function (str, cb) {
  let args = Array.prototype.slice.call(arguments)
  let err = {}

  if (args.length !== 2 || typeof str !== 'string' || str instanceof String) {
    err = new Error('Method `simpleString` expects two arguments, which must be a string and a callback')
    err.name = 'InputError'
    this.emit('error', err)
    return
  }

  NCPy2.initialize()
  NCPy2.simpleString(args[0])
  NCPy2.finalize()

  cb = (typeof cb === 'function') ? cb : function () {}

  return cb(err)
}

/**
* The ffi method serves as entry point for generally executing Python functions
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
  let self = this
  let args = Array.prototype.slice.call(arguments)

  if (args.length === 0) {
    return // to stream
  }

  // this.initialize()
  NCPy2.setPath(path.join(process.cwd(), path.dirname(file)))

  cb = (typeof cb === 'function') ? cb : function () {}

  FFI._require(file)
  FFI.simpleRun(file, functionname, argList, function (err, res) {
    // self.finalize()
    return cb(err, res)
  })
}

Ncpy.prototype.ffi.require = function (file, options) {
  Object.defineProperty(this, 'fileParam', {
    get: function () {
      return [file || '', options.path || '']
    }
  })

  // go down to ffi in JS land
  FFI._require(this.fileParam[0])
  return this
}

Ncpy.prototype.ffi._setPath = function () {
  // go directly down to cc-land
  return NCPy2.setPath(this.fileParam[1])
}

Ncpy.prototype.ffi.init = function (stream) {
  NCPy2.initialize()

  this._setPath()

  this.stream = stream
  // the callback for init function shoots at 'end' event
  // However this might currently be unsafe since we don't
  // listen for SIGINT (and sorts)
  // REVIEW: for memory leaks
  FFI._init(stream, function () {
    NCPy2.finalize()
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
Ncpy.prototype.eval = function () {

}

/**
* initialize python context, reserve memory.
*
*/
Ncpy.prototype.initialize = function () {
  return NCPy2.initialize()
}

/**
* Finalize python context, clear memory.
* @param {callback} callback for completion of py context
*/
Ncpy.prototype.finalize = function (ref) {
  NCPy2.finalize(ref)
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
