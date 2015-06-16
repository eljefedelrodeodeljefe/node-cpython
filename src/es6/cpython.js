'use strict';
import {SomeClass} from "./math";
import {PyCalls} from "./PyCalls";
import {EventEmitter} from "events";
import {glob} from "glob";

const nanCPython = require('bindings')('../build/Release/node-cpython');

/**
 * Implements the CPython Python interpreter
 * @class CPython
 */
export class CPython extends EventEmitter {
  constructor(opts) {
    super()

    //Emscripten.init.call(this)
    this.opts = opts
    //super()
  }

  /**
  * Executes any number of Python source code files.
  * This is JS userland API and automates and abstracts many choices of the
  * below C-API. If you want to have more control, please use the below methods.
  *
  * @example
  * 'use strict';
  * var cpython = require('cpython');
  *
  * cpython.on('error', function(err) {console.log(err);})
  *
  * cpython.run('[example/**\/*.py', function(result) { console.log(result) })
  *
  * @param {string|string[]} glob - a glob of valid .py files
  * @param {callback} [cb] - Optional callback
  */
  // TODO: actually implement callbacks
  run(glob, callback) {
    var args = Array.prototype.slice.call(arguments);

    // //TODO: check if condition is valid at all (after first review: seems to be the case)
    // if (args.length != 2 || typeof filepath != 'string' || filepath instanceof String) {
    //
    //   var err = new Error("Method 'simpleString' expects one argument, which must be a string")
    //   err.name = "InputError"
    //
    //   this.emit('error', err)
    //   return
    // }

    /**
    * call simpleFile from below and pass args as string
    */
    nanCPython.runRun("example/multiply_2.py", 3, ["name1","name2"])

    // TODO: Check if chainability is actually usuful
    return this
  }

  /**
  *
  */
  anyFile() {

  }

  /**
  * Executes the Python source code from command.
  * See also [Python docs]{@link https://docs.python.org/2/c-api/veryhigh.html#c.PyRun_SimpleStringFlags} for Reference
  *
  * @example
  * 'use strict';
  * var cpython = require('cpython');
  *
  * cpython.on('error', function(err) {console.log(err);})
  *
  * cpython.simpleString("from time import time,ctime\nprint 'Today is',ctime(time())\n")
  *
  * @param {string} str - String of python denoted code
  * @param {string|string[]} [flags=null] - Compiler flag or array of flags for CPython
  * @param {callback} [cb] - Optional callback
  */
  // TODO: actually implement compiler flags and callbacks
  simpleString(str, flags, cb) {
    var args = Array.prototype.slice.call(arguments);

    // TODO: check if condition is valid at all (after first review: seems to be the case)
    if (args.length != 1 || typeof str != 'string' || str instanceof String) {

      var err = new Error("Method 'simpleString' expects one argument, which must be a string")
      err.name = "InputError"

      this.emit('error', err)
      return
    }

    /**
    * call simpleString from below and pass args as string
    */
    nanCPython.simpleString(str)

    // TODO: Check if chainability is actually usuful
    return this
  }



  /**
  * Executes the Python source code from file.
  * Similar to simpleString(), but the Python source code is read from a file
  * instead of an in-memory string. filename should be the name of the file.
  * See also [Python docs]{@link https://docs.python.org/2/c-api/veryhigh.html#c.PyRun_SimpleFileExFlags} for Reference
  *
  * @example
  * 'use strict';
  * var cpython = require('cpython');
  *
  * cpython.on('error', function(err) {console.log(err);})
  *
  * cpython.simpleFile("example/multiply.py", "multiply.py")
  * // passing the filename seems to be a necessity of the C-API
  * // TODO: this will only last very shortly and be made optional
  *
  * @param {string} filepath - String of filepath
  * @param {string} filename - String of filename
  * @param {string|string[]} [flags=null] - Compiler flag or array of flags for CPython
  * @param {callback} [cb] - Optional callback
  */
  // TODO: actually implement compiler flags and callbacks
  simpleFile(filepath, filename, flags, callback) {
    var args = Array.prototype.slice.call(arguments);

    //TODO: check if condition is valid at all (after first review: seems to be the case)
    if (args.length != 2 || typeof filepath != 'string' || filepath instanceof String) {

      var err = new Error("Method 'simpleString' expects one argument, which must be a string")
      err.name = "InputError"

      this.emit('error', err)
      return
    }

    /**
    * call simpleFile from below and pass args as string
    */
    nanCPython.simpleFile(filepath, filename)

    // TODO: Check if chainability is actually usuful
    return this
  }

  /**
   * [callForeignFunction description]
   * @param  {string} file        [description]
   * @param  {string} functioname [description]
   * @return {function}             [description]
   */
  callForeignFunction(file, functioname) {
    nanCPython.simpleFile(file, functionname)

    // TODO: Check if chainability is actually usuful
    return this
  }

  /**
   * [ffi description]
   * @param  {string} file         [description]
   * @param  {string} functionname [description]
   * @return {function}              [description]
   */
  ffi(file, functionname) {
    this.callForeignFunction(file, filename)
  }

  /**
  *
  */
  interactiveOne() {

  }

  /**
  *
  */
  interactiveLoop() {

  }

  /**
  *
  */
  simpleParseString() {

  }

  /**
  *
  */
  simpleParseFile() {

  }

  /**
  *
  */
  string() {

  }

  /**
  *
  */
  file() {

  }

  /**
  *
  */
  compileString() {

  }

  /**
  *
  */
  evalCode() {

  }

  /**
  *
  */
  evalFrame () {

  }

  /**
  * initialize python context, reserve memory.
  *
  */
  initialize () {
    nanCPython.initialize()
  }

  /**
  * Finalize python context, clear memory.
  * @param {callback} callback for completion of py context
  */
  finalize (cb) {

    nanCPython.finalize()

    cb()

  }

  /**
  * set low level python program name (optional)
  * @param {string} Program name.
  */
  setProgramName (str) {
    nanCPython.setprogramname(str)
  }

  /**
  * set low level python argv
  * @param {string|string[]} string or an array of strings as argv; argc is auto computed by the arrays length
  */
  setArgv ( arr ) {
    nanCPython.setargv(arr)
  }

  /**
  * Create a context in memory to run the python script and injects a python function to run in.
  * @param {callback} python function to run in the memory
  */
  pyCreateContext (program) {
    this.setProgramName()
    this.initialize()
    this.setArgv

    // execute program here
    program()

    this.finalize( (err) => {
      this.emit('err', err)
    })
  }

  /**
  * Create a context in memory to run the python script in
  * @private
  * @param {string[]} globbing pattern
  * @param {callback} [cb] - Optional callback
  */
  _getListOfFiles(pattern, options, cb) {
    //var args = Array.prototype.slice.call(arguments);
    glob("**/*.js", options, function (err, files) {
      // files is an array of filenames.
      // If the `nonull` option is set, and nothing
      // was found, then files is ["**/*.js"]
      // er is an error object or null.
      return cb(err,files)
    })
  }


}

let inst = new CPython()
module.exports = inst
