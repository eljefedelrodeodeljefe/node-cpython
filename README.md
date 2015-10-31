# node-cpython

Native bindings to run python in its native interpreter.

This Library is in alpha status. **Do not use for fun or profit**

[![Build Status](https://travis-ci.org/eljefedelrodeodeljefe/node-cpython.svg?branch=master)](https://travis-ci.org/eljefedelrodeodeljefe/node-cpython) [![Build status](https://ci.appveyor.com/api/projects/status/59q34ua3i457k27x?svg=true)](https://ci.appveyor.com/project/eljefederodeodeljefe/node-cpython) [![js-standard-style](https://img.shields.io/badge/code%20style-standard-brightgreen.svg?style=flat)](http://standardjs.com/) [![Join the chat at https://gitter.im/eljefedelrodeodeljefe/node-cpython](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/eljefedelrodeodeljefe/node-cpython?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

[![NPM](https://nodei.co/npm-dl/cpython.png?months=6&height=2)](https://nodei.co/npm/cpython/)

## TL;DR

Sometimes you want to use Python scripts or even whole libraries, but you don't want to rely on `child_process.exec()` or `child_process.spawn()`. This module initializes the standard Python interpreter and passes Py code to it.

![](http://res.cloudinary.com/jefe-io/image/upload/v1446302782/ncpy_showcase_2_uvlp6b.gif)

## Implementation Status<a name="status"></a>
| Method | implemented |
| --- | --- |
| .anyFile() | - |
| .ffi(py_file, fn_name, args, [options], [cb]) | **yes** |
| .simpleString(str, [flags], [cb]) | **yes** |
| .simpleFile() | - |
| .repl() | **yes** |
| .simpleParseString() | - |
| .simpleParseFile() | - |
| .string() | - |
| .file() | - |
| .compileString() | - |
| .evalCode() | - |
| .evalFrame() | - |
| - | - |
| **Stream API** | - |
| ffi.require(py_file, [options]) | **yes** |
| ffi.init(stream) | **yes** |
| ffi.run(fn_name) | **yes** |
| ffi.pipe(stream) | **yes** |
| ffi.on(event) | **yes** |

## Introduction

The following shall give background information and explain why you want to use this.

### Motivation

In order to compile C code with [Emscripten](https://github.com/kripken/emscripten) you'd have to run the Python script, which utilizes LLVM. However working with `child_process.exec()` or `chold_process.spawn()` seems odd, since it neither safe nor does it handle errors nor is it platform independent.
So in order to run scripts programmatically it seemed a good idea to use the the perfect legit `Python.h` C-header in the standard implementation of Python.

### Overview

### Technical Overview

**Rquirements:**
* Node 4.0.0+

## Platform

This module is currently tested on:

| Platform | 0.12 | 3.0 | 4.0 | 5.0 |
| --- | --- | --- | --- | ---|
| Mac OS X | - | - | **yes** | **yes**|
| Linux | - | - | **yes** | **yes**  |
| Windows | - | - | - | - |

## Roadmap

Please see [list of the implemented methods](#status) for now.


## API
<a name="Ncpy"></a>
## Ncpy
**Kind**: global class  

* [Ncpy](#Ncpy)
  * [new Ncpy()](#new_Ncpy_new)
  * [.init(options)](#Ncpy+init) ⇒ <code>Object</code>
  * [.run(glob, [cb])](#Ncpy+run)
  * [.anyFile()](#Ncpy+anyFile)
  * [.runString()](#Ncpy+runString)
  * [.repl()](#Ncpy+repl)
  * [.simpleString(str, [flags], [cb])](#Ncpy+simpleString)
  * [.simpleFile(filepath, filename, [flags], [cb])](#Ncpy+simpleFile)
  * [.callForeignFunction(file, functioname)](#Ncpy+callForeignFunction) ⇒ <code>function</code>
  * [.ffi(file, functionname)](#Ncpy+ffi) ⇒ <code>Callback</code>
  * [.interactiveOne()](#Ncpy+interactiveOne)
  * [.interactiveLoop()](#Ncpy+interactiveLoop)
  * [.simpleParseString()](#Ncpy+simpleParseString)
  * [.simpleParseFile()](#Ncpy+simpleParseFile)
  * [.string()](#Ncpy+string)
  * [.file()](#Ncpy+file)
  * [.compileString()](#Ncpy+compileString)
  * [.evalCode()](#Ncpy+evalCode)
  * [.evalFrame()](#Ncpy+evalFrame)
  * [.initialize()](#Ncpy+initialize)
  * [.finalize(callback)](#Ncpy+finalize)
  * [.setProgramName(Program)](#Ncpy+setProgramName)
  * [.setArgv(string)](#Ncpy+setArgv)
  * [.pyCreateContext(python)](#Ncpy+pyCreateContext)

<a name="new_Ncpy_new"></a>
### new Ncpy()
Implements the Ncpy Python interpreter

<a name="Ncpy+init"></a>
### ncpy.init(options) ⇒ <code>Object</code>
intitialze this module from init function rather than over constructor

**Kind**: instance method of <code>[Ncpy](#Ncpy)</code>  
**Returns**: <code>Object</code> - returns itself is chainable  

| Param | Type | Description |
| --- | --- | --- |
| options | <code>Object</code> | object where keys represent toggles of individual features or point to files |

**Example**  
```js
const ncpy = require('node-cpython')

let options = {
	\/\* Options go in here \*\/
}

ncpy.init(options)
\/\/ available options [here](https://github.com/eljefedelrodeodeljefe/node-cpython#options)
```
<a name="Ncpy+run"></a>
### ncpy.run(glob, [cb])
Executes any number of Python source code files.
This is JS userland API and automates and abstracts many choices of the
below C-API. If you want to have more control, please use the below methods.

**Kind**: instance method of <code>[Ncpy](#Ncpy)</code>  

| Param | Type | Description |
| --- | --- | --- |
| glob | <code>string</code> &#124; <code>Array.&lt;string&gt;</code> | a glob of valid .py files |
| [cb] | <code>callback</code> | Optional callback |

**Example**  
```js
'use strict'
const ncpy = require('node-cpython')

cpython.on('error', function(err) {console.log(err)})

cpython.run('[example/**\/*.py', function(result) { console.log(result) })
```
<a name="Ncpy+anyFile"></a>
### ncpy.anyFile()
**Kind**: instance method of <code>[Ncpy](#Ncpy)</code>  
<a name="Ncpy+runString"></a>
### ncpy.runString()
**Kind**: instance method of <code>[Ncpy](#Ncpy)</code>  
<a name="Ncpy+repl"></a>
### ncpy.repl()
**Kind**: instance method of <code>[Ncpy](#Ncpy)</code>  
<a name="Ncpy+simpleString"></a>
### ncpy.simpleString(str, [flags], [cb])
Executes the Python source code from command.
See also [Python docs](https://docs.python.org/2/c-api/veryhigh.html#c.PyRun_SimpleStringFlags) for Reference

**Kind**: instance method of <code>[Ncpy](#Ncpy)</code>  

| Param | Type | Default | Description |
| --- | --- | --- | --- |
| str | <code>string</code> |  | String of python denoted code |
| [flags] | <code>string</code> &#124; <code>Array.&lt;string&gt;</code> | <code>null</code> | Compiler flag or array of flags for CPython |
| [cb] | <code>callback</code> |  | Optional callback |

**Example**  
```js
'use strict'
const ncpy = require('node-cpython')

cpython.on('error', function(err) {console.log(err)})

cpython.simpleString('from time import time,ctime\nprint 'Today is',ctime(time())\n')
```
<a name="Ncpy+simpleFile"></a>
### ncpy.simpleFile(filepath, filename, [flags], [cb])
Executes the Python source code from file.
Similar to simpleString(), but the Python source code is read from a file
instead of an in-memory string. filename should be the name of the file.
See also [Python docs](https://docs.python.org/2/c-api/veryhigh.html#c.PyRun_SimpleFileExFlags) for Reference

**Kind**: instance method of <code>[Ncpy](#Ncpy)</code>  

| Param | Type | Default | Description |
| --- | --- | --- | --- |
| filepath | <code>string</code> |  | String of filepath |
| filename | <code>string</code> |  | String of filename |
| [flags] | <code>string</code> &#124; <code>Array.&lt;string&gt;</code> | <code>null</code> | Compiler flag or array of flags for CPython |
| [cb] | <code>callback</code> |  | Optional callback |

**Example**  
```js
'use strict'
const ncpy = require('node-cpython')

cpython.on('error', function(err) {console.log(err)})

cpython.simpleFile('example/multiply.py', 'multiply.py')
// passing the filename seems to be a necessity of the C-API
// TODO: this will only last very shortly and be made optional
```
<a name="Ncpy+callForeignFunction"></a>
### ncpy.callForeignFunction(file, functioname) ⇒ <code>function</code>
[callForeignFunction description]

**Kind**: instance method of <code>[Ncpy](#Ncpy)</code>  
**Returns**: <code>function</code> - [description]  

| Param | Type | Description |
| --- | --- | --- |
| file | <code>string</code> | [description] |
| functioname | <code>string</code> | [description] |

<a name="Ncpy+ffi"></a>
### ncpy.ffi(file, functionname) ⇒ <code>Callback</code>
The ffi method serves as entry point fo genreally executing Python functions
from .py-files. Important to note is, that is branching in two modes, depending
how many arguments get passed. If there are arguments it makes a singular call
to the script, you open and close a whole Python memory contexts for it.

Second, when called in a chain with the stream API (see below). The context get's
created and only closed on stream end.

Use it accourdingly:

**Kind**: instance method of <code>[Ncpy](#Ncpy)</code>  
**Returns**: <code>Callback</code> - Tailcall with err and res  

| Param | Type | Description |
| --- | --- | --- |
| file | <code>String</code> | .py file with function definition |
| functionname | <code>String</code> | name of function definition |

**Example**  
```js
const ncpy = require('node-cpython')

ncpy.ffi('multiplication.py', 'multiply', [ 20, 5], function (err, res) {
  console.log('ncpy -> easy call to multiply, here');
  console.log('ncpy -> ' + res + '\n');
})
	var Readable = require('stream').Readable;
var SomeStream = new Readable({ "objectMode": true })

SomeStream.push([1,2])
SomeStream.push([20,3])
SomeStream.push([3,40])
SomeStream.push([4,50])
SomeStream.push([55,66])
SomeStream.push(null)
ncpy.ffi
  // load the python script and intitialize the python interpreter
  .require('multiplication.py', { path: './examples' })
  // this expects a stream (in { objectMode: true })
  .init(SomeStream)
  // Tell `ncpy` what function to excute.
  .run('multiply')
  // add your own transform or any other stream here
  .pipe()
  .on('end', function() {
    console.log('ncpy -> Ending python context here.');
  })
```
<a name="Ncpy+interactiveOne"></a>
### ncpy.interactiveOne()
**Kind**: instance method of <code>[Ncpy](#Ncpy)</code>  
<a name="Ncpy+interactiveLoop"></a>
### ncpy.interactiveLoop()
**Kind**: instance method of <code>[Ncpy](#Ncpy)</code>  
<a name="Ncpy+simpleParseString"></a>
### ncpy.simpleParseString()
**Kind**: instance method of <code>[Ncpy](#Ncpy)</code>  
<a name="Ncpy+simpleParseFile"></a>
### ncpy.simpleParseFile()
**Kind**: instance method of <code>[Ncpy](#Ncpy)</code>  
<a name="Ncpy+string"></a>
### ncpy.string()
**Kind**: instance method of <code>[Ncpy](#Ncpy)</code>  
<a name="Ncpy+file"></a>
### ncpy.file()
**Kind**: instance method of <code>[Ncpy](#Ncpy)</code>  
<a name="Ncpy+compileString"></a>
### ncpy.compileString()
**Kind**: instance method of <code>[Ncpy](#Ncpy)</code>  
<a name="Ncpy+evalCode"></a>
### ncpy.evalCode()
**Kind**: instance method of <code>[Ncpy](#Ncpy)</code>  
<a name="Ncpy+evalFrame"></a>
### ncpy.evalFrame()
**Kind**: instance method of <code>[Ncpy](#Ncpy)</code>  
<a name="Ncpy+initialize"></a>
### ncpy.initialize()
initialize python context, reserve memory.

**Kind**: instance method of <code>[Ncpy](#Ncpy)</code>  
<a name="Ncpy+finalize"></a>
### ncpy.finalize(callback)
Finalize python context, clear memory.

**Kind**: instance method of <code>[Ncpy](#Ncpy)</code>  

| Param | Type | Description |
| --- | --- | --- |
| callback | <code>callback</code> | for completion of py context |

<a name="Ncpy+setProgramName"></a>
### ncpy.setProgramName(Program)
set low level python program name (optional)

**Kind**: instance method of <code>[Ncpy](#Ncpy)</code>  

| Param | Type | Description |
| --- | --- | --- |
| Program | <code>string</code> | name. |

<a name="Ncpy+setArgv"></a>
### ncpy.setArgv(string)
set low level python argv

**Kind**: instance method of <code>[Ncpy](#Ncpy)</code>  

| Param | Type | Description |
| --- | --- | --- |
| string | <code>string</code> &#124; <code>Array.&lt;string&gt;</code> | or an array of strings as argv argc is auto computed by the arrays length |

<a name="Ncpy+pyCreateContext"></a>
### ncpy.pyCreateContext(python)
Create a context in memory to run the python script and injects a python function to run in.

**Kind**: instance method of <code>[Ncpy](#Ncpy)</code>  

| Param | Type | Description |
| --- | --- | --- |
| python | <code>callback</code> | function to run in the memory |

## License

MIT
