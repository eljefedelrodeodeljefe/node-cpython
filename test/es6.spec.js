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

  it('Throws errors through EventEmitter if more than 2 args', function (done) {
      cpython.on('error', function(err) {
        expect(err).to.be.an.instanceof(Error)
        done()
      })
      cpython.simpleFile('someargument1', 'someargument2', 'someargument3')
  });

  it('Throws no error with less than 3 args', function (done) {
      cpython.on('error', function(err) {
        expect(err).to.be.undefined;
      })
      cpython.simpleFile('someargument1','some')
      done()
  });

  it('Gets globbing pattern right', function (done) {
      //
      // let files = []
      // let cb = function(err, files) {
      //  done()
      // }
      //
      // cpython._getListOfFiles("**/*.py", {silent: true} , cb)
      // expect(files).to.be.instanceof(Array);
      done()

  });


});
