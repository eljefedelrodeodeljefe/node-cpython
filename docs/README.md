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
| .anyFile() | -  |
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
|  |  |
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
| Mac OS X | - | - | **yes**   **yes**| |
| Linux | - | - | **yes** | **yes**  |
| Windows | - | - | - | - |

## Roadmap

Please see [list of the implemented methods](#status) for now.


## API
