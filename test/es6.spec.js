'use strict'
var expect = require('chai').expect
var cpython = require('../src/es6/cpython')

describe('CPython class', function () {

  it('Call CPython class', function (done) {
    done()
  });

  it('CPython class does extend EventEmitter', function (done) {
    cpython.on('testevent', function (arg) {
      expect(arg).to.eql('test')
      done()
    })
    cpython.emit('testevent', "test")
  });

  it('Throws errors through EventEmitter', function (done) {
    try {
      cpython.simpleFile('someargument1', 'someargument2', 'someargument2')
    } catch (e) {
      cpyton.on('error', function(err) {
        expect(err).to.throw(Error)
        done()
      })
    } finally {
      done()
    }

  });
});
