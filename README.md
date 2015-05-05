# Node-CPython

Native bindings to run python in its native interpreter.

This Library is in alpha status. **Do not use for fun or profit**

[![Build Status](https://travis-ci.org/eljefedelrodeodeljefe/node-cpython.svg?branch=master)](https://travis-ci.org/eljefedelrodeodeljefe/node-cpython)

[![NPM](https://nodei.co/npm/cpython.png?downloads=true&downloadRank=true&stars=true)](https://nodei.co/npm/cpython/)[![NPM](https://nodei.co/npm-dl/cpython.png?months=6&height=2)](https://nodei.co/npm/cpython/)

## TL;DR

Sometimes you want to use Python scripts or even whole libraries, but you don't want to rely on `child_process.exec()` or `child_process.spawn()`. This module initializes the standard Python interpreter and passes Py code to it.

## Implementation Status
| Method | implemented |
| --- | --- |
| .anyFile() | -  |
| .simpleString(str, [flags], [cb]) | **yes** |
| .simpleFile() | *pending* |
| .interactiveOne() | - |
| .interactiveLoop() | - |
| .simpleParseString() | - |
| .simpleParseFile() | - |
| .string() | - |
| .file() | - |
| .compileString() | - |
| .evalCode() | - |
| .evalFrame() | - |

## Introduction

The following shall give background information and explain why you want to use this.

### Motivation

In order to compile C code with [Emscripten](https://github.com/kripken/emscripten) you'd have to run the Python script, which utilizes LLVM. However working with `child_process.exec()` or `chold_process.spawn()` seems odd, since it neither safe nor does it handle errors nor is it platform independent.
So in order to run scripts programmatically it seemed a good idea to use the the perfect legit `Python.h` C-header in the standard implementation of Python.

### Overview

### Technical Overview

**Rquirements:**
* Python 2.7 (for now)
* Any Python for Gyp
* Node 0.12+ / IO.js

## Platform

This module is currently tested on:

| Platform | Node | IO.js |
| --- | --- | --- |
| Mac OS X | - | **yes** |
| Linux | - | - |
| Windows | - | - |

## API

<a name="CPython"></a>
## CPython
**Kind**: global class  

* [CPython](#CPython)
  * [new CPython()](#new_CPython_new)
  * [.anyFile()](#CPython#anyFile)
  * [.simpleString(str, [flags], [cb])](#CPython#simpleString)
  * [.simpleFile()](#CPython#simpleFile)
  * [.interactiveOne()](#CPython#interactiveOne)
  * [.interactiveLoop()](#CPython#interactiveLoop)
  * [.simpleParseString()](#CPython#simpleParseString)
  * [.simpleParseFile()](#CPython#simpleParseFile)
  * [.string()](#CPython#string)
  * [.file()](#CPython#file)
  * [.compileString()](#CPython#compileString)
  * [.evalCode()](#CPython#evalCode)
  * [.evalFrame()](#CPython#evalFrame)

<a name="new_CPython_new"></a>
### new CPython()
Implements the CPython Python interpreter

<a name="CPython#anyFile"></a>
### cPython.anyFile()
**Kind**: instance method of <code>[CPython](#CPython)</code>  
<a name="CPython#simpleString"></a>
### cPython.simpleString(str, [flags], [cb])
Executes the Python source code from command.
See also [Python docs](https://docs.python.org/2/c-api/veryhigh.html#c.PyRun_SimpleStringFlags) for Reference

**Kind**: instance method of <code>[CPython](#CPython)</code>  

| Param | Type | Default | Description |
| --- | --- | --- | --- |
| str | <code>string</code> |  | String of python denoted code |
| [flags] | <code>string</code> &#124; <code>Array.&lt;string&gt;</code> | <code>null</code> | Compiler flag or array of flags for CPython |
| [cb] | <code>callback</code> |  | Optional callback |

**Example**  
```js
'use strict';
var cpython = require('cpython');

cpython.on('error', function(err) {console.log(err);})

cpython.simpleString("from time import time,ctime\nprint 'Today is',ctime(time())\n", "hello")
```
<a name="CPython#simpleFile"></a>
### cPython.simpleFile()
**Kind**: instance method of <code>[CPython](#CPython)</code>  
<a name="CPython#interactiveOne"></a>
### cPython.interactiveOne()
**Kind**: instance method of <code>[CPython](#CPython)</code>  
<a name="CPython#interactiveLoop"></a>
### cPython.interactiveLoop()
**Kind**: instance method of <code>[CPython](#CPython)</code>  
<a name="CPython#simpleParseString"></a>
### cPython.simpleParseString()
**Kind**: instance method of <code>[CPython](#CPython)</code>  
<a name="CPython#simpleParseFile"></a>
### cPython.simpleParseFile()
**Kind**: instance method of <code>[CPython](#CPython)</code>  
<a name="CPython#string"></a>
### cPython.string()
**Kind**: instance method of <code>[CPython](#CPython)</code>  
<a name="CPython#file"></a>
### cPython.file()
**Kind**: instance method of <code>[CPython](#CPython)</code>  
<a name="CPython#compileString"></a>
### cPython.compileString()
**Kind**: instance method of <code>[CPython](#CPython)</code>  
<a name="CPython#evalCode"></a>
### cPython.evalCode()
**Kind**: instance method of <code>[CPython](#CPython)</code>  
<a name="CPython#evalFrame"></a>
### cPython.evalFrame()
**Kind**: instance method of <code>[CPython](#CPython)</code>  

## License

MIT
