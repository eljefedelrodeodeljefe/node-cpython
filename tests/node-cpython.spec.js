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
    t.plan(2);

    let ncpy = require('../')
    t.comment('Running ffi on simple multiplication')
    ncpy.ffi('examples/py/multiplication.py', 'multiply', [20, 5], function (err, res) {
      t.deepEqual(err,{}, 'Error is falsy here')
      t.equal(res, 100, 'multiply fixture w/ integers should result in 100')
    })
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
