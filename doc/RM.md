# Node-CPython

Native bindings to run python in its native interpreter.

This Library is in alpha status.

## TL;DR

Sometimes you want to use Python scripts or even whole libraries, but you don't want to rely on `child_process.exec()` or `chold_process.spawn()`. This module initializes the standard Python interpreter and passes Py code to it.

## Implementation Status
| Method | implemented |
| --- | --- |
| .anyFile() | -  |
| .simpleString(str, [flags], [cb]) | **yes** |
| .simpleFile() | - |
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

## API
