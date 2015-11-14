'use strict'
var test = require('tape');

test('Can be required', function (t) {
    t.plan(2);

    let ncpy = require('../')
    t.ok(ncpy, 'Instance of node-cpython class was created')
    let ncpy2 = require('../')
    t.deepEqual(ncpy, ncpy2, '2 Intances should be exactly the same')

});

// test('Simple ffi', function (t) {
//     t.plan(2);
//
//     let ncpy = require('../')
//     t.comment('Running ffi on simple multiplication')
//     ncpy.ffi('../examples/multiplication.py', 'multiply', [20, 5], function (err, res) {
//       t.deepEqual(err,{}, 'Error is falsy here')
//       t.equal(res, 100, 'multiply fixture w/ integers should result in 100')
//     })
// });
