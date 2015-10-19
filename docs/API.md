<a name="CPython"></a>
## CPython
**Kind**: global class  

* [CPython](#CPython)
  * [new CPython()](#new_CPython_new)
  * [.init(arguments)](#CPython+init) ⇒ <code>Object</code>
  * [.run(glob, [cb])](#CPython+run)
  * [.anyFile()](#CPython+anyFile)
  * [.simpleString(str, [flags], [cb])](#CPython+simpleString)
  * [.simpleFile(filepath, filename, [flags], [cb])](#CPython+simpleFile)
  * [.callForeignFunction(file, functioname)](#CPython+callForeignFunction) ⇒ <code>function</code>
  * [.ffi(file, functionname)](#CPython+ffi) ⇒ <code>function</code>
  * [.interactiveOne()](#CPython+interactiveOne)
  * [.interactiveLoop()](#CPython+interactiveLoop)
  * [.simpleParseString()](#CPython+simpleParseString)
  * [.simpleParseFile()](#CPython+simpleParseFile)
  * [.string()](#CPython+string)
  * [.file()](#CPython+file)
  * [.compileString()](#CPython+compileString)
  * [.evalCode()](#CPython+evalCode)
  * [.evalFrame()](#CPython+evalFrame)
  * [.initialize()](#CPython+initialize)
  * [.finalize(callback)](#CPython+finalize)
  * [.setProgramName(Program)](#CPython+setProgramName)
  * [.setArgv(string)](#CPython+setArgv)
  * [.pyCreateContext(python)](#CPython+pyCreateContext)

<a name="new_CPython_new"></a>
### new CPython()
Implements the CPython Python interpreter

<a name="CPython+init"></a>
### cPython.init(arguments) ⇒ <code>Object</code>
intitialze this module from init function rather than over constructor

**Kind**: instance method of <code>[CPython](#CPython)</code>  
**Returns**: <code>Object</code> - returns itself; is chainable  

| Param | Type | Description |
| --- | --- | --- |
| arguments | <code>Object</code> | object where keys represent toggles of individual features or point to files |

**Example**  
```js
const cpython = require('node-cpython')

let options = {
	\/\* Options go in here \*\/
}

cpython.init(options)
\/\/ available options [here](https://github.com/eljefedelrodeodeljefe/node-cpython#options)
```
<a name="CPython+run"></a>
### cPython.run(glob, [cb])
Executes any number of Python source code files.
This is JS userland API and automates and abstracts many choices of the
below C-API. If you want to have more control, please use the below methods.

**Kind**: instance method of <code>[CPython](#CPython)</code>  

| Param | Type | Description |
| --- | --- | --- |
| glob | <code>string</code> &#124; <code>Array.&lt;string&gt;</code> | a glob of valid .py files |
| [cb] | <code>callback</code> | Optional callback |

**Example**  
```js
'use strict'
let cpython = require('cpython')

cpython.on('error', function(err) {console.log(err)})

cpython.run('[example/**\/*.py', function(result) { console.log(result) })
```
<a name="CPython+anyFile"></a>
### cPython.anyFile()
**Kind**: instance method of <code>[CPython](#CPython)</code>  
<a name="CPython+simpleString"></a>
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
'use strict'
let cpython = require('cpython')

cpython.on('error', function(err) {console.log(err)})

cpython.simpleString('from time import time,ctime\nprint 'Today is',ctime(time())\n')
```
<a name="CPython+simpleFile"></a>
### cPython.simpleFile(filepath, filename, [flags], [cb])
Executes the Python source code from file.
Similar to simpleString(), but the Python source code is read from a file
instead of an in-memory string. filename should be the name of the file.
See also [Python docs](https://docs.python.org/2/c-api/veryhigh.html#c.PyRun_SimpleFileExFlags) for Reference

**Kind**: instance method of <code>[CPython](#CPython)</code>  

| Param | Type | Default | Description |
| --- | --- | --- | --- |
| filepath | <code>string</code> |  | String of filepath |
| filename | <code>string</code> |  | String of filename |
| [flags] | <code>string</code> &#124; <code>Array.&lt;string&gt;</code> | <code>null</code> | Compiler flag or array of flags for CPython |
| [cb] | <code>callback</code> |  | Optional callback |

**Example**  
```js
'use strict'
let cpython = require('cpython')

cpython.on('error', function(err) {console.log(err)})

cpython.simpleFile('example/multiply.py', 'multiply.py')
// passing the filename seems to be a necessity of the C-API
// TODO: this will only last very shortly and be made optional
```
<a name="CPython+callForeignFunction"></a>
### cPython.callForeignFunction(file, functioname) ⇒ <code>function</code>
[callForeignFunction description]

**Kind**: instance method of <code>[CPython](#CPython)</code>  
**Returns**: <code>function</code> - [description]  

| Param | Type | Description |
| --- | --- | --- |
| file | <code>string</code> | [description] |
| functioname | <code>string</code> | [description] |

<a name="CPython+ffi"></a>
### cPython.ffi(file, functionname) ⇒ <code>function</code>
[ffi description]

**Kind**: instance method of <code>[CPython](#CPython)</code>  
**Returns**: <code>function</code> - [description]  

| Param | Type | Description |
| --- | --- | --- |
| file | <code>string</code> | [description] |
| functionname | <code>string</code> | [description] |

<a name="CPython+interactiveOne"></a>
### cPython.interactiveOne()
**Kind**: instance method of <code>[CPython](#CPython)</code>  
<a name="CPython+interactiveLoop"></a>
### cPython.interactiveLoop()
**Kind**: instance method of <code>[CPython](#CPython)</code>  
<a name="CPython+simpleParseString"></a>
### cPython.simpleParseString()
**Kind**: instance method of <code>[CPython](#CPython)</code>  
<a name="CPython+simpleParseFile"></a>
### cPython.simpleParseFile()
**Kind**: instance method of <code>[CPython](#CPython)</code>  
<a name="CPython+string"></a>
### cPython.string()
**Kind**: instance method of <code>[CPython](#CPython)</code>  
<a name="CPython+file"></a>
### cPython.file()
**Kind**: instance method of <code>[CPython](#CPython)</code>  
<a name="CPython+compileString"></a>
### cPython.compileString()
**Kind**: instance method of <code>[CPython](#CPython)</code>  
<a name="CPython+evalCode"></a>
### cPython.evalCode()
**Kind**: instance method of <code>[CPython](#CPython)</code>  
<a name="CPython+evalFrame"></a>
### cPython.evalFrame()
**Kind**: instance method of <code>[CPython](#CPython)</code>  
<a name="CPython+initialize"></a>
### cPython.initialize()
initialize python context, reserve memory.

**Kind**: instance method of <code>[CPython](#CPython)</code>  
<a name="CPython+finalize"></a>
### cPython.finalize(callback)
Finalize python context, clear memory.

**Kind**: instance method of <code>[CPython](#CPython)</code>  

| Param | Type | Description |
| --- | --- | --- |
| callback | <code>callback</code> | for completion of py context |

<a name="CPython+setProgramName"></a>
### cPython.setProgramName(Program)
set low level python program name (optional)

**Kind**: instance method of <code>[CPython](#CPython)</code>  

| Param | Type | Description |
| --- | --- | --- |
| Program | <code>string</code> | name. |

<a name="CPython+setArgv"></a>
### cPython.setArgv(string)
set low level python argv

**Kind**: instance method of <code>[CPython](#CPython)</code>  

| Param | Type | Description |
| --- | --- | --- |
| string | <code>string</code> &#124; <code>Array.&lt;string&gt;</code> | or an array of strings as argv argc is auto computed by the arrays length |

<a name="CPython+pyCreateContext"></a>
### cPython.pyCreateContext(python)
Create a context in memory to run the python script and injects a python function to run in.

**Kind**: instance method of <code>[CPython](#CPython)</code>  

| Param | Type | Description |
| --- | --- | --- |
| python | <code>callback</code> | function to run in the memory |

