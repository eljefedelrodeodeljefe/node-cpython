"use strict";

var _classCallCheck = function (instance, Constructor) { if (!(instance instanceof Constructor)) { throw new TypeError("Cannot call a class as a function"); } };

var _createClass = (function () { function defineProperties(target, props) { for (var i = 0; i < props.length; i++) { var descriptor = props[i]; descriptor.enumerable = descriptor.enumerable || false; descriptor.configurable = true; if ("value" in descriptor) descriptor.writable = true; Object.defineProperty(target, descriptor.key, descriptor); } } return function (Constructor, protoProps, staticProps) { if (protoProps) defineProperties(Constructor.prototype, protoProps); if (staticProps) defineProperties(Constructor, staticProps); return Constructor; }; })();

var _get = function get(object, property, receiver) { var desc = Object.getOwnPropertyDescriptor(object, property); if (desc === undefined) { var parent = Object.getPrototypeOf(object); if (parent === null) { return undefined; } else { return get(parent, property, receiver); } } else if ("value" in desc) { return desc.value; } else { var getter = desc.get; if (getter === undefined) { return undefined; } return getter.call(receiver); } };

var _inherits = function (subClass, superClass) { if (typeof superClass !== "function" && superClass !== null) { throw new TypeError("Super expression must either be null or a function, not " + typeof superClass); } subClass.prototype = Object.create(superClass && superClass.prototype, { constructor: { value: subClass, enumerable: false, writable: true, configurable: true } }); if (superClass) subClass.__proto__ = superClass; };

Object.defineProperty(exports, "__esModule", {
  value: true
});

var _SomeClass = require("./math");

var _PyCalls = require("./PyCalls");

var _EventEmitter2 = require("events");

"use strict";

var nanCPython = require("bindings")("../build/Release/cpython");

/**
 * Implements the CPython Python interpreter
 * @class CPython
 */

var CPython = (function (_EventEmitter) {
  function CPython(opts) {
    _classCallCheck(this, CPython);

    _get(Object.getPrototypeOf(CPython.prototype), "constructor", this).call(this);

    //Emscripten.init.call(this)
    this.opts = opts
    //super()
    ;
  }

  _inherits(CPython, _EventEmitter);

  _createClass(CPython, [{
    key: "anyFile",

    /**
    *
    */
    value: function anyFile() {}
  }, {
    key: "simpleString",

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
    value: function simpleString(str, flags, cb) {
      var args = Array.prototype.slice.call(arguments);

      // TODO: check if condition is valid at all (after first review: seems to be the case)
      if (args.length != 1 || typeof str != "string" || str instanceof String) {

        var err = new Error("Method 'simpleString' expects one argument, which must be a string");
        err.name = "InputError";

        this.emit("error", err);
        return;
      }

      /**
      * call simpleString from below and pass args as string
      */
      nanCPython.simpleString(str);

      // TODO: Check if chainability is actually usuful
      return this;
    }
  }, {
    key: "simpleFile",

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
    * cpython.simpleFile("./example/multiply.py")
    *
    * @param {string} filename - String of filename
    * @param {string|string[]} [flags=null] - Compiler flag or array of flags for CPython
    * @param {callback} [cb] - Optional callback
    */
    // TODO: actually implement compiler flags and callbacks
    value: function simpleFile(filePath, filedesciptor, callback) {
      var args = Array.prototype.slice.call(arguments);

      // TODO: check if condition is valid at all (after first review: seems to be the case)
      if (args.length != 1 || typeof str != "string" || str instanceof String) {

        var err = new Error("Method 'simpleString' expects one argument, which must be a string");
        err.name = "InputError";

        this.emit("error", err);
        return;
      }

      /**
      * call simpleFile from below and pass args as string
      */
      nanCPython.simpleFile(filePath);

      // TODO: Check if chainability is actually usuful
      return this;
    }
  }, {
    key: "interactiveOne",

    /**
    *
    */
    value: function interactiveOne() {}
  }, {
    key: "interactiveLoop",

    /**
    *
    */
    value: function interactiveLoop() {}
  }, {
    key: "simpleParseString",

    /**
    *
    */
    value: function simpleParseString() {}
  }, {
    key: "simpleParseFile",

    /**
    *
    */
    value: function simpleParseFile() {}
  }, {
    key: "string",

    /**
    *
    */
    value: function string() {}
  }, {
    key: "file",

    /**
    *
    */
    value: function file() {}
  }, {
    key: "compileString",

    /**
    *
    */
    value: function compileString() {}
  }, {
    key: "evalCode",

    /**
    *
    */
    value: function evalCode() {}
  }, {
    key: "evalFrame",

    /**
    *
    */
    value: function evalFrame() {}
  }]);

  return CPython;
})(_EventEmitter2.EventEmitter);

exports.CPython = CPython;

var inst = new CPython();
module.exports = inst;