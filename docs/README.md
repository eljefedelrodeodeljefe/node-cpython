# node-cpython

Native bindings to run python in its native interpreter.

This Library is in alpha status. **Do not use for fun or profit**

[![Build Status](https://travis-ci.org/eljefedelrodeodeljefe/node-cpython.svg?branch=master)](https://travis-ci.org/eljefedelrodeodeljefe/node-cpython) [![Build status](https://ci.appveyor.com/api/projects/status/59q34ua3i457k27x?svg=true)](https://ci.appveyor.com/project/eljefederodeodeljefe/node-cpython)


[![NPM](https://nodei.co/npm/cpython.png?downloads=true&downloadRank=true&stars=true)](https://nodei.co/npm/cpython/)[![NPM](https://nodei.co/npm-dl/cpython.png?months=6&height=2)](https://nodei.co/npm/cpython/)

## TL;DR

Sometimes you want to use Python scripts or even whole libraries, but you don't want to rely on `child_process.exec()` or `child_process.spawn()`. This module initializes the standard Python interpreter and passes Py code to it.

![](http://res.cloudinary.com/jefe-io/image/upload/c_scale,w_500/v1431433374/Node-CPython-Logo_cw7rko.png)

## Implementation Status<a name="status"></a>
| Method | implemented |
| --- | --- |
| .anyFile() | -  |
| .simpleString(str, [flags], [cb]) | **yes** \* |
| .simpleFile() | - |
| .repl() | **yes** \* |
| .simpleParseString() | - |
| .simpleParseFile() | - |
| .string() | - |
| .file() | - |
| .compileString() | - |
| .evalCode() | - |
| .evalFrame() | - |

\* Will be extended, but not directly in JS user space. It will be optional to pass more than the required params so the functionality of the CPython-API will be implicitly usable. This includes closeits and compiler flags.

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

| Platform | Node | IO.js |
| --- | --- | --- |
| Mac OS X | - | **yes** |
| Linux | - | **yes** |
| Windows | - | - |

## Roadmap

Please see [list of the implemented methods](#status) for now.


## API
