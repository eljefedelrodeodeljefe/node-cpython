'use strict'
var test = require('tape');
var util = require('util')

test('Can be required', function (t) {
    t.plan(2);

    let ncpy = require('../')
    t.ok(ncpy, 'Instance of node-cpython class was created')
    let ncpy2 = require('../')
    t.deepEqual(ncpy, ncpy2, '2 Intances should be exactly the same')

});

test('Simple ffi', function (t) {
    t.plan(3);

    let ncpy = require('../')
    t.comment('Running ffi on simple multiplication')
    ncpy.ffi('examples/py/multiplication.py', 'multiply', [20, 5], function (err, res) {
      t.deepEqual(err,{}, 'Error is falsy here')
      t.equal(res, 100, 'multiply fixture w/ integers should result in 100')
    })

    ncpy.once('error', function(err) {
      if(err instanceof Error) {
        t.pass('Error from class emitter, when ncpy is run w/o insufficient arguments count')
        console.log(err);
      }
    })
    ncpy.ffi()
});

test('Py Streams', function (t) {
    t.plan(1);

    var ncpy = require('../');

    var Readable = require('stream').Readable;
    var Transform = require('stream').Transform;
    var SomeStream = new Readable({ "objectMode": true })
    function testTransform() {
      Transform.call(this, { objectMode: true })
    }
    util.inherits(testTransform, Transform)
    testTransform.prototype._transform = function(data, encoding, done) {
      console.log(data);
      return done()
    }

    SomeStream.push([1,2])
    SomeStream.push([20,3])
    SomeStream.push([3,40])
    SomeStream.push([4,50])
    SomeStream.push([55,66])
    SomeStream.push(null)

    let res = [2, 60, 120, 200, 3630]

    ncpy.ffi
      // load the python script and intitialize the python interpreter
      .require('py/multiplication.py', { path: './examples' })
      // this expects a stream (in { objectMode: true })
      .init(SomeStream)
      // Tell `ncpy` what function to excute.
      .run('multiply')
      // add your own transform or any other stream here
      .pipe(new testTransform())
      .on('end', function() {
        t.pass()
        t.comment('ncpy -> Ending python context here.');
      })
});

test('Ncpy.simpleString', function (t) {
  t.plan(4)
  var ncpy = require('../')
  ncpy.simpleString("from time import time,ctime\nprint 'Today is',ctime(time())\n", function() {
    t.pass()
  })
  ncpy.simpleString("from time import time,ctime\nprint 'Today is',ctime(time())\n")
  t.pass('Can be executed w/ no callback also')

  ncpy.once('error', function(err) {
    if(err instanceof Error) {
      t.pass('Error from class emitter is of type error')
    }
  })

  ncpy.simpleString(2, function(err) {
    if(err instanceof Error) {
      t.pass('Error from callback is of type error')
    }
  })
})

test('Ncpy.runString', function (t) {
  t.plan(1)
  t.pass()
})

test('Ncpy.initialize / Ncpy.finalize', function (t) {
  t.plan(3)
  var ncpy = require('../')
  ncpy.initialize()
  t.ok(ncpy.isInitialized(), 'Ncpy is initialized')
  ncpy.finalize()
  ncpy.isFinalized()
  t.ok(ncpy.isFinalized(), 'Ncpy is finalized')
  t.pass('initialize and finalize test is okay,q when no segfault or expection is thrown')
})

test('Ncpy.init and default options', function (t) {
  t.plan(3)
  var ncpy = require('../')
  t.equal(ncpy.opts.version, '2.7', 'Default version (w/o calling constructor explictely) is 2.7')
  var ref1 = ncpy.init({version: '2.7'})
  t.equal(ref1.opts.version, '2.7', 'Version (w/ calling constructor explictely) is 2.7')
  var ref2 = ncpy.init({version: '3.x'})
  t.equal(ref2.opts.version, '3.x', 'Version (w/ calling constructor explictely) is 3.x')
})
