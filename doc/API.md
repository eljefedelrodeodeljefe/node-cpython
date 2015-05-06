<a name="CPython"></a>
## CPython
**Kind**: global class  

* [CPython](#CPython)
  * [new CPython()](#new_CPython_new)
  * [.anyFile()](#CPython#anyFile)
  * [.simpleString(str, [flags], [cb])](#CPython#simpleString)
  * [.simpleFile(filepath, filename, [flags], [cb])](#CPython#simpleFile)
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

cpython.simpleString("from time import time,ctime\nprint 'Today is',ctime(time())\n")
```
<a name="CPython#simpleFile"></a>
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
'use strict';
var cpython = require('cpython');

cpython.on('error', function(err) {console.log(err);})

cpython.simpleFile("example/multiply.py", "multiply.py")
// passing the filename seems to be a necessity of the C-API
// TODO: this will only last very shortly and be made optional
```
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
