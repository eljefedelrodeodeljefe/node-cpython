'use strict'
var test = require('tape');

test('Can be required', function (t) {
    t.plan(2);

    let cpython = require('../')
    t.ok(cpython, 'Instance of node-cpython class was created')
    let cpython2 = require('../')
    t.deepEqual(cpython, cpython2, '2 Intances should be exactly the same')

});
